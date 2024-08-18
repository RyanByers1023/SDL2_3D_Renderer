#include "Renderer.h"

Renderer::Renderer(const int windowWidth, const int windowHeight)
	: screenPtr(std::make_unique<Screen>(windowWidth, windowHeight)),
	  projMatrixPtr(std::make_unique<ProjectionMatrix>(windowWidth, windowHeight)),
	  clipperPtr(std::make_unique<PolygonClipper>()),
	  cameraLocation(Vec3(80.0f, 60.0f, 0.0f))
{
	SetScreenSpaceBoundaries();
}

void Renderer::SetScreenSpaceBoundaries(){
	// left boundary of screen
	//assume 1920x1080 resolution for ex. vals:
	this->boundingEdgeLeft.v1 = { 0, 0 }; //(0,0) -- top left corner
	this->boundingEdgeLeft.v2 = { 0, screenPtr->height }; //(0, 1080) -- bottom left corner

	// bottom boundary of screen
	this->boundingEdgeBottom.v1 = { 0, screenPtr->height }; //(0, 1080) -- bottom left corner
	this->boundingEdgeBottom.v2 = { screenPtr->width, screenPtr->height }; //(1920, 1080) -- bottom right corner

	// right boundary of screen
	this->boundingEdgeRight.v1 = { screenPtr->width, screenPtr->height }; //(1920, 1080) -- bottom right corner
	this->boundingEdgeRight.v2 = { screenPtr->width, 0 }; //(1920, 0) -- top right corner

	// top boundary of screen
	this->boundingEdgeTop.v1 = { screenPtr->width, 0 }; //(1920, 0) -- top right corner
	this->boundingEdgeTop.v2 = { 0, 0 }; //(0,0) -- top left corner
}

//draws all objects contained within worldObjects to the screen. will call shader functions as well, but these will be kept in a seperate module, Shader.cpp 
bool Renderer::Render(std::unique_ptr<WorldObjects>& worldObjectsPtr) { 
	std::vector<Polygon2D> polygonList;

	if (worldObjectsPtr->objects.empty()) {
		std::cout << "There are no objects to render. Renderer shutting down..." << std::endl;
		return false;
	}

	//Initialize all objects' face and vertex normals
	GetAllNormals(worldObjectsPtr);
	
	//obtain list of all polygons that are within the screen space boundaries, store in polygonList
	GetProjectedPolygons(worldObjectsPtr, polygonList);

	//clip all polygons in polygonList against the screen boundaries, store in polygonList
	GetClippedPolygons(polygonList);

	//draw the polygon(s) to the screen
	DrawPolygons(polygonList);

	//fill the area between the vertices of the polygon using a scanline algorithm (SHADING NOT YET IMPLEMENTED)
	screenPtr->Show(); //will go through screen.vertices and show each vertex (pixel) on the screen
	screenPtr->Clear(); //clear the screen (will also clear out screenPtr->vertices)
	SDL_Delay(15); //this will determine the frame rate of the simulation. set to update every 15 msecs. lower value == higher framerate. Is normalized using Time.deltaTime;

	return true;
}

//grab current normal vector of all vertices and faces within worldObjectsPtr during this current frame
void Renderer::GetAllNormals(std::unique_ptr<WorldObjects>& worldObjectsPtr) const {
	GetAllFaceNormals(worldObjectsPtr);
	GetAllVertexNormals(worldObjectsPtr);
}

//grab normal vector of all tri3D faces
void Renderer::GetAllFaceNormals(std::unique_ptr<WorldObjects>& worldObjectsPtr) const {
	for (const auto& it : worldObjectsPtr->objects) {
		for (auto& tri3D : it.second->primitiveMesh.triangles) {
			tri3D.faceNormal = CalculateNormalVector(tri3D); //store it within the mesh for later use
		}
	}
}

//grab normals of all tri3D vertices
void Renderer::GetAllVertexNormals(std::unique_ptr<WorldObjects>& worldObjectsPtr) const {
	for (const auto& it : worldObjectsPtr->objects) {
		StoreVertexNormals(it.second->primitiveMesh);
	}
}

//obtain normals corresponding to vertices and store within the mesh for easy access
void Renderer::StoreVertexNormals(mesh& triangleMesh) const{
	std::map<Vec3, Vec3> vertexNormalMap;

	//below loop visits each within the mesh multiple times...
	//this process causes each vertex to eventually have each face it is adjacent of to have its face normal added to it

	//accumulate face normals for each vertex
	for (Triangle3D& tri3D : triangleMesh.triangles) { //visit every triangle that makes up triangleMesh.triangles
		for (int i = 0; i < 3; ++i) { //add all face normal adajacent to this vertex together
			vertexNormalMap[tri3D.vertices[i]] += tri3D.faceNormal; //add face normal corresponding to this vertex to this vertex's entry
		}
	}

	//turn accumulation of face vertices into vertex normals
	for (Triangle3D& tri3D : triangleMesh.triangles) {
		//turn the summation of the face normals adjacent to this vertex into averages of the face normals adajacent to this vertex
		for (int i = 0; i < 3; ++i) { //iterate through each vertex in the triangle
			vertexNormalMap[tri3D.vertices[i]] = vertexNormalMap[tri3D.vertices[i]].Normalize(); //normalize it (take average), store at global level
			tri3D.vertexNormals[i] = vertexNormalMap[tri3D.vertices[i]]; //store normalized vertex normal at local level
		}
	}

	//store the vertexMap in the mesh of the 3D triangle
	triangleMesh.vertexNormalMap = vertexNormalMap;
}

