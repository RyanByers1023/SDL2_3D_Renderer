#include "ObjParser.h"

ObjFile::ObjFile(std::string fileName){
    this->mesh = GetMesh(fileName);
}

//this will be the main function that returns the entire completed mesh
primitiveMesh ObjFile::GetMesh(std::string fileName){
    std::ifstream objFile;
    if(OpenObjFile(fileName, objFile)){
        //objFile should point to the correct file at this point in time
        //want to enter into the main getline loop that is used to parse the file...
        IterateThroughObjFile(objFile, mesh); //do this here. This will populate the mesh
    }
    return mesh; //return the complete mesh
}

bool ObjFile::OpenObjFile(std::string fileName, std::ifstream& objFile){ //this parser assumes the obj file only contains vertex information (will crash otherwise, i should probably handle this)
    objFile.open(filename);
    if(!objFile.is_open()){ //.obj file was not found in program main directory, return false.
        std::cerr<< "Failed to open object file. File not found. Did you enter the correct .obj File name?"<< std::endl;
        return false;
    }
    return true; //[filename].obj exists, and we have opened it, return true
}

void ObjFile::IterateThroughObjFile(const std::ifstream& objFile){
    std::string line;

    while(std::getline(objFile, line)){
        std::istringstream vertexStream(line);
        char vertexCheck; //first character of a line defining a vertex will be 'v'
        vertexStream >> vertexCheck; //stream the first character of the line into vertexCheck
        if(vertexCheck == 'v'){ //there is a definition for a vertex here...
            Triangle3D newTriangle = CreateTriangle(vertexStream, newTriangle); //the next three rows will be vertices for a triangle, create a new triangle with them 
        }
        mesh.push_back(newTriangle); //store our new triangle in the mesh
    }
}

//initialize a triangle
Triangle3D CreateTriangle(std::istringstream& vertexStream){
    Triangle3D newTriangle;
    for(int i = 0; i < 3; ++i){ //populate the triangle with the next three vertices
        Vec3 newVertex = CreateVertex(std::istringstream& vertexStream, newVertex); //create a new Vec3 object to store the vertex
        newTriangle.point[i] = newVertex; //populate vertex i of the triangle with the new vertex
    }
    return newTriangle;
}

//intitialize a vertex
Vec3 ObjFile::CreateVertex(std::istringstream& vertexStream, Vec3 newVertex){ 
    float x, y, z;
    vertexStream >> x >> y >> z;

    newVertex.x = x;
    newVertex.y = y;
    newVertex.z = z;

    return newVertex;
}