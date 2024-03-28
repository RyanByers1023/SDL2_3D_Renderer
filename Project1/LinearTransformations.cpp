#include "LinearTransformations.h"

void LinearTransformations::ApplyRotation(PrimitiveObject& object) { //rotates radiansToRotate/sec when corresponding input is held down
	float xRadians = 0, yRadians = 0, zRadians = 0;
	float radiansToRotate = 1;

	vec3 centeroid = object.GetCenteroid();

	if (object.screenPtr->leftInput) xRadians = radiansToRotate * object.screenPtr->deltaTime;
	if (object.screenPtr->rightInput) xRadians = radiansToRotate * object.screenPtr->deltaTime;
	if (object.screenPtr->upInput) yRadians = radiansToRotate * object.screenPtr->deltaTime;
	if (object.screenPtr->downInput) yRadians = radiansToRotate * object.screenPtr->deltaTime;

	for (auto& tri : object.primitiveMesh.triangles) {
		for (int i = 0; i < 3; ++i) {
			tri.p[i].x -= centeroid.x;
			tri.p[i].y -= centeroid.y;
			tri.p[i].z -= centeroid.z;
		}
		
		RotationMatrix rotationMatrix(xRadians, yRadians, zRadians);

		for (int i = 0; i < 3; i++) {
			tri.p[i] *= rotationMatrix;
		}

		for (int i = 0; i < 3; ++i) {
			tri.p[i].x += centeroid.x;
			tri.p[i].y += centeroid.y;
			tri.p[i].z += centeroid.z;
		}
	}
}

/*void LinearTransformations::ApplyTransformation(PrimitiveObject& object, vec3 dp) {

}

void LinearTransformations::ApplyScaling(PrimitiveObject& object, float scalar) {

}
*/