#include "ObjParser.h"

//this will be the main function that returns the entire comepleted mesh
primitiveMesh GetMesh(){

}

bool OpenObjFile(string filename){ //this parser assumes the obj file only contains vertex information (will crash otherwise, i should probably handle this)
    std::ifstream objFile (filename);

    if(objFile.is_open()){ //file was found in program main directory
        GetLine()
    }
    else{ //file was not found in program main directory
        std::cerr<< "Failed to open object file. File not found. Did you enter the correct .obj File name?"<< std::endl;
        return false;
    }    
    return true;
}

bool GetLines(const std::ifstream& objFile, string& line){
    if(getline(objFile, line)){
        return true;
    }
    else{
        return false;
    }
}

Vec3 GetVertex(std::string line){ 
    char vertexCheck;

    while(GetLines()){ //the current line from objFile is now = to line
            std::istringstream vertexLine(line);
            vertexLine >> vertexCheck;
            if(vertexCheck == 'v'){ //this is a line that is going to give me vertex information
                float x, y, z;
                vertexLine >> x >> y >> z;
                //create a new vec3 object and intialize with these values
                Vec3 vertex;
                vertex.x = x;
                vertex.y = y;
                vertex.z = z;
                //we now have extracted a vertex from the obj file that is to be a part of the mesh
            }
    }
}