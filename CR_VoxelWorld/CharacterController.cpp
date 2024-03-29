#include "CharacterController.h"

#include <bullet/btBulletDynamicsCommon.h>
#include <Entity.h>
#include <Rigidbody.h>
#include <Input.h>
#include <Time.h>
#include <BoxCollider.h>
#include <ParticleSystem.h>



CharacterController::CharacterController(Entity* entity) : Component(entity) {}

CharacterController::~CharacterController() {
	if (collider != nullptr) {
		delete collider;
	}
}


void CharacterController::onStart() {
	rigidbody = entity->getComponent<Rigidbody>();
	if (rigidbody == nullptr) return;
	collider = new BoxCollider({.2f, .9f, .2f});
	rigidbody->setCollider(collider);
	rigidbody->setMass(1.0f);
	rigidbody->getBulletBody()->setAngularFactor(btVector3(0, 0, 0));
	rigidbody->getBulletBody()->setActivationState(DISABLE_DEACTIVATION);
}

void CharacterController::onUpdate() {
	if (rigidbody == nullptr || camera == nullptr) return;
	if (Input::getKeyDown(KeyCode::C)) {
		noclipMode = !noclipMode;
		if (noclipMode) {
			rigidbody->disable();
		} else {
			rigidbody->enable();
		}
	}

	

	if (noclipMode) {
		if (Input::getKeyPressed(KeyCode::LEFT_SHIFT)) {
			currentSpeed = speed * 4.0f;
		} else {
			currentSpeed = speed;
		}

		float dt = Time::deltaTime;
		if (Input::getKeyPressed(KeyCode::W)) {
			transform->translate(camera->transform->forward() * currentSpeed * dt);
		}
		if (Input::getKeyPressed(KeyCode::S)) {
			transform->translate(camera->transform->backward() * currentSpeed * dt);
		}
		if (Input::getKeyPressed(KeyCode::D)) {
			transform->translate(camera->transform->right() * currentSpeed * dt);
		}
		if (Input::getKeyPressed(KeyCode::A)) {
			transform->translate(camera->transform->left() * currentSpeed * dt);
		}
		if (Input::getKeyPressed(KeyCode::Q)) {
			transform->translate(camera->transform->down() * currentSpeed * dt);
		}
		if (Input::getKeyPressed(KeyCode::E)) {
			transform->translate(camera->transform->up() * currentSpeed * dt);
		}
	} else {
		if (Input::getKeyPressed(KeyCode::LEFT_SHIFT)) {
			currentSpeed = speed * 2.0f;
		} else {
			currentSpeed = speed;
		}

		btVector3 btVel = rigidbody->getBulletBody()->getLinearVelocity();
		vel.x = 0.0f;
		vel.y = btVel.y();
		vel.z = 0.0f;
		Vec3f flatForward = Vec3f(camera->transform->forward().x, 0, camera->transform->forward().z);
		flatForward.normalize();
		Vec3f flatRight = Vec3f(camera->transform->right().x, 0, camera->transform->right().z);
		flatRight.normalize();
		if (Input::getKeyPressed(KeyCode::W)) {
			vel += flatForward * currentSpeed;
		}
		if (Input::getKeyPressed(KeyCode::S)) {
			vel -= flatForward * currentSpeed;
		}
		if (Input::getKeyPressed(KeyCode::A)) {
			vel -= flatRight * currentSpeed;
		}
		if (Input::getKeyPressed(KeyCode::D)) {
			vel += flatRight * currentSpeed;
		}
		if (Input::getKeyPressed(KeyCode::SPACE)) {
			vel += Vec3f::up * jetpackForce * Time::deltaTime;
			if (!jetpackSystem->getEmitting()) {
				jetpackSystem->startEmit();
			}
		} else if (jetpackSystem->getEmitting()) {
			jetpackSystem->stopEmit();
		}
		rigidbody->getBulletBody()->setLinearVelocity(btVector3(vel.x, vel.y, vel.z));
	}

	if (Input::getMouseDown(MouseButton::RIGHT)) {
		Input::LockMouse();
	}
	if (Input::getMousePressed(MouseButton::RIGHT)) {
		eulerRot.y += Input::mouseDelta.x * lookSensivity * Time::deltaTime;
		eulerRot.x += Input::mouseDelta.y * lookSensivity * Time::deltaTime;
		Input::mouseDelta = Vec2f::zero; // TODO remove when input system better
		camera->transform->setRotation(Quaternion::euler(eulerRot));
	}
	if (Input::getMouseUp(MouseButton::RIGHT)) {
		Input::UnlockMouse();
	}
}
