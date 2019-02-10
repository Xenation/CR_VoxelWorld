#pragma once
#include <XMath.h>
class Chunk;
class WorldGenerator {
public:
	WorldGenerator(unsigned int seed);
	~WorldGenerator();

	Chunk* generateChunk(Vec3i chkPos);

private:
	unsigned int seed;
};

