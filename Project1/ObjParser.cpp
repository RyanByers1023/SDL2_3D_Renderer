#include "ObjParser.h"

//this will be the main function that returns the entire completed mesh
primitiveMesh GetMesh(std::string fileName){
    std::vector<Triangle3D> mesh;
    std::ifstream objFile;
    if(OpenObjFile(fileName, objFile)){
        //objFile should point to the correct file at this point in time
        //want to enter into the main getline loop that is used to parse the file...
        IterateThroughObjFile(objFile, mesh); //do this here. This will also populate the mesh
    }
    return mesh; //return the complete mesh
}

bool OpenObjFile(std::string fileName, std::ifstream& objFile){ //this parser assumes the obj file only contains vertex information (will crash otherwise, i should probably handle this)
    if(!objFile.is_open()){ //.obj file was not found in program main directory, return false.
        std::cerr<< "Failed to open object file. File not found. Did you enter the correct .obj File name?"<< std::endl;
        return false;
    }
    return true; //[filename].obj exists, and we have opened it, return true
}

void IterateThroughObjFile(const std::ifstream& objFile, std::vector<Triangle3D> mesh){
    while(std::getline(objFile, line)){
        std::istringstream vertexStream(line);
        char vertexCheck; //first character of a line defining a vertex will be 'v'
        vertexStream >> vertexCheck; //stream the first character of the line into vertexCheck
        if(vertexCheck == 'v'){ //there is a definition for a vertex here...
            Triangle3D newTriangle;
            GetTriangle(vertexStream, newTriangle); //create a triangle     
        }
        mesh.push_back(newTriangle); //store our new triangle in the mesh
    }
}

//intitialize a vertex
Vec3 GetVertex(std::istringstream& vertexStream, Vec3 newVertex){ 
    float x, y, z;
    vertexStream >> x >> y >> z;

    newVertex.x = x;
    newVertex.y = y;
    newVertex.z = z;
}

//initialize a triangle
Vec3 GetTriangle(std::istringstream& vertexStream){
    Triangle3D newTriangle;
    for(int i = 0; i < 3; ++i){ //populate the triangle with our three new vertices
        Vec3 newVertex; //create a new Vec3 object to store the newly found vertex
        GetVertex(std::istringstream& vertexStream, newVertex); //now the new vertex from the .obj file is stored in newVertex
        newTriangle.point[i] = newVertex; //populate vertex i of the triangle with the new vertex
    }
}