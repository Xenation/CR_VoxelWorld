#include "WorldMesher.h"

#include <Debug.h>
#include "World.h"
#include "Chunk.h"
#include "Voxel.h"



WorldMesher::WorldMesher(World* world) : world(world) {
}

WorldMesher::~WorldMesher() {
}


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

void WorldMesher::processChunk(Chunk* chunk) {
	// Counting pass
	int opaqueVertexCount = 0;
	int opaqueIndexCount = 0;
	int transparentVertexCount = 0;
	int transparentIndexCount = 0;

	for (int y = 0; y < CHUNK_SIZE; y++) {
		for (int z = 0; z < CHUNK_SIZE; z++) {
			for (int x = 0; x < CHUNK_SIZE; x++) {
				Vec3c voxelPos = Vec3c(x, y, z);
				Voxel& voxel = chunk->voxels[zorder(voxelPos)];
				if (voxel.type == VoxelType::air) continue;
				if (voxel.type->isTransparent) {
					for (int side = 0; side < 6; side++) {
						if (hasVisibleSideTransparent(chunk, voxelPos, voxel.type, side)) {
							transparentVertexCount += 4;
							transparentIndexCount += 6;
						}
					}
				} else {
					for (int side = 0; side < 6; side++) {
						if (hasVisibleSideOpaque(chunk, voxelPos, side)) {
							opaqueVertexCount += 4;
							opaqueIndexCount += 6;
						}
					}
				}
			}
		}
	}
	if (transparentVertexCount == 0 && opaqueVertexCount == 0) return;

	// Meshing pass
	Vec3f* opaqueVertices = nullptr;
	unsigned int* opaqueTypes = nullptr;
	unsigned int* opaqueIndices = nullptr;
	int opaqueVerticesIndex = 0;
	int opaqueIndicesIndex = 0;
	if (opaqueVertexCount != 0) {
		opaqueVertices = new Vec3f[opaqueVertexCount];
		opaqueTypes = new unsigned int[opaqueVertexCount];
		opaqueIndices = new unsigned int[opaqueIndexCount];
		chunk->opaqueMesh = new Mesh(opaqueVertexCount, opaqueIndexCount);
		chunk->opaqueMesh->setAttributesDefinition(2, new int[2]{4, 1}, new GLenum[2]{GL_FLOAT, GL_UNSIGNED_INT});
	}
	Vec3f* transparentVertices = nullptr;
	unsigned int* transparentTypes = nullptr;
	unsigned int* transparentIndices = nullptr;
	int transparentVerticesIndex = 0;
	int transparentIndicesIndex = 0;
	if (transparentVertexCount != 0) {
		transparentVertices = new Vec3f[transparentVertexCount];
		transparentTypes = new unsigned int[transparentVertexCount];
		transparentIndices = new unsigned int[transparentIndexCount];
		chunk->transparentMesh = new Mesh(transparentVertexCount, transparentIndexCount);
		chunk->transparentMesh->setAttributesDefinition(2, new int[2]{4, 1}, new GLenum[2]{GL_FLOAT, GL_UNSIGNED_INT});
	}
	for (int y = 0; y < CHUNK_SIZE; y++) {
		for (int z = 0; z < CHUNK_SIZE; z++) {
			for (int x = 0; x < CHUNK_SIZE; x++) {
				Vec3c voxelPos = Vec3c(x, y, z);
				Voxel& voxel = chunk->voxels[zorder(voxelPos)];
				if (voxel.type == VoxelType::air) continue;
				if (voxel.type->isTransparent) {
					if (transparentVertexCount == 0) continue;
					for (int side = 0; side < 6; side++) {
						if (hasVisibleSideTransparent(chunk, voxelPos, voxel.type, side)) {
							fillFace(transparentVertices, transparentTypes, transparentVerticesIndex, transparentIndices, transparentIndicesIndex, Vec3f(voxelPos.x, voxelPos.y, voxelPos.z), side, voxel.type->id);
							transparentVerticesIndex += 4;
							transparentIndicesIndex += 6;
						}
					}
				} else {
					if (opaqueVertexCount == 0) continue;
					for (int side = 0; side < 6; side++) {
						if (hasVisibleSideOpaque(chunk, voxelPos, side)) {
							fillFace(opaqueVertices, opaqueTypes, opaqueVerticesIndex, opaqueIndices, opaqueIndicesIndex, Vec3f(voxelPos.x, voxelPos.y, voxelPos.z), side, voxel.type->id);
							opaqueVerticesIndex += 4;
							opaqueIndicesIndex += 6;
						}
					}
				}
			}
		}
	}
	if (opaqueVertexCount != 0) {
		chunk->opaqueMesh->setAttribute(0, (float*)opaqueVertices);
		chunk->opaqueMesh->setAttribute(1, opaqueTypes);
		chunk->opaqueMesh->setIndices(opaqueIndices);
		delete[] opaqueVertices;
		delete[] opaqueTypes;
		chunk->opaqueMesh->uploadToGL();
		chunk->opaqueMesh->deleteLocal();
	}

	if (transparentVertexCount != 0) {
		chunk->transparentMesh->setAttribute(0, (float*)transparentVertices);
		chunk->transparentMesh->setAttribute(1, transparentTypes);
		chunk->transparentMesh->setIndices(transparentIndices);
		delete[] transparentVertices;
		delete[] transparentTypes;
		chunk->transparentMesh->uploadToGL();
		chunk->transparentMesh->deleteLocal();
	}

}

