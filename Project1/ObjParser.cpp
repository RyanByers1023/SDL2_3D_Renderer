#include "ObjParser.h"

ObjFile::ObjFile(std::string fileName){
    GetMesh(fileName);
}

//this will be the main function that returns the entire completed mesh
void ObjFile::GetMesh(std::string fileName){
    std::ifstream objFile;
    if(OpenObjFile(fileName, objFile)){ //verify file exists
        IterateThroughObjFile(objFile); //populate the mesh
    }
}

bool ObjFile::OpenObjFile(std::string fileName, std::ifstream& objFile){ //this parser assumes the obj file only contains vertex information (will crash otherwise, i should probably handle this)
    objFile.open(fileName);
    if(!objFile.is_open()){ //.obj file was not found in program main directory, return false.
        std::cerr<< "Failed to open object file. File not found. Did you enter the correct .obj File name?"<< std::endl;
        return false;
    }
    return true; //[filename].obj exists
}

void ObjFile::IterateThroughObjFile(std::ifstream& objFile){
    std::string line;
    Triangle3D newTriangle;

    while(std::getline(objFile, line)){
        std::istringstream lineStream(line);
        char prefix; //first character of a line defining a vertex will be 'v'
        lineStream >> prefix; //stream first character into vertexCheck

        if(prefix == 'v'){ //definition for a vertex here...
            //parse the vertex
            newTriangle = CreateTriangle(lineStream); //next 3 rows are vertices
            this->newMesh.triangles.push_back(newTriangle); //store newTriangle as a part of the mesh
            //note: obj files store vertices counterclockwise
            //this is important info for the calculation of face normals
        }  
    }
}

//initialize a triangle
Triangle3D ObjFile::CreateTriangle(std::istringstream& lineStream){
    Triangle3D newTriangle;
    for(int i = 0; i < 3; ++i){ //populate the triangle with the next three vertices
        Vec3 newVertex = CreateVertex(lineStream); //create a new Vec3 object to store the vertex
        newTriangle.point[i] = newVertex; //populate vertex i of the triangle with the new vertex
    }
    return newTriangle;
}

//intitialize a vertex
Vec3 ObjFile::CreateVertex(std::istringstream& lineStream){ 
    Vec3 newVertex;
    lineStream >> newVertex.x >> newVertex.y >> newVertex.z;

    return newVertex;
}