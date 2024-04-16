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

void Renderer::CalculateNormalVector(const Triangle3D tri) { //put in RendererHelperFunctions.cpp
	//need to determine whether or not we need to draw the triangle based on perspective (eg. we don't want to render the back side of the triangle if we are viewing the front)...
	//use the cross product of two vectors to determine the normal vector, use this to determine angle with respect to camera.
	//this angle is useful to determine if a certain triangle should be visible to the camera or not
	Vec3 normal, lineA, lineB;

	//calculate line A and line B
	lineA.x = tri.point[1].x - tri.point[0].x; lineB.x = tri.point[2].x - tri.point[0].x;
	lineA.y = tri.point[1].y - tri.point[0].y; lineB.y = tri.point[2].y - tri.point[0].y;
	lineA.z = tri.point[1].z - tri.point[0].z; lineB.z = tri.point[2].z - tri.point[0].z;

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

bool Renderer::ShouldRender(const Triangle3D tri) { //put in RendererHelperFunctions.cpp
	//determine whether or not the triangle should be rendered...
	//calculate the dot product between the normal, the camera and a triangle that is on the same plane. Trivially, the first point was selected. Could have been p[1] or p[2], it would still work regardless.
	//if this value is negative, then draw the triangle.
	return (normal.x * (tri.point[0].x - cameraLocation.x) +
			normal.y * (tri.point[0].y - cameraLocation.y) +
			normal.z * (tri.point[0].z - cameraLocation.z)) < 0.0f; //Notice: if you change this statement to instead evaluate true for dotproductN > 0.0f, the object will be renderered inside out...
}

void Renderer::SortVerticesByYCoordinates(Triangle2D& triangleCopy) { //sort in ascending order to make shading easier ////put in ShaderHelperFunctions.cpp
	if (triangleCopy.point[0].y > triangleCopy.point[1].y) std::swap(triangleCopy.point[0].y, triangleCopy.point[1].y);
}

float Renderer::CalculateSlope(const Triangle2D triangleCopy) { //put in RendererHelperFunctions.cpp
	float slopeRise = triangleCopy.point[1].y - triangleCopy.point[0].y;
	float slopeRun = triangleCopy.point[1].x - triangleCopy.point[0].x;
	if (slopeRise == 0) return 0; //avoid division by zero
	else return (slopeRise / slopeRun);
}

void Renderer::Shade(Triangle2D& triangleCopy) { //put in Shader.cpp
	SortVerticesByYCoordinates(triangleCopy);
}

bool Renderer::Render() { //draws all objects contained within worldObjects to the screen. will call shader functions as well, but these will be kept in a seperate module, Shader.cpp 
	if (worldObjectsPtr->objects.empty()) {
		std::cout << "There are no objects to render. Renderer shutting down..." << std::endl;
		return false;
	}

	for (const auto& it : worldObjectsPtr->objects) { //for every object contained in the worldObjects->objects unordered_map///
		for (auto& tri3D : it.second.primitiveMesh.triangles) { //project and draw each triangle that is a part of their mesh one at a time
			
			CalculateNormalVector(tri3D);

			if (ShouldRender(tri3D)) { //only project and draw a part of a mesh if it should be visible with respect to the camera object
				Triangle2D projectedTriangle;

				for (int i = 0; i < 3; i++) {
					projectedTriangle.point[i] = tri3D.point[i] * *projMatrixPtr;
				}

				/*
				std::cout << "Projected Triangle point[0].x = " << projectedTriangle.point[0].x << "Projected Triangle point[0].y = " << projectedTriangle.point[0].y << std::endl;
				std::cout << "Projected Triangle point[1].x = " << projectedTriangle.point[1].x << "Projected Triangle point[0].y = " << projectedTriangle.point[1].y << std::endl;
				std::cout << "Projected Triangle point[2].x = " << projectedTriangle.point[2].x << "Projected Triangle point[0].y = " << projectedTriangle.point[2].y << std::endl;
				std::cout << "\n\n\n";
				*/

				projectedTriangle.point[0].x += 1.0f; projectedTriangle.point[0].y += 1.0f; //make sure when we draw our objects, we draw them in front of the camera (this may be removed later)
				projectedTriangle.point[1].x += 1.0f; projectedTriangle.point[1].y += 1.0f;
				projectedTriangle.point[2].x += 1.0f; projectedTriangle.point[2].y += 1.0f;

				float halfScreenWidth = static_cast<float>(screenPtr->width) * 0.5f; //get the values corresponding to the middle of the screen (this may be removed later)
				float halfScreenHeight = static_cast<float>(screenPtr->height) * 0.5f;

				projectedTriangle.point[0].x *= halfScreenWidth; projectedTriangle.point[0].y *= halfScreenHeight; //draw the objects in the middle of the screen (this may be removed later)
				projectedTriangle.point[1].x *= halfScreenWidth; projectedTriangle.point[1].y *= halfScreenHeight;
				projectedTriangle.point[2].x *= halfScreenWidth; projectedTriangle.point[2].y *= halfScreenHeight;

				Line line1(*screenPtr, projectedTriangle.point[0].x, projectedTriangle.point[0].y, projectedTriangle.point[1].x, projectedTriangle.point[1].y); //first line of triangle (side a)
				line1.Draw();

				Line line2(*screenPtr, projectedTriangle.point[1].x, projectedTriangle.point[1].y, projectedTriangle.point[2].x, projectedTriangle.point[2].y); //second line of triangle (side b)
				line2.Draw();

				Line line3(*screenPtr, projectedTriangle.point[2].x, projectedTriangle.point[2].y, projectedTriangle.point[0].x, projectedTriangle.point[0].y); //third line of triangle (side c) -- this is the hypotenuse
				line3.Draw();
			}
		}		
	}

	screenPtr->Show(); //will go through screen.vertices and draw each vertex (pixel) to the screen
	screenPtr->Clear(); //clear the screen (will also clear out screen.vertices)
	SDL_Delay(15); //this will determine the frame rate of the simulation. set to update every 15 msecs. lower value == higher framerate. Is normalized using Time.deltaTime;

	return true;
}
