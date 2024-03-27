#pragma once
#include <vector>
#include "screen.h"
#include "vec3.h"
#include "Line.h"
#include "Matrix.h"

class PrimitiveObject{
    //protected methods
    protected:
        void Draw(); //this will draw/project the primitive 3-D shape when provided with an acceptable mesh (counter-clockwise ordered vertices)
        void CalcCenteroid(); //adds all vertices together and divides by number of vertices. Centeroid stored as a vec3
        //linear transformation methods (meaning, these do not change the object)
        void Rotate(); //rotates all of the vertices. Utilizes basic rotation matrix to accomplish. (kind of, need to be more explcit and use the 4x4Matrix)
        void Translate(); //changes the position of the primitiveObject.
        void Scale(); //changes the size of the primitiveObject. Retain original dimension ratio.
        //getters
        vec3 GetPosition(); //will return the bottom left vertice (first vertex in mesh)
        vec3 GetCenteroid(); //will return the center point of the object
        
    //protected attributes
        Screen* screenPtr; //access to screen via a pointer value.
        vec3 centeroid; //center coordinate of the object.
        vec3 position; //This = the north face, bottom left vertice. (first vertex in mesh)
        std::vector<vec3> vertices; //stores all of the vertices (corner points) of the cube. Helpful in centeroid calculation.
        mesh primitiveMesh; //the mesh of the primitive 3-D object is stored here. Made up entirely of triangle objects. Triangle objects store 3 coordinates in 3 space. these are stored as vec3s. vec3s are float(x, y, z)



}

