#pragma once
#include <Rigidbody.h>

class btCompoundShape;
class World;
class Chunk;

class WorldRigidbody : public Rigidbody {
public:
	World* world;

	WorldRigidbody(Entity* entity);
	~WorldRigidbody();

	void addChunk(Chunk* chunk);
	void removeChunk(Chunk* chunk);
};

