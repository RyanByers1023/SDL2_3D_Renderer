#include "Shader.h"
//want to implement "gouraud" shading.
//pretty antiquated: paper was written by gouraud in 1971, but visuals are acceptable for this project imo
//could implement a more advanced shading algo, but i personally dont think it is worth it
//wiki: https://en.wikipedia.org/wiki/Gouraud_shading

//note: this algorithm benefits visually from an increased poly count -- Diminishing returns as poly count increases past a certain point

Shader::Shader(Screen* screenPtr) {
	this->screenPtr = screenPtr;
}

void Shader::ShadePolygon(const Polygon2D& polygon) {
    
}

