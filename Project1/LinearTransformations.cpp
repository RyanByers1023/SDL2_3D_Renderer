#include "LinearTransformations.h"
#include <iostream>

void LinearTransformations::ApplyRotation(InputHandler* inputHandlerPtr, Time* timePtr, PrimitiveObject& object) { //rotates radiansToRotate/sec when corresponding input is held down
	float xRadians = 0, yRadians = 0, zRadians = 0;
	float radiansToRotate = 1;

	
	Vec3 centeroid = object.centeroid;

	if (inputHandlerPtr->leftInput) yRadians = radiansToRotate * timePtr->deltaTime;
	if (inputHandlerPtr->rightInput) yRadians = -radiansToRotate * timePtr->deltaTime;
	if (inputHandlerPtr->upInput) xRadians = -radiansToRotate * timePtr->deltaTime;
	if (inputHandlerPtr->downInput) xRadians = radiansToRotate * timePtr->deltaTime;

	for (auto& tri : object.primitiveMesh.triangles) { //normalization
		for (int i = 0; i < 3; ++i) {
			tri.point[i].x -= centeroid.x;
			tri.point[i].y -= centeroid.y;
			tri.point[i].z -= centeroid.z;
		}
		
		//Debugging code for testing radian values
		//std::cout << "xRadians = " << xRadians << "yRadians = " << yRadians << "zRadians = " << zRadians << std::endl;

		RotationMatrix rotationMatrix(xRadians, yRadians, zRadians);

		/*for (int i = 0; i < 4; ++i) {
			for (int j = 0; j < 4; ++j) {
				std::cout << "Row " << i + 1 << " Column " << j + 1 << " = " << rotationMatrix.matrix[i][j] << std::endl;
			}
		}
		*/

		for (int i = 0; i < 3; i++) {
			tri.point[i] *= rotationMatrix;
		}

		for (int i = 0; i < 3; ++i) { //revert normalization operation
			tri.point[i].x += centeroid.x;
			tri.point[i].y += centeroid.y;
			tri.point[i].z += centeroid.z;
		}
	}
}

void LinearTransformations::ApplyTransformation(InputHandler* inputHandlerPtr, Time* timePtr, PrimitiveObject& object) {
	float dx = 0, dy = 0, dz = 0;

	float distanceToMove = 80.0f;

	
	if (inputHandlerPtr->wInput) dy = -distanceToMove * timePtr->deltaTime;
	if (inputHandlerPtr->aInput) dx = -distanceToMove * timePtr->deltaTime;
	if (inputHandlerPtr->sInput) dy = distanceToMove * timePtr->deltaTime;
	if (inputHandlerPtr->dInput) dx = distanceToMove * timePtr->deltaTime;
	if (inputHandlerPtr->zInput) dz = distanceToMove * timePtr->deltaTime;
	if (inputHandlerPtr->xInput) dz = -distanceToMove * timePtr->deltaTime;
	

	for (auto& tri : object.primitiveMesh.triangles) {
		for (int i = 0; i < 3; ++i) {
			tri.point[i].x += dx;
			tri.point[i].y += dy;
			tri.point[i].z += dz;
		}
	}
	
	for (auto& vertex : object.vertices) {
		vertex.x += dx;
		vertex.y += dy;
		vertex.z += dz;
	}

	object.position = object.vertices[0]; //we've moved the object, the position needs to be updated
	object.CalcCenteroid(); //we've moved the object. Centeroid has changed, need to recalculate it.
}

/*
void LinearTransformations::ApplyScaling(InputHandler* inputHandlerPtr, PrimitiveObject& object, Time* timePtr, float scalar) {
	if (inputHandlerPtr->minusInput) scalar -= 0.2f;

	float normalizedScalar = scalar * timePtr->deltaTime;

	for (auto point : object.vertices) {
		point.x *= normalizedScalar;
		point.y *= normalizedScalar;
		point.z *= normalizedScalar;
	}

	for (auto point : object.primitiveMesh.triangles) { //mark work
		point.point;
	}
*/

