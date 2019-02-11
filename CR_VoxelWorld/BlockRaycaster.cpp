#include "BlockRaycaster.h"

#include <XMath.h>
#include <Transform.h>
#include <Entity.h>
#include <Input.h>
#include "World.h"



BlockRaycaster::BlockRaycaster(Entity* entity) : Component(entity) { }

BlockRaycaster::~BlockRaycaster() { }


void BlockRaycaster::onStart() {
	
}

void BlockRaycaster::onUpdate() {
	if (world == nullptr || debugEntity == nullptr) return;

	Vec3f pos;
	if (Input::mouseLeftPressed && world->raycast(Ray(transform->getPosition(), transform->forward()), raycastRange, pos)) {
		debugEntity->transform->setPosition(pos);
	}
}
