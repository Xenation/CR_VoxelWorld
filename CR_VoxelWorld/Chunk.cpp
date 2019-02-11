#include "Chunk.h"



Chunk::Chunk(Vec3i pos) : position(pos) {}

Chunk::~Chunk() {}

void fillFace(Vec3f* vertices, unsigned int* types, int vIndex, unsigned int* indices, int iIndex, Vec3f voxPos, int side, unsigned int voxelType) {
	// sides: x+, x-, y+, y-, z+, z-

	static unsigned int faceIndices[6]{
		0, 3, 2,
		0, 2, 1
	};

	for (int i = 0; i < 4; i++) {
		vertices[vIndex + i] = voxPos + Voxel::faceVertices[side][i];
		types[vIndex + i] = voxelType;
	}
	for (int i = 0; i < 6; i++) {
		indices[iIndex + i] = faceIndices[i] + vIndex;
	}
}

void Chunk::generateMesh() {
	// Counting pass
	int vCount = 0;
	int iCount = 0;
	for (int y = 0; y < CHUNK_SIZE; y++) {
		for (int z = 0; z < CHUNK_SIZE; z++) {
			for (int x = 0; x < CHUNK_SIZE; x++) {
				Vec3c voxelPos = Vec3c(x, y, z);
				if (voxels[zorder(voxelPos)].type == VoxelType::air) continue;
				for (int side = 0; side < 6; side++) {
					if (!hasVoxelOnSide(voxelPos, side)) {
						vCount += 4;
						iCount += 6;
					}
				}
			}
		}
	}

	mesh = new Mesh(vCount, iCount);
	mesh->setAttributesDefinition(2, new int[2] {4, 1}, new GLenum[2] {GL_FLOAT, GL_UNSIGNED_INT});
	
	// Meshing pass
	Vec3f* vertices = new Vec3f[vCount];
	unsigned int* types = new unsigned int[vCount];
	unsigned int* indices = new unsigned int[iCount];
	int vIndex = 0;
	int iIndex = 0;
	for (int y = 0; y < CHUNK_SIZE; y++) {
		for (int z = 0; z < CHUNK_SIZE; z++) {
			for (int x = 0; x < CHUNK_SIZE; x++) {
				Vec3c voxelPos = Vec3c(x, y, z);
				Voxel& voxel = voxels[zorder(voxelPos)];
				if (voxel.type == VoxelType::air) continue;
				for (int side = 0; side < 6; side++) {
					if (!hasVoxelOnSide(voxelPos, side)) {
						fillFace(vertices, types, vIndex, indices, iIndex, Vec3f(voxelPos.x, voxelPos.y, voxelPos.z), side, voxel.type->id);
						vIndex += 4;
						iIndex += 6;
					}
				}
			}
		}
	}

	mesh->setAttribute(0, (float*) vertices);
	mesh->setAttribute(1, types);
	mesh->setIndices(indices);
	delete[] vertices;
	delete[] types;
	mesh->uploadToGL();
	mesh->deleteLocal();
}

bool Chunk::hasVoxelOnSide(Vec3c voxPos, int side) {
	// sides: x+, x-, y+, y-, z+, z-

	switch (side) {
	case 0:
		if (voxPos.x == CHUNK_SIZE - 1) return false;
		return voxels[zorder(voxPos + Vec3c(1, 0, 0))].type != VoxelType::air;
		break;
	case 1:
		if (voxPos.x == 0) return false;
		return voxels[zorder(voxPos + Vec3c(-1, 0, 0))].type != VoxelType::air;
		break;
	case 2:
		if (voxPos.y == CHUNK_SIZE - 1) return false;
		return voxels[zorder(voxPos + Vec3c(0, 1, 0))].type != VoxelType::air;
		break;
	case 3:
		if (voxPos.y == 0) return false;
		return voxels[zorder(voxPos + Vec3c(0, -1, 0))].type != VoxelType::air;
		break;
	case 4:
		if (voxPos.z == CHUNK_SIZE - 1) return false;
		return voxels[zorder(voxPos + Vec3c(0, 0, 1))].type != VoxelType::air;
		break;
	case 5:
		if (voxPos.z == 0) return false;
		return voxels[zorder(voxPos + Vec3c(0, 0, -1))].type != VoxelType::air;
		break;
	}

	return true;
}

void Chunk::linkAdjacentChunks() {
	if (north == nullptr) {
		
	}
}
