#pragma once
#include "PrimitiveObject.h"
#include <string>
#include <unordered_map>

class WorldObjects {
public:
	std::unordered_map<std::string, PrimitiveObject> objects;
};