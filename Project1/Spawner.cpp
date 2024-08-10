#include "Spawner.h"

void Spawner::SpawnCube(std::shared_ptr<WorldObjects> worldObjectsPtr, const std::string& name, const Vec3& position, const int& size) {
	//create a 100px x 100px x 100px cube in the center of the screen (as long as position and size parameters haven't been passed)
	Cube cube(position, size, name); 
	auto it = worldObjectsPtr->objects.find(name);
	if (it != worldObjectsPtr->objects.end()) {
		std::cout << "There already exists an object with that name. Please name the object you wish to create something different.\n\n" << std::endl;
		return;
	}
	worldObjectsPtr->objects[name] = cube;
}