#pragma once
#include <unordered_map>
#include <XMath.h>
#include <Component.h>
#include "VMath.h"
#include "WorldGenerator.h"
class Chunk;
class World : public Component {
public:
	std::unordered_map<Vec3i, Chunk*, Vec3iHash> chunks;

	World(Entity* entity);
	World(const World&) = delete;
	~World();

	virtual void onStart() override;
	virtual void onDestroy() override;

private:
	WorldGenerator generator;
};

