#include "World.h"

#include <Entity.h>
#include "WorldRenderer.h"
#include "Chunk.h"



World::World(Entity* entity) : Component(entity), generator(8) {}

World::~World() {}


void World::onStart() {
	// TestGen
	for (int z = 0; z < 4; z++) {
		for (int x = 0; x < 4; x++) {
			Vec3i chkPos = Vec3i(x, 0, z);
			Chunk* chunk = generator.generateChunk(chkPos);
			chunks[chkPos] = chunk;
			chunk->generateMesh();
		}
	}

	WorldRenderer* renderer = entity->addComponent<WorldRenderer>();
	renderer->world = this;
}

void World::onDestroy() {
	for (std::pair<Vec3i, Chunk*> pair : chunks) {
		delete pair.second;
	}
}
