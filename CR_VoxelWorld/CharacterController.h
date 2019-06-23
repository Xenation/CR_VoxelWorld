#pragma once
#include <Component.h>
#include <XMath.h>

class Entity;
class Rigidbody;
class Collider;

class CharacterController : public Component {
public:
	float speed = 4.0f;
	float lookSensivity = 1.0f;
	Entity* camera = nullptr;

	CharacterController(Entity* entity);
	~CharacterController();

	virtual void onStart() override;
	virtual void onUpdate() override;

private:
	float currentSpeed = 0.0f;
	Vec3f vel = Vec3f::zero;
	Vec3f eulerRot = Vec3f::zero;
	Rigidbody* rigidbody = nullptr;
	Collider* collider = nullptr;
};

