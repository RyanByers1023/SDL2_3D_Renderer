#include "Renderer.h"

Renderer::Renderer(int windowWidth, int windowHeight, WorldObjects* worldObjectsPtr) {
	this->screenPtr = new Screen(windowWidth, windowHeight);
	this->projMatrixPtr = new ProjectionMatrix(windowWidth, windowHeight);
	this->worldObjectsPtr = worldObjectsPtr;

	//this is temporary:
	cameraLocation = { 0.0f, 0.0f, 0.0f };
}

Renderer::~Renderer() {
	delete this->screenPtr;
	delete this->projMatrixPtr;
}

void Renderer::CalculateNormalVector(const triangle tri) {
	//need to determine whether or not we need to draw the triangle based on perspective (eg. we don't want to render the back side of the triangle if we are viewing the front)...
	//use the cross product of two vectors to determine the normal vector, use this to determine angle with respect to camera.
	//this angle is useful to determine if a certain triangle should be visible to the camera or not
	vec3 normal, lineA, lineB;

	//calculate line A and line B
	lineA.x = tri.p[1].x - tri.p[0].x; lineB.x = tri.p[2].x - tri.p[0].x;
	lineA.y = tri.p[1].y - tri.p[0].y; lineB.y = tri.p[2].y - tri.p[0].y;
	lineA.z = tri.p[1].z - tri.p[0].z; lineB.z = tri.p[2].z - tri.p[0].z;

	//Calculate the cross product of the two vectors A and B. Gives the normal (perpendicular) vector with respect to both of them.
	this->normal.x = lineA.y * lineB.z - lineA.z * lineB.y;
	this->normal.y = lineA.z * lineB.x - lineA.x * lineB.z;
	this->normal.z = lineA.x * lineB.y - lineA.y * lineB.x;

	//normalize the normal vector -- need x^2, y^2, and z^2 from the normal vector
	float xComponentSqaured = this->normal.x * this->normal.x; float yComponentSquared = this->normal.y * this->normal.y; float zComponentSquared = this->normal.z * this->normal.z;

	//use the distance formula to determine magnitude (length of vector)
	float magnitude = sqrtf(xComponentSqaured + yComponentSquared + zComponentSquared);

	//use magnitude of normal vector to create the unit (length of 1) normal vector:
	this->normal.x /= magnitude; this->normal.y /= magnitude; this->normal.z /= magnitude;
}

bool Renderer::ShouldRender(const triangle tri) {
	//determine whether or not the triangle should be rendered...
	//calculate the dot product between the normal, the camera and a triangle that is on the same plane. Trivially, the first point was selected. Could have been p[1] or p[2], it would still work regardless.
	//if this value is negative, then draw the triangle.
	return (normal.x * (tri.p[0].x - cameraLocation.x) +
			normal.y * (tri.p[0].y - cameraLocation.y) +
			normal.z * (tri.p[0].z - cameraLocation.z)) < 0.0f;
}

bool Renderer::Render() { //draws all objects contained within worldObjects to the screen
	if (worldObjectsPtr->objects.empty()) {
		std::cout << "There are no objects to render. Renderer shutting down..." << std::endl;
		return false;
	}

	for (const auto& it : worldObjectsPtr->objects) { //for every object contained in the worldObjects->objects unordered_map///
		for (auto& tri : it.second.primitiveMesh.triangles) { //project and draw each triangle that is a part of their mesh one at a time
			triangle projectedTriangle; //store projected version of the triangle here

			CalculateNormalVector(tri);

			//only project and draw a part of a mesh if it should be visible with respect to the camera object
			if (ShouldRender(tri)) {
				for (int i = 0; i < 3; i++) {
					projectedTriangle.p[i] = tri.p[i] * *projMatrixPtr; //project each of the edges of the triangle using the projection vector (previously initialized) turns 3-D triangle into 2-D projection
				}

				projectedTriangle.p[0].x += 1.0f; projectedTriangle.p[0].y += 1.0f; //make sure when we draw our objects, we draw them in front of the camera (this may be removed later)
				projectedTriangle.p[1].x += 1.0f; projectedTriangle.p[1].y += 1.0f;
				projectedTriangle.p[2].x += 1.0f; projectedTriangle.p[2].y += 1.0f;

				float halfScreenWidth = static_cast<float>(screenPtr->width) * 0.5f; //get the values corresponding to the middle of the screen (this may be removed later)
				float halfScreenHeight = static_cast<float>(screenPtr->height) * 0.5f;

				projectedTriangle.p[0].x *= halfScreenWidth; projectedTriangle.p[0].y *= halfScreenHeight; //draw the objects in the middle of the screen (this may be removed later)
				projectedTriangle.p[1].x *= halfScreenWidth; projectedTriangle.p[1].y *= halfScreenHeight;
				projectedTriangle.p[2].x *= halfScreenWidth; projectedTriangle.p[2].y *= halfScreenHeight;

				float x1 = projectedTriangle.p[0].x; float y1 = projectedTriangle.p[0].y; //get the values needed to draw the lines to the screen (all of the vertices that make up the edges of the triangles in 2-space)
				float x2 = projectedTriangle.p[1].x; float y2 = projectedTriangle.p[1].y;
				float x3 = projectedTriangle.p[2].x; float y3 = projectedTriangle.p[2].y;

				Line line1(*screenPtr, x1, y1, x2, y2); //first line of triangle (side a)
				line1.Draw();

				Line line2(*screenPtr, x2, y2, x3, y3); //second line of triangle (side b)
				line2.Draw();

				Line line3(*screenPtr, x3, y3, x1, y1); //third line of triangle (side c) -- this is the hypotenuse
				line3.Draw();
			}
		}		
	}

	screenPtr->Show(); //will go through screen.vertices and draw each vertex (pixel) to the screen
	screenPtr->Clear(); //clear the screen (will also clear out screen.vertices)
	SDL_Delay(15); //this will determine the frame rate of the simulation. set to update every 15 msecs. lower value == higher framerate. Is normalized using Time.deltaTime;

	return true;
}
