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


void WorldRigidbody::addChunk(Chunk* chunk) {
	Engine::physicsWorld->unregisterRigidbody(this);
	((CompoundCollider*) collider)->addCollider(chunk->collider, Vec3f(chunk->position.x * CHUNK_SIZE, chunk->position.y * CHUNK_SIZE, chunk->position.z * CHUNK_SIZE), Quaternion::identity);
	Engine::physicsWorld->registerRigidbody(this);
}

void WorldRigidbody::removeChunk(Chunk* chunk) {
	Engine::physicsWorld->unregisterRigidbody(this);
	((CompoundCollider*) collider)->removeCollider(chunk->collider);
	Engine::physicsWorld->registerRigidbody(this);
}
