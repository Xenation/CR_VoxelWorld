#pragma once
#include <XMath.h>
#include <Mesh.h>
#include "Voxel.h"
#include "ZOrder.h"

// Size must be a power of 2
#define CHUNK_SIZE 32
#define CHUNK_VOXEL_COUNT (CHUNK_SIZE * CHUNK_SIZE * CHUNK_SIZE)

class Chunk {
public:
	Vec3i position;
	Voxel voxels[CHUNK_VOXEL_COUNT];
	Mesh* mesh;

	inline Voxel& getVoxel(const Vec3c& pos) {
		return voxels[zorder(pos)];
	}

	void generateMesh();

	Chunk(Vec3i pos);
	Chunk(const Chunk&) = delete;
	~Chunk();
};

