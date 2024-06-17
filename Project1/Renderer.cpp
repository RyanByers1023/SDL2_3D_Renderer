#include "Renderer.h"

Renderer::Renderer(int windowWidth, int windowHeight, WorldObjects* worldObjectsPtr) {
	//get all of the needed parameters from the starter file
	this->screenPtr = new Screen(windowWidth, windowHeight);
	this->projMatrixPtr = new ProjectionMatrix(windowWidth, windowHeight);
	this->shaderPtr = new Shader(screenPtr);
	this->worldObjectsPtr = worldObjectsPtr;

	//set up the screen space boundaries
	this->boundingEdgeLeft.v1 = {0, screenPtr->height}; this->boundingEdgeLeft.v2 = {0, 0}; //left boundary of screen
	this->boundingEdgeRight.v1 = {screenPtr->width, screenPtr-> height}; this->boundingEdgeRight.v2 = {screenPtr->width, 0}; //right boundary of screen
	this->boundingEdgeTop.v1 = {0,0}; this->boundingEdgeTop.v2 = {screenPtr->width, 0}; //top boundary of screen
	this->boundingEdgeBottom.v1 = {0, screenPtr->height}; this->boundingEdgeBottom.v2 = {screenPtr->width, screenPtr->height}; //bottom boundary of screen

	//this is temporary:
	cameraLocation = { 0.0f, 0.0f, 0.0f };
}

Renderer::~Renderer() {
	delete this->screenPtr;
	delete this->projMatrixPtr;
	delete this->shaderPtr;
}

bool Renderer::Render() { //draws all objects contained within worldObjects to the screen. will call shader functions as well, but these will be kept in a seperate module, Shader.cpp 
	polygonList.clear(); //reset the list of 2D polygons for the current frame
	if (worldObjectsPtr->objects.empty()) {
		std::cout << "There are no objects to render. Renderer shutting down..." << std::endl;
		return false;
	}

	//get a list of all polygons that are within the screen space and clip them, store in polygonList
	GetClippedPolygons();

	//draw the polygon to the screen
	DrawPolygons();

	//fill the area between the vertices of the polygon using a scanline algorithm (NOT IMPLEMENTED)
	screenPtr->Show(); //will go through screen.vertices and draw each vertex (pixel) to the screen
	screenPtr->Clear(); //clear the screen (will also clear out screen.vertices)
	SDL_Delay(15); //this will determine the frame rate of the simulation. set to update every 15 msecs. lower value == higher framerate. Is normalized using Time.deltaTime;

	return true;
}

void Renderer::GetClippedPolygons(){
	for (const auto& it : worldObjectsPtr->objects) { //for every object contained in the worldObjects->objects unordered_map///
		for (auto& tri3D : it.second.primitiveMesh.triangles) { //project and draw each triangle that is a part of their mesh one at a time
			
			Vec3 normal = CalculateNormalVector(tri3D);

			if (ShouldRender(tri3D, normal, cameraLocation)) { //only project and draw a part of a mesh if it should be visible with respect to the camera object
				Triangle2D projectedTriangle;

				//project the triangle to 2-space
				for (int i = 0; i < 3; i++) {
					projectedTriangle.point[i] = tri3D.point[i] * *projMatrixPtr;
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
				ClipVertices(projectedTriangle, clippedTriangle, boundingEdgeBottom);	
				ClipVertices(projectedTriangle, clippedTriangle, boundingEdgeRight);
				ClipVertices(projectedTriangle, clippedTriangle, boundingEdgeTop);
				ClipVertices(projectedTriangle, clippedTriangle, boundingEdgeLeft);

				//now clippedTriangle holds a clipped version of projectedTriangle		
				polygonList.push_back(clippedTriangle); //store it in polygonList
			}
		}		
	}
}

//all this does is draw lines from one edge of the polygon to another
//if i were to implement scanline shading (which I plan on doing) i dont think this will be necessary...
void Renderer::DrawPolygons(){
	//access list of polygons
 	for(auto& poly : polygonList){
		//access list of vertices for each polygon
		for(auto& vertex : poly.vertices){
			//add to screenPtr's pixel list (this can be done using line.cpp's draw function)
		}
	}
}
