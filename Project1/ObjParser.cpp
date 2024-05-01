#include "ObjParser.h"

bool OpenObjFile(string filename){ //this parser assumes the obj file only contains vertex information
    std::ifstream objFile (filename);
    if(!objFile.is_open()){
        std::cerr<< "Failed to open file. Did you enter the correct objFile name?"<< std::endl;
        return false;
    }
    std::istringstream
    
    
    return true;
}