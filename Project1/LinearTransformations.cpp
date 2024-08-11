#include "LinearTransformations.h"

void LinearTransformations::ApplyRotation(const std::unique_ptr<InputHandler>& inputHandlerPtr, const std::unqiue_ptr<Time>& timePtr, PrimitiveObject& object) { //rotates radiansToRotate/sec when corresponding input is held down
	float xRadians = 0, yRadians = 0, zRadians = 0;
	float radiansToRotate = 1;

	
	Vec3 centeroid = object.centeroid;

	if (inputHandlerPtr->leftInput) yRadians = radiansToRotate * timePtr->deltaTime;
	if (inputHandlerPtr->rightInput) yRadians = -radiansToRotate * timePtr->deltaTime;
	if (inputHandlerPtr->upInput) xRadians = radiansToRotate * timePtr->deltaTime;
	if (inputHandlerPtr->downInput) xRadians = -radiansToRotate * timePtr->deltaTime;

	for (auto& tri : object.primitiveMesh.triangles) { //normalization
		for (int i = 0; i < 3; ++i) {
			tri.vertices[i].x -= centeroid.x;
			tri.vertices[i].y -= centeroid.y;
			tri.vertices[i].z -= centeroid.z;
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
			tri.vertices[i] *= rotationMatrix;
		}

		for (int i = 0; i < 3; ++i) { //revert normalization operation
			tri.vertices[i].x += centeroid.x;
			tri.vertices[i].y += centeroid.y;
			tri.vertices[i].z += centeroid.z;
		}
	}
}

void LinearTransformations::ApplyTransformation(InputHandler* inputHandlerPtr, Time* timePtr, PrimitiveObject& object) {
	float dx = 0, dy = 0, dz = 0;

	float distanceToMove = 80.0f;

	
	if (inputHandlerPtr->wInput) dy = distanceToMove * timePtr->deltaTime;
	if (inputHandlerPtr->aInput) dx = -distanceToMove * timePtr->deltaTime;
	if (inputHandlerPtr->sInput) dy = -distanceToMove * timePtr->deltaTime;
	if (inputHandlerPtr->dInput) dx = distanceToMove * timePtr->deltaTime;
	if (inputHandlerPtr->zInput) dz = distanceToMove * timePtr->deltaTime;
	if (inputHandlerPtr->xInput) dz = -distanceToMove * timePtr->deltaTime;
	

	for (auto& tri : object.primitiveMesh.triangles) {
		for (int i = 0; i < 3; ++i) {
			tri.vertices[i].x += dx;
			tri.vertices[i].y += dy;
			tri.vertices[i].z += dz;
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

