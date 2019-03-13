#include "VoxelWorldGame.h"

#include <ShaderProgram.h>
#include <Material.h>



VoxelWorldGame::VoxelWorldGame() {}

VoxelWorldGame::~VoxelWorldGame() {}


void VoxelWorldGame::initialize() {
	voxelShader = ShaderProgram::find("voxels");
	voxelShader->load();
	voxelMaterialOpaque = new Material(voxelShader, "opaque");
	voxelMaterialOpaque->setField(1, Vec4f(1.5f, -2.0f, -1.0f, 0));
	voxelMaterialOpaque->setField(2, 0.15f);
	voxelMaterialTransparent = new Material(voxelShader, "transparent");
	voxelMaterialTransparent->setField(1, Vec4f(1.5f, -2.0f, -1.0f, 0));
	voxelMaterialTransparent->setField(2, 0.15f);
}

void VoxelWorldGame::preUpdate() {

}

void VoxelWorldGame::postUpdate() {

}

void VoxelWorldGame::cleanUp() {
	delete voxelMaterialTransparent;
	delete voxelMaterialOpaque;
	delete voxelShader;
}
