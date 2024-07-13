#include "Renderer.h"

Renderer::Renderer(int windowWidth, int windowHeight, WorldObjects* worldObjectsPtr) {
	//get all of the needed parameters from the runner file
	this->screenPtr = new Screen(windowWidth, windowHeight);
	this->projMatrixPtr = new ProjectionMatrix(windowWidth, windowHeight);
	this->shaderPtr = new Shader(screenPtr);
	this->worldObjectsPtr = worldObjectsPtr;
	this->clipperPtr = new PolygonClipper();

	//set up the screen space boundaries:
	SetScreenSpaceBoundaries();

	//this is temporary:
	cameraLocation = { 0.0f, 0.0f, 0.0f }; //initalize camera location to origin
}

Renderer::~Renderer() {
	delete this->screenPtr;
	delete this->projMatrixPtr;
	delete this->shaderPtr;
	delete this->clipperPtr;
}

void Renderer::SetScreenSpaceBoundaries(){
	//left boundary of screen
	this->boundingEdgeLeft.v1 = {0, screenPtr->height};
	this->boundingEdgeLeft.v2 = {0, 0};

	//right boundary of screen
	this->boundingEdgeRight.v1 = {screenPtr->width, screenPtr-> height};
	this->boundingEdgeRight.v2 = {screenPtr->width, 0};

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
					vertex *= projMatrixPtr;
					projectedTriangle.vertices.push_back(vertex);
				}

				/*
				std::cout << "Projected Triangle point[0].x = " << projectedTriangle.point[0].x << "Projected Triangle point[0].y = " << projectedTriangle.point[0].y << std::endl;
				std::cout << "Projected Triangle point[1].x = " << projectedTriangle.point[1].x << "Projected Triangle point[0].y = " << projectedTriangle.point[1].y << std::endl;
				std::cout << "Projected Triangle point[2].x = " << projectedTriangle.point[2].x << "Projected Triangle point[0].y = " << projectedTriangle.point[2].y << std::endl;
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

//draw edges of polygons in polygonList to the screen (DOES NOT PERFORM SHADING)
void Renderer::DrawPolygons(){
	//create line to hold edge of polygon
	Line newLine(screenPtr);
	//access list of polygons
 	for(auto& poly : polygonList){
		//access list of vertices for each polygon
		for(int i = 0; i < poly.vertices.size(); ++i){
			if(poly.vertices.size() < 3) continue; //cannot form a closed 2-D shape without more than 2 vertices

			//get the two vertices that make up the polygon
			Vec2 v1 = poly.vertices[i];
			Vec2 v2 = poly.vertices[(i + 1) % poly.vertices.size()]; //choose the next vertex in the list, if i == the second to last index, loop back around to complete the shape

			//create the line that defines this edge of the polygon
			newLine.line.v1.x = v1.x; newLine.line.v1.y = v1.y;
			newLine.line.v2.x = v2.x; newLine.line.v2.y = v2.y;
			
			//add to screenPtr's pixel list (this can be done using line.cpp's draw function)
			newLine.Draw();
		}
	}
}
