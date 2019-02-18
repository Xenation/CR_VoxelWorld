#pragma once
#include <XMath.h>
#include <Mesh.h>
#include "VZOrder.h"
#include "Voxel.h"

// Size must be a power of 2
#define CHUNK_SIZE 32
#define CHUNK_VOXEL_COUNT (CHUNK_SIZE * CHUNK_SIZE * CHUNK_SIZE)

class World;
class Chunk {
public:
	Vec3i position;
	Voxel voxels[CHUNK_VOXEL_COUNT];
	World* world;
	Chunk* north = nullptr; Chunk* east = nullptr; Chunk* south = nullptr; Chunk* west = nullptr; Chunk* top = nullptr; Chunk* bottom = nullptr;
	Mesh* opaqueMesh = nullptr;
	Mesh* transparentMesh = nullptr;
	bool meshed = false;

	inline Voxel& getVoxel(const Vec3c& pos) {
		return voxels[zorder(pos)];
	}

	Chunk(Vec3i pos, World* world);
	Chunk(const Chunk&) = delete;
	~Chunk();

private:
	void linkAdjacentChunks();
	void unlinkAdjacentChunks();
};

