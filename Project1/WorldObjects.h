#pragma once
#include "PrimitiveObject.h"
#include <string>
#include <unordered_map>
#include <memory>

class WorldObjects {
public:
	std::unordered_map<std::string, PrimitiveObject*> objects;
};