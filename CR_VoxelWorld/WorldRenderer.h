#pragma once
#include <Renderer.h>
#include <SimpleList.h>
class World;
class Chunk;
class WorldRenderer : public Renderer {
public:
	World* world;

	WorldRenderer(Entity* entity);
	~WorldRenderer();

	virtual void render() override;

private:
	bool isTransparent = false;
};

