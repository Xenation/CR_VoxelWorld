#pragma once
#include <XMath.h>
#include "VMath.h"
struct VoxelType {
	static const VoxelType*const air;
	static const VoxelType*const stone;
	static const VoxelType*const dirt;
	static const VoxelType*const grass;
	static const VoxelType*const water;

	const unsigned int id;
	const bool isSolid;
	const bool isTransparent;
	const Vec4f color;

public:
	VoxelType() = delete;
	VoxelType(const VoxelType&) = delete;

private:
	VoxelType(unsigned int id, bool isSolid, bool isTransparent, Vec4f color) : id(id), isSolid(isSolid), isTransparent(isTransparent), color(color) {}
};

struct Voxel {
	static const Vec3f faceVertices[6][4];
	
	Vec3c position;
	const VoxelType* type;


public:
	Voxel() : position(Vec3c()), type(VoxelType::air) {}
	Voxel(Vec3c pos, const VoxelType* type) : position(pos), type(type) {}
	Voxel(const Voxel&) = delete;
	~Voxel() {}
};
