#include "Spawner.h"

void SpawnCube(Renderer& renderer, std::string name, vec3 position, int size) {
	Cube cube(position, size); //create a 100px x 100px x 100px cube in the center of the screen. parameters: (Screen object, position to spawn object (vec3), size of cube (int in pixels)
	auto it = renderer.worldObjects.find(name);
	if (it != renderer.worldObjects.end()) {
		std::cout << "There already exists an object with that name. Please name the object you wish to create something different.\n\n" << std::endl;
		return;
	}
	renderer.worldObjects[name] = cube;
}