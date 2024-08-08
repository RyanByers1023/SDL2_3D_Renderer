#include "RendererHelperFunctions.h"

//if this outputs a positive value, then this face is facing the camera, the object is facing the camera, it needs to be rendered (eg. don't render the back side of the triangle if we are viewing the front)...
//process is known as "back face culling"
bool ShouldRender(const Triangle3D& tri, const Vec3& triNormal, const Vec3& cameraLocation) {	
	return (triNormal.x * (tri.vertices[0].x - cameraLocation.x) +
			triNormal.y * (tri.vertices[0].y - cameraLocation.y) +
			triNormal.z * (tri.vertices[0].z - cameraLocation.z)) < 0.0f;
}

Vec3 CalculateNormalVector(const Triangle3D& tri) {	
	Vec3 normal, lineA, lineB;

	//calculate line A and line B
	lineA.x = tri.vertices[1].x - tri.vertices[0].x; lineB.x = tri.vertices[2].x - tri.vertices[0].x;
	lineA.y = tri.vertices[1].y - tri.vertices[0].y; lineB.y = tri.vertices[2].y - tri.vertices[0].y;
	lineA.z = tri.vertices[1].z - tri.vertices[0].z; lineB.z = tri.vertices[2].z - tri.vertices[0].z;

	//Calculate the cross product of the two vectors A and B. Gives the normal vector
	normal.x = lineA.y * lineB.z - lineA.z * lineB.y;
	normal.y = lineA.z * lineB.x - lineA.x * lineB.z;
	normal.z = lineA.x * lineB.y - lineA.y * lineB.x;

	//normalize the normal vector -- need x^2, y^2, and z^2 from the normal vector
	float xComponentSqaured = normal.x * normal.x;
	float yComponentSquared = normal.y * normal.y;
	float zComponentSquared = normal.z * normal.z;

	//use the distance formula to determine magnitude
	float magnitude = sqrtf(xComponentSqaured + yComponentSquared + zComponentSquared);

	//use magnitude of normal vector to create the unit normal vector
	normal.x /= magnitude; normal.y /= magnitude; normal.z /= magnitude;

	return normal;
}