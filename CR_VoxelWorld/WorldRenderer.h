#pragma once
#include <Renderer.h>
#include <SimpleList.h>

class World;
class Chunk;
class Material;

class WorldRenderer : public Renderer {
public:
	World* world;

	WorldRenderer(Entity* entity);
	~WorldRenderer();

	virtual void setMaterial(Material* mat) override;
	virtual void render() override;

private:
	bool isTransparent = false;
	unsigned int modelMatrixLocation = 0;
};

