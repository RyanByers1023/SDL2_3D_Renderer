#include "Renderer.h"

Renderer::Renderer(int windowWidth, int windowHeight, WorldObjects* worldObjectsPtr) {
	//get all of the needed parameters from the runner file
	this->screenPtr = new Screen(windowWidth, windowHeight);
	this->projMatrixPtr = new ProjectionMatrix(windowWidth, windowHeight, 90.0f, 100.0f, 0.1f);
	this->worldObjectsPtr = worldObjectsPtr;
	this->clipperPtr = new PolygonClipper();

	//set up the screen space boundaries:
	SetScreenSpaceBoundaries();

	//this is temporary:
	cameraLocation = { 80.0f, 60.0f, 0.0f };
}

Renderer::~Renderer() {
	delete this->screenPtr;
	delete this->projMatrixPtr;
	delete this->clipperPtr;
}

void Renderer::SetScreenSpaceBoundaries(){
	//left boundary of screen
	this->boundingEdgeLeft.v1 = { 0, 0 };
	this->boundingEdgeLeft.v2 = {0, screenPtr->height};

	//right boundary of screen
	this->boundingEdgeRight.v1 = { screenPtr->width, 0 };
	this->boundingEdgeRight.v2 = {screenPtr->width, screenPtr-> height};

	//top boundary of screen
	this->boundingEdgeTop.v1 = {0,0};
	this->boundingEdgeTop.v2 = {screenPtr->width, 0};

	//bottom boundary of screen
	this->boundingEdgeBottom.v1 = {0, screenPtr->height};
	this->boundingEdgeBottom.v2 = {screenPtr->width, screenPtr->height};
}

bool Renderer::Render() { //draws all objects contained within worldObjects to the screen. will call shader functions as well, but these will be kept in a seperate module, Shader.cpp 
	polygonList.clear(); //reset the list of 2D polygons for the current frame

	if (worldObjectsPtr->objects.empty()) {
		std::cout << "There are no objects to render. Renderer shutting down..." << std::endl;
		return false;
	}

	//get a list of all polygons that are within the screen space and clip them, store in polygonList
	GetClippedPolygons();

	//draw the polygon(s) to the screen
	DrawPolygons();

	//fill the area between the vertices of the polygon using a scanline algorithm (SHADING NOT YET IMPLEMENTED)
	screenPtr->Show(); //will go through screen.vertices and draw each vertex (pixel) to the screen
	screenPtr->Clear(); //clear the screen (will also clear out screen.vertices)
	SDL_Delay(15); //this will determine the frame rate of the simulation. set to update every 15 msecs. lower value == higher framerate. Is normalized using Time.deltaTime;

	return true;
}

void Renderer::GetClippedPolygons(){
	for (const auto& it : worldObjectsPtr->objects) { //for every object contained in the worldObjects->objects unordered_map///
		for (auto& tri3D : it.second.primitiveMesh.triangles) { //project each triangle that is a part of each respective mesh one at a time, and store this projection in polygonList
			
			//get the normal vector relative to the current triangle and the pov
			Vec3 normal = CalculateNormalVector(tri3D);

			if (ShouldRender(tri3D, normal, cameraLocation)) { //only consider a part of a mesh for rendering if it should be visible with respect to the camera object
				Triangle2D projectedTriangle;

				//project the triangle to 2-space
				for (auto& vertex : tri3D.point) {

					/*
					std::cout << "3D Triangle point[0].x = " << tri3D.point[0].x << "  3D Triangle point[0].y = " << tri3D.point[0].y << std::endl;
					std::cout << "3D Triangle point[1].x = " << tri3D.point[1].x << "  3D Triangle point[1].y = " << tri3D.point[1].y << std::endl;
					std::cout << "3D Triangle point[2].x = " << tri3D.point[2].x << "  3D Triangle point[2].y = " << tri3D.point[2].y << std::endl;
					std::cout << "3D Triangle point[0].z = " << tri3D.point[0].z << std::endl;
					std::cout << "3D Triangle point[1].z = " << tri3D.point[1].z << std::endl;
					std::cout << "3D Triangle point[2].z = " << tri3D.point[2].z << std::endl;
					std::cout << "\n\n\n";
					*/
					
					
					Vec2 newVertex = GetScreenSpaceVertex(vertex, cameraLocation, screenPtr->width, screenPtr->height);

					// Debug output to check values
					//std::cout << "Projected Vertex: (" << newVertex.x << ", " << newVertex.y << ")" << std::endl;

					projectedTriangle.vertices.push_back(newVertex);

					//std::cout << "Projected Vertex: (" << projectedTriangle.vertices.back().x << ", "  << projectedTriangle.vertices.back().y << ")" << std::endl;
				}

				/*
				std::cout << "Projected Triangle point[0].x = " << projectedTriangle.vertices[0].x << "  Projected Triangle point[0].y = " << projectedTriangle.vertices[0].y << std::endl;
				std::cout << "Projected Triangle point[1].x = " << projectedTriangle.vertices[1].x << "  Projected Triangle point[0].y = " << projectedTriangle.vertices[1].y << std::endl;
				std::cout << "Projected Triangle point[2].x = " << projectedTriangle.vertices[2].x << "  Projected Triangle point[0].y = " << projectedTriangle.vertices[2].y << std::endl;
				std::cout << "\n\n\n";
				*/
				

				//this will store the clipped version of the triangle
				Polygon2D clippedTriangle;

				//clip counterclockwise starting at the bottom of the screen with regard to the screen's boundaries
				clipperPtr->Clip(projectedTriangle, clippedTriangle, boundingEdgeBottom);	
				clipperPtr->Clip(projectedTriangle, clippedTriangle, boundingEdgeRight);
				clipperPtr->Clip(projectedTriangle, clippedTriangle, boundingEdgeTop);
				clipperPtr->Clip(projectedTriangle, clippedTriangle, boundingEdgeLeft);

				//now clippedTriangle holds a clipped version of projectedTriangle		
				polygonList.push_back(clippedTriangle); //store it in polygonList
			}
		}		
	}
}

Vec2 Renderer::GetScreenSpaceVertex(const Vec3 &vertex, const Vec3& cameraLocation, const float& width, const float& height) const {
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

	return Vec2(screenSpaceX, screenSpaceY);
}

//draw edges of polygons in polygonList to the screen (DOES NOT PERFORM SHADING)
void Renderer::DrawPolygons(){
	//create line to hold edge of polygon
	Line newLine(screenPtr);
	//access list of polygons
 	for(auto& poly : polygonList){
		//access list of vertices for each polygon
		for(int i = 0; i < poly.vertices.size(); ++i){
			if(poly.vertices.size() < 3) continue; //cannot form a closed 2-D shape without more than 2 vertices

			//get the two vertices that make up the edge
			Vec2 v1 = poly.vertices[i];
			Vec2 v2 = poly.vertices[(i + 1) % poly.vertices.size()]; //choose the next vertex in the list, if i == the second to last index, loop back around to complete the shape

			//create the line that defines this edge of the polygon
			newLine.line.v1 = v1;
			newLine.line.v2 = v2;
			
			//add to screenPtr's pixel list (this can be done using line.cpp's draw function)
			newLine.Draw();
		}
	}
}
