#include "Spawner.h"

void SpawnCube(std::shared_ptr<WorldObjects> worldObjectsPtr, const std::string& name, const Vec3& position, int size) {
    if (!worldObjectsPtr) {
        std::cerr << "worldObjectsPtr is null." << std::endl;
        return;
    }

    auto it = worldObjectsPtr->objects.find(name);
    if (it != worldObjectsPtr->objects.end()) {
        std::cout << "Object with that name already exists." << std::endl;
        return;
    }

    //ensure size is valid
    if (size <= 0) {
        std::cerr << "Invalid size for the cube." << std::endl;
        return;
    }

    // Create the cube and add it to the worldObjects
    worldObjectsPtr->objects[name] = std::make_shared<Cube>(position, size);
}