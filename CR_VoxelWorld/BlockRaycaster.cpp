#include "BlockRaycaster.h"

#include <XMath.h>
#include <Transform.h>
#include <Entity.h>
#include <Input.h>
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
	if (Input::mouseLeftPressed && world->raycast(Ray(transform->getPosition(), transform->forward()), raycastRange, pos, voxel, chunk)) {
		debugEntity->transform->setPosition(pos);
		voxel->type = VoxelType::air;
		world->remeshChunk(chunk);
	}
}
