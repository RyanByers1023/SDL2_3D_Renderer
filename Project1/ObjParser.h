#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>

#include "Vec3.h"

class ObjFile{
public:
    ObjFile(string fileName);
private:
    mesh GetMesh(std::string fileName);
    bool OpenObjFile(string fileName);
    void IterateThroughObjFile(const std::ifstream& objFile);
    Triangle3D CreateTriangle(std::istringstream& vertexStream);
    Vec3 CreateVertex(std::istringstream& vertexStream, Vec3 newVertex)
    std::vector<Triangle3D> mesh;
}

