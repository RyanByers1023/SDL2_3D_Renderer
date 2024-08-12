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

void Shader::ShadePolygon(const Polygon2D& polygon) {
    
}

//bounding box:

BoundingBox Shader::GetBoundingBox(const Polygon2D& polygon) {
    BoundingBox boundingBox;

    //calculate the minimum x coordinate (closest to origin) and minimum y coordinate
    boundingBox.minPoint.x = std::min({ polygon.vertices[0].x, polygon.vertices[1].x, polygon.vertices[2].x });
    boundingBox.minPoint.y = std::min({ polygon.vertices[0].y, polygon.vertices[1].y, polygon.vertices[2].y });
    boundingBox.maxPoint.x = std::max({ polygon.vertices[0].x, polygon.vertices[1].x, polygon.vertices[2].x });
    boundingBox.maxPoint.y = std::max({ polygon.vertices[0].y, polygon.vertices[1].y, polygon.vertices[2].y });

    //now we need to clamp the bounding box to the screen coordinates
    ClampBoundingBox(boundingBox);

    return boundingBox;
}

void Shader::ClampBoundingBox(BoundingBox& boundingBox) {//process that clamps the boundingBox to be within the screen space, and convert floats to integers for easy iteration through the bounding box
    boundingBox.minPoint.x = std::max({ 0, static_cast<int>(std::floor(boundingBox.minPoint.x)) }); //clamp between 0 and the min x val of the boundingBox (if a float, it is rounded down)
    boundingBox.minPoint.y = std::max({ 0, static_cast<int>(std::floor(boundingBox.minPoint.y)) }); //clamp between 0 and the min y val of the boundingBox (if a float, it is rounded down)
    boundingBox.maxPoint.x = std::min({ screenPtr->width - 1, static_cast<int>(std::ceil(boundingBox.maxPoint.x)) }); //clamp between screenWidth - 1 and the max x val of the boundingBox (if a float, it is rounded up)
    boundingBox.maxPoint.y = std::min({ screenPtr->height - 1, static_cast<int>(std::ceil(boundingBox.maxPoint.y)) }); //clamp between screenHeight - 1 and the max y val of the boundingBox (if a float, it is rounded up)
}

//check for intersections:

bool Shader::IntersectsPolygon(const Vec2& currPoint, const Polygon2D& polygon) { //if all of the below statements equate to true (all cross product operations >= 0) the point intersects polygon, therfore we want to draw this point.
    return GetEdgeFunctionDet(currPoint, polygon.vertices[0], polygon.vertices[1]) >= 0 && //edge from v0 to v1
        GetEdgeFunctionDet(currPoint, polygon.vertices[1], polygon.vertices[2]) >= 0 && //edge from v1 to v2
        GetEdgeFunctionDet(currPoint, polygon.vertices[2], polygon.vertices[0]) >= 0;   //edge from v2 to v0
}

float Shader::GetEdgeFunctionDet(const Vec2& currPoint, const Vec2& v0, const Vec2& v1) { //Computes cross product between edge v0 -> v1 with respect to currPoint
    float edgeFunctionValue = (v1.x - v0.x) * (currPoint.y - v0.y) - (v1.y - v0.y) * (currPoint.x - v0.x);
    return edgeFunctionValue; //return value for above evaluation in IntersectsTriangle
}

Vec3 Shader::ClampColor(const Vec3& color) {
    return Vec3(std::clamp(color.x, 0.0f, 1.0f),
                std::clamp(color.y, 0.0f, 1.0f),
                std::clamp(color.z, 0.0f, 1.0f));
}

Vec3 Shader::CalculateVertexColor(const Vec3& vertexPos, const Vec3& vertexNormal, const Light& light, const Vec3& cameraPos, const Material& material) {
    Vec3 ambientColor = light.ambient * material.ambient;

    Vec3 lightDir = (light.position - vertexPos).Normalize();
    float diffuseFactor = std::max(vertexNormal.Dot(lightDir), 0.0f);
    Vec3 diffuseColor = light.diffuse * diffuseFactor * material.diffuse;

    Vec3 viewDir = (cameraPos - vertexPos).Normalize();
    Vec3 reflectDir = (vertexNormal * 2.0f * vertexNormal.Dot(lightDir) - lightDir).Normalize();
    float specularFactor = std::pow(std::max(viewDir.Dot(reflectDir), 0.0f), material.shininess);
    Vec3 specularColor = light.specular * specularFactor * material.specular;

    Vec3 finalColor = ambientColor + diffuseColor + specularColor;
    return ClampColor(finalColor);
}

