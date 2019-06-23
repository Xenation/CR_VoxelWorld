#include "WorldRigidbody.h"

#include <bullet/btBulletCollisionCommon.h>
#include <CompoundCollider.h>
#include <ConcaveMeshCollider.h>
#include <Engine.h>
#include <PhysicsWorld.h>
#include <Debug.h>
#include "World.h"
#include "Chunk.h"



WorldRigidbody::WorldRigidbody(Entity* entity) : Rigidbody(entity, new CompoundCollider()) {}

WorldRigidbody::~WorldRigidbody() {}


void WorldRigidbody::onUpdate() {
	Engine::physicsWorld->unregisterRigidbody(this);
	for (std::pair<Vec3i, Chunk*> pair : world->chunks) {
		if (pair.second->collider->_parent != nullptr || !pair.second->meshed || pair.second->opaqueMesh == nullptr) continue;
		((CompoundCollider*) collider)->addCollider(pair.second->collider, Vec3f(pair.second->position.x * CHUNK_SIZE, pair.second->position.y * CHUNK_SIZE, pair.second->position.z * CHUNK_SIZE), Quaternion::identity);
	}
	Engine::physicsWorld->registerRigidbody(this);
}
