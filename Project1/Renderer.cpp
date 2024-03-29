#include "Renderer.h"

Renderer::Renderer(Screen* screenPtr, ProjectionMatrix& projMatrix) {
	this->screenPtr = screenPtr;
	this->projMatrix = projMatrix;
}

void Renderer::Render() { //may eventually change this to render a list of items. Only renders one item at a time for now, which is okay

	for (auto& object : worldObjects) {
		for (auto& tri : object.primitiveMesh.triangles) {
			triangle projectedTriangle;

			for (int i = 0; i < 3; i++) {
				projectedTriangle.p[i] = tri.p[i] * projMatrix;
			}

			projectedTriangle.p[0].x += 1.0f; projectedTriangle.p[0].y += 1.0f;
			projectedTriangle.p[1].x += 1.0f; projectedTriangle.p[1].y += 1.0f;
			projectedTriangle.p[2].x += 1.0f; projectedTriangle.p[2].y += 1.0f;

			float halfScreenWidth = static_cast<float>(screenPtr->width) * 0.5f;
			float halfScreenHeight = static_cast<float>(screenPtr->height) * 0.5f;

			projectedTriangle.p[0].x *= halfScreenWidth;
			projectedTriangle.p[0].y *= halfScreenHeight;
			projectedTriangle.p[1].x *= halfScreenWidth;
			projectedTriangle.p[1].y *= halfScreenHeight;
			projectedTriangle.p[2].x *= halfScreenWidth;
			projectedTriangle.p[2].y *= halfScreenHeight;

			float x1 = projectedTriangle.p[0].x;
			float y1 = projectedTriangle.p[0].y;

			float x2 = projectedTriangle.p[1].x;
			float y2 = projectedTriangle.p[1].y;

			float x3 = projectedTriangle.p[2].x;
			float y3 = projectedTriangle.p[2].y;

			Line line1(*screenPtr, x1, y1, x2, y2); //first line of triangle (side a)
			line1.Draw();

			Line line2(*screenPtr, x2, y2, x3, y3); //second line of triangle (side b)
			line2.Draw();

			Line line3(*screenPtr, x3, y3, x1, y1); //third line of triangle (side c) -- this is the hypotenuse
			line3.Draw();
		}
	}

	/* move below code to its own function
	LinearTransformations transform;

	if (screen.leftInput || screen.rightInput || screen.upInput || screen.downInput) transform.ApplyRotation(object); //FIX-ME--maybe best to include this in its own method later on...
	if (screen.wInput || screen.aInput || screen.sInput || screen.dInput || screen.zInput || screen.xInput) transform.ApplyTransformation(object);
	*/
}
