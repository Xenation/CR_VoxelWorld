#pragma once
#include <XMath.h>
class Chunk;
class World;
class WorldGenerator {
public:
	World* world;

	WorldGenerator(World* world, unsigned int seed);
	~WorldGenerator();

	Chunk* generateChunk(Vec3i chkPos);

private:
	unsigned int seed;

	float densityAt(Vec3f worldPos);
};

