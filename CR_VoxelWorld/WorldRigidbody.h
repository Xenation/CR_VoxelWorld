#pragma once
#include <Rigidbody.h>

class btCompoundShape;
class World;

class WorldRigidbody : public Rigidbody {
public:
	World* world;

	WorldRigidbody(Entity* entity);
	~WorldRigidbody();

	virtual void onUpdate() override;
};

