#include "RendererHelperFunctions.h"

//calculate the dot product between the normal, the camera and a triangle that is on the same plane.
//if this outputs a positive value, then this face is facing the camera, render it
bool ShouldRender(const Triangle3D tri, Vec3 normal, Vec3 cameraLocation) {	
	return (normal.x * (tri.point[0].x - cameraLocation.x) +
		    normal.y * (tri.point[0].y - cameraLocation.y) +
		    normal.z * (tri.point[0].z - cameraLocation.z)) < 0.0f;
}

//determines whether or not we need to draw the triangle based on perspective (eg. we don't want to render the back side of the triangle if we are viewing the front)...
Vec3 CalculateNormalVector(const Triangle3D tri) {	
	//this angle is useful to determine if a certain triangle should be visible to the camera or not
	Vec3 normal, lineA, lineB;

	//calculate line A and line B
	lineA.x = tri.point[1].x - tri.point[0].x; lineB.x = tri.point[2].x - tri.point[0].x;
	lineA.y = tri.point[1].y - tri.point[0].y; lineB.y = tri.point[2].y - tri.point[0].y;
	lineA.z = tri.point[1].z - tri.point[0].z; lineB.z = tri.point[2].z - tri.point[0].z;

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