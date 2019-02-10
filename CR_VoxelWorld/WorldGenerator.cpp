#include "WorldGenerator.h"

#include <Perlin.h>
#include "Chunk.h"



WorldGenerator::WorldGenerator(unsigned int seed) : seed(seed) {}

WorldGenerator::~WorldGenerator() {}

Chunk* WorldGenerator::generateChunk(Vec3i chkPos) {
	Chunk* chunk = new Chunk(chkPos);
	for (int y = 0; y < CHUNK_SIZE; y++) {
		for (int z = 0; z < CHUNK_SIZE; z++) {
			for (int x = 0; x < CHUNK_SIZE; x++) {
				Vec3f worldPos = Vec3f(chkPos.x * CHUNK_SIZE + x, chkPos.y * CHUNK_SIZE + y, chkPos.z * CHUNK_SIZE + z) * 0.05f;
				float noise = perlinf(worldPos.x, worldPos.y, worldPos.z) * 0.5f + 0.5f;

				Vec3c voxelPos = Vec3c(x, y, z);
				if (noise > 0.5f) {
					chunk->voxels[zorder(voxelPos)] = Voxel(voxelPos, Voxel::Air);
				} else {
					chunk->voxels[zorder(voxelPos)] = Voxel(voxelPos, Voxel::Stone);
				}
			}
		}
	}
	return chunk;
}

