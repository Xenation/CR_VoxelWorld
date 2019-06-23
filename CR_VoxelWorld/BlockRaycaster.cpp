#include "BlockRaycaster.h"

#include <XMath.h>
#include <Transform.h>
#include <Entity.h>
#include <Input.h>
#include <Debug.h>
#include "World.h"
#include "Chunk.h"



BlockRaycaster::BlockRaycaster(Entity* entity) : Component(entity) { }

BlockRaycaster::~BlockRaycaster() { }


void BlockRaycaster::onStart() {
	
}

void BlockRaycaster::onUpdate() {
	if (world == nullptr || debugEntity == nullptr) return;

	Vec3f pos;
	Voxel* voxel;
	Chunk* chunk;
	if (Input::getMouseDown(MouseButton::LEFT) && world->raycast(Ray(transform->getWorldPosition(), transform->forward()), raycastRange, pos, voxel, chunk)) {
		debugEntity->transform->setWorldPosition(pos);
		voxel->type = VoxelType::air;
		world->remeshChunk(chunk);
		//Debug::log("VOX", std::to_string(voxel->position.x) + ", " + std::to_string(voxel->position.y) + ", " + std::to_string(voxel->position.z));
		if (voxel->position.x == 0) {
			world->remeshChunk(chunk->west);
		} else if (voxel->position.x == CHUNK_SIZE - 1) {
			world->remeshChunk(chunk->east);
		}
		if (voxel->position.y == 0) {
			world->remeshChunk(chunk->bottom);
		} else if (voxel->position.y == CHUNK_SIZE - 1) {
			world->remeshChunk(chunk->top);
		}
		if (voxel->position.z == 0) {
			world->remeshChunk(chunk->south);
		} else if (voxel->position.z == CHUNK_SIZE - 1) {
			world->remeshChunk(chunk->north);
		}
	}
}
