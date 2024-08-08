#include "Material.h"

void Material::ClampColors() {
    ambient = Clamp(ambient);
    diffuse = Clamp(diffuse);
    specular = Clamp(specular);
}

Vec3 Material::Clamp(const Vec3& color) {
    return Vec3(std::clamp(color.x, 0.0f, 1.0f),
                std::clamp(color.y, 0.0f, 1.0f),
                std::clamp(color.z, 0.0f, 1.0f));
}