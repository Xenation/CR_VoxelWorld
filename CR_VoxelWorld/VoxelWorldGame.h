#pragma once
#include <Game.h>

class ShaderProgram;
class Material;

class VoxelWorldGame : public Game {
public:
	ShaderProgram* voxelShader;
	Material* voxelMaterialOpaque;
	Material* voxelMaterialTransparent;
	ShaderProgram* basicShader;
	Material* basicMaterial;
	ShaderProgram* particleShader;
	Material* particleMaterial;

	VoxelWorldGame();
	~VoxelWorldGame();

	virtual void initialize() override;
	virtual void preUpdate() override;
	virtual void postUpdate() override;
	virtual void cleanUp() override;
};

