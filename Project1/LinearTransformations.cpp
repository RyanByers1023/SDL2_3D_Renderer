#include "LinearTransformations.h"

void LinearTransformations::ApplyRotation(PrimitiveObject& object) { //rotates radiansToRotate/sec when corresponding input is held down
	float xRadians = 0, yRadians = 0, zRadians = 0;
	float radiansToRotate = 1;

	vec3 centeroid = object.centeroid;

	//if (object.screenPtr->leftInput) yRadians = radiansToRotate * object.screenPtr->deltaTime;
	//if (object.screenPtr->rightInput) yRadians = -radiansToRotate * object.screenPtr->deltaTime; //i need to make an input handler for this. Dont want to use screenPtr anymore
	//if (object.screenPtr->upInput) xRadians = -radiansToRotate * object.screenPtr->deltaTime;
	//if (object.screenPtr->downInput) xRadians = radiansToRotate * object.screenPtr->deltaTime;

	for (auto& tri : object.primitiveMesh.triangles) { //normalization
		for (int i = 0; i < 3; ++i) {
			tri.p[i].x -= centeroid.x;
			tri.p[i].y -= centeroid.y;
			tri.p[i].z -= centeroid.z;
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
			tri.p[i] *= rotationMatrix;
		}

		for (int i = 0; i < 3; ++i) { //revert normalization operation
			tri.p[i].x += centeroid.x;
			tri.p[i].y += centeroid.y;
			tri.p[i].z += centeroid.z;
		}
	}
}

void LinearTransformations::ApplyTransformation(PrimitiveObject& object) {
	float dx = 0, dy = 0, dz = 0;

	float distanceToMove = 80.0f;

	/*
	if (object.screenPtr->wInput) dy = -distanceToMove * object.screenPtr->deltaTime; //up
	if (object.screenPtr->aInput) dx = -distanceToMove * object.screenPtr->deltaTime; //left
	if (object.screenPtr->sInput) dy = distanceToMove * object.screenPtr->deltaTime; //down
	if (object.screenPtr->dInput) dx = distanceToMove * object.screenPtr->deltaTime; //right 
	if (object.screenPtr->zInput) dz = distanceToMove * object.screenPtr->deltaTime; //doesnt work
	if (object.screenPtr->xInput) dz = -distanceToMove * object.screenPtr->deltaTime; //doesnt work
	*/

	for (auto& tri : object.primitiveMesh.triangles) {
		for (int i = 0; i < 3; ++i) {
			tri.p[i].x += dx;
			tri.p[i].y += dy;
			tri.p[i].z += dz;
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

/*void LinearTransformations::ApplyScaling(PrimitiveObject& object, float scalar) {

}
*/