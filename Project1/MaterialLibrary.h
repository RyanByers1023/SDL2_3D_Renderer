#pragma once
#include "Material.h"

class MaterialLibrary {
	Material gold;
	Material bronze;
	Material plastic;

    //pre-defined materials for objects initialized without materials assigned
    //--materials created by ChatGPT
    MaterialLibrary()
        : gold(
            Vec3(1.0f, 0.843f, 0.0f),
            Vec3(1.0f, 0.843f, 0.0f),
            Vec3(0.5f, 0.5f, 0.5f),
            32.0f),
        plastic(
            Vec3(0.1f, 0.1f, 0.1f),
            Vec3(0.6f, 0.6f, 0.6f),
            Vec3(0.3f, 0.3f, 0.3f),
            10.0f),
        bronze(
            Vec3(0.2125f, 0.1275f, 0.054f),
            Vec3(0.714f, 0.4284f, 0.18144f),
            Vec3(0.393548f, 0.271906f, 0.166721f),
            25.6f) {}
};