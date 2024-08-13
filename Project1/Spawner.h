#pragma once
#include "Cube.h"
#include "WorldObjects.h"
#include <string>
#include <iostream>

void SpawnCube(std::unique_ptr<WorldObjects>& worldObjectsPtr, std::string name, Vec3 position = { 40.0f, 20.0f, 180.0f }, int size = 100);
	
