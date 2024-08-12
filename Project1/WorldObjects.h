#pragma once
#include "PrimitiveObject.h"
#include <string>
#include <unordered_map>
#include <memory>

class WorldObjects {
public:
	//FIX-ME: worldObjectsPtr is NULL when trying to instantiate controller
	std::unordered_map<std::string, std::shared_ptr<PrimitiveObject>> objects;
};