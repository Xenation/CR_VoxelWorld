#pragma once
#include "VMath.h"
class World;
class Chunk;
struct Voxel;
struct VoxelType;
class WorldMesher {
public:
	World* world;

	WorldMesher(World* world);
	~WorldMesher();

	void processChunk(Chunk* chunk);

private:
	bool hasVisibleSideOpaque(Chunk* chunk, Vec3c voxPos, int side);
	bool hasVisibleSideTransparent(Chunk* chunk, Vec3c voxPos, const VoxelType*const type, int side);
	Voxel* getVoxelOnSide(Chunk* chunk, Vec3c voxPos, int side);
};