void Renderer::GetClippedPolygons(std::vector<Polygon2D>& polygonList) const {
	for(auto& poly: polygonList){
		//replace the projected ploygon with a clipped polygon
		poly = PerformClipping(poly);
	}
}

void Renderer::GetProjectedPolygons(const std::unique_ptr<WorldObjects>&, std::vector<Polygon2D>& polygonList) const{
	for (auto& it : worldObjectsPtr->objects) { //for every object contained in the worldObjects->objects unordered_map
		for (auto& tri3D : it.second->primitiveMesh.triangles) { //project each triangle that is a part of each respective mesh one at a time, and store this projection in polygonList

			if (ShouldRender(tri3D, tri3D.faceNormal, cameraLocation)) { //only consider a part of a mesh for rendering if it should be visible with respect to the camera object
				
				//project the triangle to 2-space and convert coordinates from NDC coordinates to screen space coordinates
				Polygon2D projectedTriangle = ProjectTriangle(tri3D);

				//store triangle in polygonList
				polygonList.push_back(projectedTriangle);
			}
		}		
	}
}

Polygon2D Renderer::ProjectTriangle(const Triangle3D& tri3D) const{
	Polygon2D projectedTriangle;

	//project the triangle to 2-space
	for (auto& vertex : tri3D.vertices) {
		Vec2 newVertex = GetScreenSpaceVertex(vertex, cameraLocation, screenPtr->width, screenPtr->height);
		projectedTriangle.vertices.push_back(newVertex);
	}

	return projectedTriangle;
}

Polygon2D Renderer::PerformClipping(const Polygon2D& projectedTriangle) const {
	//clip in counterclockwise order starting at screen's left boundary
	Polygon2D clippedTriangle;

	//clip against the left boundary
	clippedTriangle = clipperPtr->Clip(projectedTriangle, boundingEdgeLeft);

	//clip against the bottom boundary
	clippedTriangle = clipperPtr->Clip(clippedTriangle, boundingEdgeBottom);

	//clip against the right boundary
	clippedTriangle = clipperPtr->Clip(clippedTriangle, boundingEdgeRight);

	//clip against the top boundary
	clippedTriangle = clipperPtr->Clip(clippedTriangle, boundingEdgeTop);

	//now clippedTriangle holds a clipped version of projectedTriangle
	return clippedTriangle;
	
}

Vec2 Renderer::GetScreenSpaceVertex(const Vec3 &vertex, const Vec3& cameraLocation, const float width, const float height) const {
	//evaluate coordinates relative to camera's position
	float viewX = vertex.x - cameraLocation.x;
	float viewY = vertex.y - cameraLocation.y;
	float viewZ = vertex.z - cameraLocation.z;

	//perform transformation using the projection matrix
	float newX = viewX * projMatrixPtr->matrix[0][0] + viewY * projMatrixPtr->matrix[1][0] + viewZ * projMatrixPtr->matrix[2][0] + projMatrixPtr->matrix[3][0];
	float newY = viewX * projMatrixPtr->matrix[0][1] + viewY * projMatrixPtr->matrix[1][1] + viewZ * projMatrixPtr->matrix[2][1] + projMatrixPtr->matrix[3][1];
	float newZ = viewX * projMatrixPtr->matrix[0][2] + viewY * projMatrixPtr->matrix[1][2] + viewZ * projMatrixPtr->matrix[2][2] + projMatrixPtr->matrix[3][2];
	float w = viewX * projMatrixPtr->matrix[0][3] + viewY * projMatrixPtr->matrix[1][3] + viewZ * projMatrixPtr->matrix[2][3] + projMatrixPtr->matrix[3][3];

	//convert to Cartesian coordinates
	if (w != 0.0f) {
		newX /= w;
		newY /= w;
		newZ /= w;
	}

	//convert from NDC to screen space coordinates
	float screenSpaceX = (newX + 1.0f) * 0.5f * width;
	float screenSpaceY = (1.0f - newY) * 0.5f * height;

	//FIX-ME: float being used for screen space coordinates (is this a problem?)
	return Vec2(screenSpaceX, screenSpaceY);
}

//draw edges of polygons in polygonList to the screen (DOES NOT PERFORM SHADING)
void Renderer::DrawPolygons(const std::vector<Polygon2D>& polygonList) {

	//access list of polygons
 	for(auto& poly : polygonList){
		//access list of vertices for each polygon
		for(int i = 0; i < poly.vertices.size(); ++i){
			if(poly.vertices.size() < 3) continue; //cannot form a closed 2-D shape without more than 2 vertices

			//FIX-ME: implement shading here.

			//get the two vertices that make up the edge
			Vec2 v1 = poly.vertices[i];
			Vec2 v2 = poly.vertices[(i + 1) % poly.vertices.size()]; //choose the next vertex in the list, if i == the second to last index, loop back around to complete the shape

			//create line to hold edge of polygon
			Line newLine(v1, v2);
			
			//add to screenPtr's pixel list (this can be done using line.cpp's draw function)
			newLine.Draw(screenPtr);
		}
	}
}
