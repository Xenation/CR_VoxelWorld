#include "World.h"

#include <string>
#include <Entity.h>
#include <ShaderProgram.h>
#include <Material.h>
#include <Transform.h>
#include <Engine.h>
#include <Game.h>
#include "WorldRenderer.h"
#include "Chunk.h"
#include "VoxelWorldGame.h"
#include "WorldRigidbody.h"



World::World(Entity* entity) : Component(entity), generator(this, 8), mesher(this) {}

World::~World() {}


void World::onStart() {
	ShaderProgram* voxelsShader = ShaderProgram::find("voxels");
	voxelsShader->load();
	WorldRenderer* opaqueRenderer = entity->addComponent<WorldRenderer>();
	opaqueRenderer->world = this;
	opaqueRenderer->setMaterial(((VoxelWorldGame*) Engine::game)->voxelMaterialOpaque);
	WorldRenderer* transparentRenderer = entity->addComponent<WorldRenderer>();
	transparentRenderer->world = this;
	transparentRenderer->setMaterial(((VoxelWorldGame*) Engine::game)->voxelMaterialTransparent);
	WorldRigidbody* rigidbody = entity->addComponent<WorldRigidbody>();
	rigidbody->world = this;
}

void World::onUpdate() {
	if (viewer == nullptr) return;
	Vec3i viewerChunkPos = toVec3i(viewer->getWorldPosition() / CHUNK_SIZE);
	int sqrViewDistance = viewDistance * viewDistance;
	// Check for chunks to delete
	SimpleList<Vec3i> toRemove(4, 4);
	for (std::pair<Vec3i, Chunk*> pair : chunks) {
		Vec3i toChunk = pair.first - viewerChunkPos;
		int sqrDistance = toChunk.x * toChunk.x + toChunk.y * toChunk.y + toChunk.z * toChunk.z;
		if (sqrDistance > sqrViewDistance) {
			delete pair.second;
			toRemove.add(pair.first);
		}
	}
	for (unsigned int i = 0; i < toRemove.count; i++) {
		chunks.erase(toRemove[i]);
	}

	// Check for chunk to generate
	Vec3i genMin = viewerChunkPos - Vec3i(generationDistance, generationDistance, generationDistance);
	Vec3i genMax = viewerChunkPos + Vec3i(generationDistance, generationDistance, generationDistance);
	for (int y = genMin.y; y <= genMax.y; y++) {
		for (int z = genMin.z; z <= genMax.z; z++) {
			for (int x = genMin.x; x <= genMax.x; x++) {
				Vec3i chkPos = Vec3i(x, y, z);
				Vec3i toChunk = chkPos - viewerChunkPos;
				if (toChunk.x * toChunk.x + toChunk.y * toChunk.y + toChunk.z * toChunk.z > sqrViewDistance) continue;
				if (getChunkAt(chkPos) == nullptr) {
					Chunk* chunk = generator.generateChunk(chkPos);
					chunks[chkPos] = chunk;
				}
			}
		}
	}

	Vec3i meshingMin = viewerChunkPos - Vec3i(viewDistance, viewDistance, viewDistance);
	Vec3i meshingMax = viewerChunkPos + Vec3i(viewDistance, viewDistance, viewDistance);
	for (int y = meshingMin.y; y <= meshingMax.y; y++) {
		for (int z = meshingMin.z; z <= meshingMax.z; z++) {
			for (int x = meshingMin.x; x <= meshingMax.x; x++) {
				Vec3i chkPos = Vec3i(x, y, z);
				Vec3i toChunk = chkPos - viewerChunkPos;
				if (toChunk.x * toChunk.x + toChunk.y * toChunk.y + toChunk.z * toChunk.z > sqrViewDistance) continue;
				Chunk* chunk = getChunkAt(chkPos);
				if (chunk == nullptr || chunk->meshed) continue;
				mesher.processChunk(chunk);
			}
		}
	}
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
	Chunk* chk;
	return getVoxelAt(voxPos, chk);
}

Voxel* World::getVoxelAt(const Vec3i& voxPos, Chunk*& chunk) {
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
	chunk = getChunkAt(chkPos);
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

bool World::raycast(const Ray& ray, float distance, Vec3f& intersect, Voxel*& intersectVoxel, Chunk*& intersectChunk) {
	Vec3i min = ray.origin.floor();
	Vec3i max = (ray.origin + ray.direction * distance).floor();
	swapToMinMax(min, max);
	float minDist = INFINITY;
	bool hasIntersected = false;
	for (int x = min.x; x <= max.x; x++) {
		for (int y = min.y; y <= max.y; y++) {
			for (int z = min.z; z <= max.z; z++) {
				Vec3i voxPos = Vec3i(x, y, z);
				Voxel* voxel = getVoxelAt(voxPos, intersectChunk);
				if (voxel == nullptr || voxel->type == VoxelType::air) continue;
				Vec3f voxIntersect;
				float dist;
				if (raycastVoxel(Vec3f(voxPos.x, voxPos.y, voxPos.z), ray, voxIntersect, dist)) {
					if (dist < minDist) {
						minDist = dist;
						intersect = voxIntersect;
						hasIntersected = true;
						intersectVoxel = voxel;
					}
				}
			}
		}
	}
	return hasIntersected;
}

void World::remeshChunk(Chunk* chunk) {
	if (chunk == nullptr) return;
	delete chunk->opaqueMesh;
	delete chunk->transparentMesh;
	mesher.processChunk(chunk);
}
