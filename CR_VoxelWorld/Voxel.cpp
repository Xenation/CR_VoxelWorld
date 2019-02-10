#include "Voxel.h"

const VoxelType*const VoxelType::air = new VoxelType(false, true, Vec4f());
const VoxelType*const VoxelType::stone = new VoxelType(true, false, Vec4f(0.631f, 0.631f, 0.631f, 1.0f));
const VoxelType*const VoxelType::dirt = new VoxelType(true, false, Vec4f(0.66f, 0.40f, 0.21f, 1.0f));
const VoxelType*const VoxelType::grass = new VoxelType(true, false, Vec4f(0.454f, 0.717f, 0.341f, 1.0f));
