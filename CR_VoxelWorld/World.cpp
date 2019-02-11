#include "World.h"

#include <string>
#include <Entity.h>
#include "WorldRenderer.h"
#include "Chunk.h"



World::World(Entity* entity) : Component(entity), generator(8) {}

World::~World() {}


void World::onStart() {
	// TestGen
	for (int y = 0; y < 4; y++) {
		for (int z = 0; z < 16; z++) {
			for (int x = 0; x < 16; x++) {
				Vec3i chkPos = Vec3i(x, y, z);
				Chunk* chunk = generator.generateChunk(chkPos);
				chunks[chkPos] = chunk;
				chunk->generateMesh();
			}
		}
	}

	WorldRenderer* renderer = entity->addComponent<WorldRenderer>();
	renderer->world = this;
}

void World::onDestroy() {
	for (std::pair<Vec3i, Chunk*> pair : chunks) {
		delete pair.second;
	}
}

Chunk* World::getChunkAt(const Vec3i& chkPos) {
	std::list<std::pair<const Vec3i, Chunk*>>::const_iterator search = chunks.find(chkPos);
	if (search != chunks.end()) {
		return search->second;
	} else {
		return nullptr;
	}
}

Voxel* World::getVoxelAt(const Vec3i& voxPos) {
	Vec3i chkPos = voxPos / CHUNK_SIZE;
	if (voxPos.x < 0) {
		chkPos.x--;
	}
	if (voxPos.y < 0) {
		chkPos.y--;
	}
	if (voxPos.z < 0) {
		chkPos.z--;
	}
	Chunk* chunk = getChunkAt(chkPos);
	if (chunk == nullptr) return nullptr;
	Vec3c relativePos = Vec3c(voxPos.x - chkPos.x * CHUNK_SIZE, voxPos.y - chkPos.y * CHUNK_SIZE, voxPos.z - chkPos.z * CHUNK_SIZE);
	return &chunk->voxels[zorder(relativePos)];
}

inline bool raycastVoxel(const Vec3f& worldPos, const Ray& ray, Vec3f& intersect, float& t) {
	for (int side = 0; side < 6; side++) {
		if (intersectQuad(Voxel::faceVertices[side][0] + worldPos, Voxel::faceVertices[side][1] + worldPos, Voxel::faceVertices[side][2] + worldPos, Voxel::faceVertices[side][3] + worldPos, ray, intersect, t)) return true;
	}
	return false;
}

bool World::raycast(const Ray& ray, float distance, Vec3f& intersect) {
	Vec3i min = ray.origin.floor();
	Vec3i max = (ray.origin + ray.direction * distance).floor();
	swapToMinMax(min, max);
	float minDist = INFINITY;
	bool hasIntersected = false;
	for (int x = min.x; x <= max.x; x++) {
		for (int y = min.y; y <= max.y; y++) {
			for (int z = min.z; z <= max.z; z++) {
				Vec3i voxPos = Vec3i(x, y, z);
				Voxel* voxel = getVoxelAt(voxPos);
				if (voxel == nullptr || voxel->type == VoxelType::air) continue;
				Vec3f voxIntersect;
				float dist;
				if (raycastVoxel(Vec3f(voxPos.x, voxPos.y, voxPos.z), ray, voxIntersect, dist)) {
					if (dist < minDist) {
						minDist = dist;
						intersect = voxIntersect;
						hasIntersected = true;
					}
				}
			}
		}
	}
	return hasIntersected;
}
