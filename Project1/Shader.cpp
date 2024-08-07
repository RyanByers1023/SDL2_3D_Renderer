#include "Shader.h"
//want to implement "gouraud" shading.
//pretty antiquated: paper was written by gouraud in 1971, but visuals are acceptable for this project imo
//could implement a more advanced shading algo, but i personally dont think it is worth it
//wiki: https://en.wikipedia.org/wiki/Gouraud_shading

//process:
//1) Get face normals (should already have this)
//2) Get vertex normals (average of face normals of all adjacent faces to vertex)
//3) Calculate light intensity relative to ambient and directional light of light sources at vertex normals
//4) draw line within screen-space 2-D poly mesh and --- choose: (linearly) / (non-linearly) interpolate between light intensities using a shaded line to fill polygon
//5) repeat step 4 until face is shaded

//note: this algorithm benefits visually from an increased poly count -- Diminishing returns as poly count increases past a certain point

Shader::Shader(Screen* screenPtr) {
	this->screenPtr = screenPtr;
}

void Shader::ShadePolygon(const Polygon2D& polygon) {
    
}

