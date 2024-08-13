#pragma once
#include "Cube.h"
#include "WorldObjects.h"
#include <string>
#include <iostream>
#include <memory>

class Spawner {
public:
	void SpawnCube(const std::unique_ptr<WorldObjects>& worldObjectsPtr, const std::string& name, const Vec3& position = { 40.0f, 20.0f, 180.0f }, int size = 100);
};

	