bool WorldMesher::hasVisibleSideOpaque(Chunk* chunk, Vec3c voxPos, int side) {
	Voxel* voxel = getVoxelOnSide(chunk, voxPos, side);
	if (voxel == nullptr) return true;
	return voxel->type->isTransparent;
}

bool WorldMesher::hasVisibleSideTransparent(Chunk* chunk, Vec3c voxPos, const VoxelType*const type, int side) {
	Voxel* voxel = getVoxelOnSide(chunk, voxPos, side);
	if (voxel == nullptr) return true;
	return (voxel->type->isTransparent) ? voxel->type != type : false;
}

Voxel* WorldMesher::getVoxelOnSide(Chunk* chunk, Vec3c voxPos, int side) {
	switch (side) {
	case 0:
		if (voxPos.x == CHUNK_SIZE - 1) {
			if (chunk->east != nullptr) {
				return &chunk->east->voxels[zorder(Vec3c(0, voxPos.y, voxPos.z))];
			} else {
				return nullptr;
			}
		}
		return &chunk->voxels[zorder(voxPos + Vec3c(1, 0, 0))];
		break;
	case 1:
		if (voxPos.x == 0) {
			if (chunk->west != nullptr) {
				return &chunk->west->voxels[zorder(Vec3c(CHUNK_SIZE - 1, voxPos.y, voxPos.z))];
			} else {
				return nullptr;
			}
		}
		return &chunk->voxels[zorder(voxPos + Vec3c(-1, 0, 0))];
		break;
	case 2:
		if (voxPos.y == CHUNK_SIZE - 1) {
			if (chunk->top != nullptr) {
				return &chunk->top->voxels[zorder(Vec3c(voxPos.x, 0, voxPos.z))];
			} else {
				return nullptr;
			}
		}
		return &chunk->voxels[zorder(voxPos + Vec3c(0, 1, 0))];
		break;
	case 3:
		if (voxPos.y == 0) {
			if (chunk->bottom != nullptr) {
				return &chunk->bottom->voxels[zorder(Vec3c(voxPos.x, CHUNK_SIZE - 1, voxPos.z))];
			} else {
				return nullptr;
			}
		}
		return &chunk->voxels[zorder(voxPos + Vec3c(0, -1, 0))];
		break;
	case 4:
		if (voxPos.z == CHUNK_SIZE - 1) {
			if (chunk->north != nullptr) {
				return &chunk->north->voxels[zorder(Vec3c(voxPos.x, voxPos.y, 0))];
			} else {
				return nullptr;
			}
		}
		return &chunk->voxels[zorder(voxPos + Vec3c(0, 0, 1))];
		break;
	case 5:
		if (voxPos.z == 0) {
			if (chunk->south != nullptr) {
				return &chunk->south->voxels[zorder(Vec3c(voxPos.x, voxPos.y, CHUNK_SIZE - 1))];
			} else {
				return nullptr;
			}
		}
		return &chunk->voxels[zorder(voxPos + Vec3c(0, 0, -1))];
		break;
	}

	return nullptr;
}
