#pragma once
#include "Cube.h"
#include "WorldObjects.h"
#include <string>
#include <iostream>

void SpawnCube(WorldObjects* worldObjectsPtr, std::string name, vec3 position = {40.0f, 20.0f, 90.0f}, int size = 100);
