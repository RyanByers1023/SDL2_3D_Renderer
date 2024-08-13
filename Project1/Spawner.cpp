#include "Spawner.h"

void SpawnCube(std::unique_ptr<WorldObjects>& worldObjectsPtr, std::string name, Vec3 position, int size) {
	Cube* cube = new Cube(name, position, size); //create a 100px x 100px x 100px cube in the center of the screen. parameters: (Screen object, position to spawn object (Vec3), size of cube (int in pixels)
	auto it = worldObjectsPtr->objects.find(name);
	if (it != worldObjectsPtr->objects.end()) {
		std::cout << "There already exists an object with that name. Please name the object you wish to create something different.\n\n" << std::endl;
		return;
	}
	worldObjectsPtr->objects.emplace(name, cube);
}