#include "Chunk.h"



Chunk::Chunk(Vec3i pos) : position(pos) {}

Chunk::~Chunk() {}

void fillCube(Vec3f* verts, int vIndex, unsigned int* indices, int iIndex, Vec3f voxPos) {
	static Vec3f cubeVerts[8]{
		{-0.5f, 0.5f, -0.5f},
		{-0.5f, 0.5f, 0.5f},
		{0.5f, 0.5f, 0.5f},
		{0.5f, 0.5f, -0.5f},
		{-0.5f, -0.5f, -0.5f},
		{-0.5f, -0.5f, 0.5f},
		{0.5f, -0.5f, 0.5f},
		{0.5f, -0.5f, -0.5f},
	};
	static unsigned int cubeIndices[36]{
		0, 2, 1,
		0, 3, 2,
		4, 3, 0,
		4, 7, 3,
		5, 0, 1,
		5, 4, 0,
		6, 1, 2,
		6, 5, 1,
		7, 2, 3,
		7, 6, 2,
		5, 7, 4,
		5, 6, 7
	};

	for (int i = 0; i < 8; i++) {
		verts[vIndex + i] = voxPos + cubeVerts[i];
	}
	for (int i = 0; i < 36; i++) {
		indices[iIndex + i] = cubeIndices[i] + vIndex;
	}
}

void Chunk::generateMesh() {
	// Counting pass
	int vCount = 0;
	int iCount = 0;
	for (int y = 0; y < CHUNK_SIZE; y++) {
		for (int z = 0; z < CHUNK_SIZE; z++) {
			for (int x = 0; x < CHUNK_SIZE; x++) {
				if (voxels[zorder(Vec3c(x, y, z))].type == Voxel::Air) continue;
				vCount += 8;
				iCount += 36;
			}
		}
	}

	mesh = new Mesh(vCount, iCount);
	mesh->setAttributesDefinition(1, new int {4});
	
	// Meshing pass
	Vec3f* vertices = new Vec3f[vCount];
	unsigned int* indices = new unsigned int[iCount];
	int vIndex = 0;
	int iIndex = 0;
	for (int y = 0; y < CHUNK_SIZE; y++) {
		for (int z = 0; z < CHUNK_SIZE; z++) {
			for (int x = 0; x < CHUNK_SIZE; x++) {
				Vec3c voxelPos = Vec3c(x, y, z);
				if (voxels[zorder(voxelPos)].type == Voxel::Air) continue;
				fillCube(vertices, vIndex, indices, iIndex, Vec3f(voxelPos.x, voxelPos.y, voxelPos.z));
				vIndex += 8;
				iIndex += 36;
			}
		}
	}

	mesh->setAttribute(0, (float*) vertices);
	mesh->setIndices(indices);
	mesh->uploadToGL();
}
