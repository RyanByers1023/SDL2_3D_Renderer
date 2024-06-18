#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>

#include "Vec3.h"

class ObjFile {
public:
    ObjFile(std::string fileName);
private:
    void GetMesh(std::string fileName);
    bool OpenObjFile(std::string fileName, std::ifstream& objFile);
    void IterateThroughObjFile(std::ifstream& objFile);
    Triangle3D CreateTriangle(std::istringstream& vertexStream);
    Vec3 CreateVertex(std::istringstream&);
    mesh newMesh;
};