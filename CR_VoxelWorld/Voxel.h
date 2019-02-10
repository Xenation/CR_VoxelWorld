#pragma once
#include <XMath.h>
#include "VMath.h"
struct Voxel {
	enum Type : unsigned int {
		Air = 0,
		Stone = 1,
	};

	Vec3c position;
	Type type;


public:
	Voxel() : position(Vec3c()), type(Air) {}
	Voxel(Vec3c pos, Type type) : position(pos), type(type) {}
	Voxel(const Voxel&) = delete;
	~Voxel() {}
};

