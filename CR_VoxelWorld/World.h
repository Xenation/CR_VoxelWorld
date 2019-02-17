#pragma once
#include <unordered_map>
#include <XMath.h>
#include <XMathHash.h>
#include <Component.h>
#include "VMath.h"
#include "WorldGenerator.h"
#include "WorldMesher.h"
#include "Voxel.h"
class Chunk;
class World : public Component {
public:
	std::unordered_map<Vec3i, Chunk*, Vec3iHash> chunks;

	World(Entity* entity);
	World(const World&) = delete;
	~World();

	virtual void onStart() override;
	virtual void onDestroy() override;

	Chunk* getChunkAt(const Vec3i& chkPos);
	Voxel* getVoxelAt(const Vec3i& voxPos);
	Voxel* getVoxelAt(const Vec3i& voxPos, Chunk*& chunk);
	bool raycast(const Ray& ray, float distance, Vec3f& intersect, Voxel*& intersectVoxel, Chunk*& intersectChunk);
	void remeshChunk(Chunk* chunk);

private:
	WorldGenerator generator;
	WorldMesher mesher;
};

