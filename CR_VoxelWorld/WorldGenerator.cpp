#include "WorldGenerator.h"

#include <Perlin.h>
#include <Debug.h>
#include <XMath.h>
#include <string>
#include "Chunk.h"



WorldGenerator::WorldGenerator(World* world, unsigned int seed) : world(world), seed(seed) {}

WorldGenerator::~WorldGenerator() {}

Chunk* WorldGenerator::generateChunk(Vec3i chkPos) {
	static const int noiseGridRes = 3;
	static const float noiseGridCellSize = CHUNK_SIZE / (float) (noiseGridRes - 1);
	float noiseMap[noiseGridRes][noiseGridRes][noiseGridRes];

	for (int y = 0; y < noiseGridRes; y++) {
		for (int z = 0; z < noiseGridRes; z++) {
			for (int x = 0; x < noiseGridRes; x++) {
				Vec3f worldPos = Vec3f(chkPos.x * CHUNK_SIZE + x * noiseGridCellSize, chkPos.y * CHUNK_SIZE + y * noiseGridCellSize, chkPos.z * CHUNK_SIZE + z * noiseGridCellSize);
				float noise = perlinf(worldPos.x * 0.05f, worldPos.y * 0.05f, worldPos.z * 0.05f);
				float interpHeight = (perlinf(worldPos.x * 0.003f, 0, worldPos.z * 0.003f) * 0.5f + 0.5f) * 32.0f;
				noise -= (worldPos.y - interpHeight) / (interpHeight * 0.5f);
				noise += (perlinf(worldPos.x * 0.003f, worldPos.y * 0.003f, worldPos.z * 0.003f) * 0.5f + 0.5f) * ((worldPos.y - interpHeight) / (interpHeight * 0.45f));
				noiseMap[x][y][z] = noise;
			}
		}
	}

	Chunk* chunk = new Chunk(chkPos, world);
	for (int y = 0; y < CHUNK_SIZE; y++) {
		for (int z = 0; z < CHUNK_SIZE; z++) {
			for (int x = 0; x < CHUNK_SIZE; x++) {
				Vec3c voxelPos = Vec3c(x, y, z);
				Vec3c noisePos = voxelPos / noiseGridCellSize;
				Vec3f noiseRelative = Vec3f(voxelPos.x, voxelPos.y, voxelPos.z) / noiseGridCellSize - Vec3f(noisePos.x, noisePos.y, noisePos.z);

				float noise = lerpf(
					lerpf( // Z-
						lerpf(noiseMap[noisePos.x][noisePos.y][noisePos.z], noiseMap[noisePos.x + 1][noisePos.y][noisePos.z], noiseRelative.x), // Y-
						lerpf(noiseMap[noisePos.x][noisePos.y + 1][noisePos.z], noiseMap[noisePos.x + 1][noisePos.y + 1][noisePos.z], noiseRelative.x), noiseRelative.y), // Y+
					lerpf( // Z+
						lerpf(noiseMap[noisePos.x][noisePos.y][noisePos.z + 1], noiseMap[noisePos.x + 1][noisePos.y][noisePos.z + 1], noiseRelative.x), // Y-
						lerpf(noiseMap[noisePos.x][noisePos.y + 1][noisePos.z + 1], noiseMap[noisePos.x + 1][noisePos.y + 1][noisePos.z + 1], noiseRelative.x), noiseRelative.y), // Y+
					noiseRelative.z);

				if (noise < 0.0f) {
					chunk->voxels[zorder(voxelPos)] = Voxel(voxelPos, VoxelType::air);
				} else {
					chunk->voxels[zorder(voxelPos)] = Voxel(voxelPos, VoxelType::stone);
				}
			}
		}
	}

	int localWaterLevel = 16 - chkPos.y * CHUNK_SIZE;

	// Lay grass
	for (int z = 0; z < CHUNK_SIZE; z++) {
		for (int x = 0; x < CHUNK_SIZE; x++) {
			for (int y = CHUNK_SIZE - 1; y > 0; y--) {
				Voxel& voxel = chunk->voxels[zorder(Vec3c(x, y, z))];
				Voxel& botVoxel = chunk->voxels[zorder(Vec3c(x, y - 1, z))];
				if (voxel.type == VoxelType::air && botVoxel.type == VoxelType::stone) {
					if (y <= localWaterLevel) {
						botVoxel.type = VoxelType::dirt;
					} else {
						botVoxel.type = VoxelType::grass;
					}
					int yd = y - 2;
					for (; yd > 0 && yd > y - 5; yd--) {
						Voxel& dirtVoxel = chunk->voxels[zorder(Vec3c(x, yd, z))];
						if (dirtVoxel.type == VoxelType::air) break;
						dirtVoxel.type = VoxelType::dirt;
					}
					y = yd + 1;
				}
			}
		}
	}

	// Ocean
	for (int z = 0; z < CHUNK_SIZE; z++) {
		for (int x = 0; x < CHUNK_SIZE; x++) {
			for (int y = localWaterLevel; y > 0; y--) {
				Voxel& voxel = chunk->voxels[zorder(Vec3c(x, y, z))];
				if (voxel.type == VoxelType::air) {
					voxel.type = VoxelType::water;
				}
			}
		}
	}

	Debug::log("WorldGen", ("Generated Chunk(" + std::to_string(chkPos.x) + ", " + std::to_string(chkPos.y) + ", " + std::to_string(chkPos.z) + ")").c_str());
	return chunk;
}

