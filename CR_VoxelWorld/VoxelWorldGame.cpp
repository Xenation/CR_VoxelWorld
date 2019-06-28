#include "VoxelWorldGame.h"

#include <ShaderProgram.h>
#include <Material.h>



VoxelWorldGame::VoxelWorldGame() {}

VoxelWorldGame::~VoxelWorldGame() {}


void VoxelWorldGame::initialize() {
	voxelShader = ShaderProgram::find("voxels");
	voxelShader->load();
	voxelMaterialOpaque = new Material("VoxelOpaque", voxelShader, "opaque");
	voxelMaterialOpaque->setField(0, Vec4f(1.5f, -2.0f, -1.0f, 0));
	voxelMaterialOpaque->setField(1, 0.15f);
	voxelMaterialOpaque->updateFields();
	voxelMaterialTransparent = new Material("VoxelTransparent", voxelShader, "transparent");
	voxelMaterialTransparent->setField(0, Vec4f(1.5f, -2.0f, -1.0f, 0));
	voxelMaterialTransparent->setField(1, 0.15f);
	voxelMaterialTransparent->updateFields();

	basicShader = ShaderProgram::find("basic");
	basicShader->load();
	basicMaterial = new Material("Basic", basicShader, "opaque");
	basicMaterial->setField(0, Color(0, 1, 1));
	basicMaterial->setField(1, Vec4f(1.5f, -2.0f, -1.0f, 0));
	basicMaterial->setField(2, 0.15f);
	basicMaterial->updateFields();

	particleShader = ShaderProgram::find("particle_basic");
	if (particleShader != nullptr) {
		particleShader->load();
	}
	particleMaterial = new Material("ParticleBasic", particleShader, "transparent");
	particleMaterial->setField(0, Color(1.0f, 0.6f, 0.0f));
}

void VoxelWorldGame::preUpdate() {

}

void VoxelWorldGame::postUpdate() {

}

void VoxelWorldGame::cleanUp() {
	delete voxelMaterialTransparent;
	delete voxelMaterialOpaque;
	delete basicMaterial;

	delete voxelShader;
	delete basicShader;
}
