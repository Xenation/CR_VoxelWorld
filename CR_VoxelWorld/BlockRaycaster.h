#pragma once
#include <Component.h>
class World;
class BlockRaycaster : public Component {
public:
	World* world;
	Entity* debugEntity;
	float raycastRange = 10.0f;

	BlockRaycaster(Entity* entity);
	~BlockRaycaster();

	virtual void onStart() override;
	virtual void onUpdate() override;
};

