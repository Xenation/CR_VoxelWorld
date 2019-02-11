#include "Voxel.h"

const VoxelType*const VoxelType::air = new VoxelType(0, false, true, Vec4f());
const VoxelType*const VoxelType::stone = new VoxelType(1, true, false, Vec4f(0.631f, 0.631f, 0.631f, 1.0f));
const VoxelType*const VoxelType::dirt = new VoxelType(2, true, false, Vec4f(0.66f, 0.40f, 0.21f, 1.0f));
const VoxelType*const VoxelType::grass = new VoxelType(3, true, false, Vec4f(0.454f, 0.717f, 0.341f, 1.0f));

const Vec3f Voxel::faceVertices[6][4]{
	{
		{1, 1, 0},
		{1, 1, 1},
		{1, 0, 1},
		{1, 0, 0}
	}, {
		{0, 1, 1},
		{0, 1, 0},
		{0, 0, 0},
		{0, 0, 1}
	}, {
		{0, 1, 1},
		{1, 1, 1},
		{1, 1, 0},
		{0, 1, 0}
	}, {
		{0, 0, 0},
		{1, 0, 0},
		{1, 0, 1},
		{0, 0, 1}
	}, {
		{1, 1, 1},
		{0, 1, 1},
		{0, 0, 1},
		{1, 0, 1}
	}, {
		{0, 1, 0},
		{1, 1, 0},
		{1, 0, 0},
		{0, 0, 0}
	}
};