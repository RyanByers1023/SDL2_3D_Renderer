#pragma once
#include <vector>
#include <string>
#include "PrimitiveObject.h"
#include "Cube.h"
#include "Screen.h"
#include "Renderer.h"

void SpawnCube(Renderer& renderer, std::string name, vec3 position = {40.0f, 20.0f, 90.0f}, int size = 100);
