#include "MainScene.h"

#include <Entity.h>
#include <Camera.h>
#include <MeshRenderer.h>
#include <ShaderProgram.h>
#include <Material.h>
#include <Mesh.h>
#include <Collider.h>
#include <BoxCollider.h>
#include <Rigidbody.h>
#include <ParticleSystem.h>
#include "World.h"
#include "WorldRenderer.h"
#include "BlockRaycaster.h"
#include "CharacterController.h"



MainScene::MainScene() {}

MainScene::~MainScene() {}


void MainScene::load() {
	Scene::load();
	player = new Entity("Player");
	Entity* camera = new Entity("Camera");
	camera->addComponent<Camera>();
	camera->setParent(player);
	camera->transform->setPosition({0, 0.5f, 0});
	player->transform->setPosition({16, 32, 16});
	player->addComponent<Rigidbody>();
	ParticleSystem* particleSystem = player->addComponent<ParticleSystem>();
	particleSystem->emitVelocity = Vec3f::down;
	particleSystem->emitOffset = Vec3f(0, -.7f, 0);
	particleSystem->emitZoneExtents = Vec3f(.2f, .1f, .2f);
	particleSystem->emitRate = 200;
	particleSystem->minLifetime = .5f;
	particleSystem->maxLifetime = 1;
	particleSystem->setMaterial(Material::find("ParticleBasic"));
	CharacterController* controller = player->addComponent<CharacterController>();
	controller->lookSensivity = 1.0f;
	controller->camera = camera;
	controller->jetpackSystem = particleSystem;
	BlockRaycaster* br = camera->addComponent<BlockRaycaster>();


	cubeMesh = new Mesh(8, 36);
	cubeMesh->setAttributesDefinition(1, new int[1]{3});
	cubeMesh->setAttribute(0, new float[24]{
		-0.5f, 0.5f, -0.5f,
		-0.5f, 0.5f, 0.5f,
		0.5f, 0.5f, 0.5f,
		0.5f, 0.5f, -0.5f,
		-0.5f, -0.5f, -0.5f,
		-0.5f, -0.5f, 0.5f,
		0.5f, -0.5f, 0.5f,
		0.5f, -0.5f, -0.5f,
		});
	cubeMesh->setIndices(new unsigned int[36]{
		0, 2, 1,
		0, 3, 2,
		4, 3, 0,
		4, 7, 3,
		5, 0, 1,
		5, 4, 0,
		6, 1, 2,
		6, 5, 1,
		7, 2, 3,
		7, 6, 2,
		5, 7, 4,
		5, 6, 7
		});
	cubeMesh->uploadToGL();

	cube = new Entity("DebugCube");
	cube->transform->setScale({.1f, .1f, .1f});
	MeshRenderer* cubeRend = cube->addComponent<MeshRenderer>();
	cubeRend->setMaterial(Material::find("Basic"));
	cubeRend->setMesh(cubeMesh);

	worldEntity = new Entity("World");
	World* world = worldEntity->addComponent<World>();
	world->viewer = player->transform;

	br->world = world;
	br->debugEntity = cube;

	Collider* cubeCollider = new BoxCollider({0.5f, 0.5f, 0.5f});

	Entity* physCube = new Entity("Physics Cube");
	physCube->setParent(worldEntity);
	physCube->transform->setPosition({ 17.1f, 22, 24 });
	MeshRenderer* physCubeRend = physCube->addComponent<MeshRenderer>();
	physCubeRend->setMaterial(Material::find("Basic"));
	physCubeRend->setMesh(cubeMesh);
	Rigidbody* physCubeRb = physCube->addComponent<Rigidbody>();
	physCubeRb->setCollider(cubeCollider);
	physCubeRb->setMass(1.0f);

	Entity* physCube2 = new Entity("Physics Cube 2");
	physCube2->setParent(worldEntity);
	physCube2->transform->setPosition({ 16, 22, 24 });
	MeshRenderer* physCubeRend2 = physCube2->addComponent<MeshRenderer>();
	physCubeRend2->setMaterial(Material::find("Basic"));
	physCubeRend2->setMesh(cubeMesh);
	Rigidbody* physCubeRb2 = physCube2->addComponent<Rigidbody>();
	physCubeRb2->setCollider(cubeCollider);
	physCubeRb2->setMass(1.0f);

	Entity* physCube3 = new Entity("Physics Cube 3");
	physCube3->setParent(worldEntity);
	physCube3->transform->setPosition({ 14.9f, 22, 24 });
	MeshRenderer* physCubeRend3 = physCube3->addComponent<MeshRenderer>();
	physCubeRend3->setMaterial(Material::find("Basic"));
	physCubeRend3->setMesh(cubeMesh);
	Rigidbody* physCubeRb3 = physCube3->addComponent<Rigidbody>();
	physCubeRb3->setCollider(cubeCollider);
	physCubeRb3->setMass(1.0f);

	Entity* physCube4 = new Entity("Physics Cube 4");
	physCube4->setParent(worldEntity);
	physCube4->transform->setPosition({ 15.45f, 23.5f, 24 });
	MeshRenderer* physCubeRend4 = physCube4->addComponent<MeshRenderer>();
	physCubeRend4->setMaterial(Material::find("Basic"));
	physCubeRend4->setMesh(cubeMesh);
	Rigidbody* physCubeRb4 = physCube4->addComponent<Rigidbody>();
	physCubeRb4->setCollider(cubeCollider);
	physCubeRb4->setMass(1.0f);

	Entity* physCube5 = new Entity("Physics Cube 5");
	physCube5->setParent(worldEntity);
	physCube5->transform->setPosition({ 16.55f, 23.5f, 24 });
	MeshRenderer* physCubeRend5 = physCube5->addComponent<MeshRenderer>();
	physCubeRend5->setMaterial(Material::find("Basic"));
	physCubeRend5->setMesh(cubeMesh);
	Rigidbody* physCubeRb5 = physCube5->addComponent<Rigidbody>();
	physCubeRb5->setCollider(cubeCollider);
	physCubeRb5->setMass(1.0f);

	Entity* physCube6 = new Entity("Physics Cube 6");
	physCube6->setParent(worldEntity);
	physCube6->transform->setPosition({ 16, 25, 24 });
	MeshRenderer* physCubeRend6 = physCube6->addComponent<MeshRenderer>();
	physCubeRend6->setMaterial(Material::find("Basic"));
	physCubeRend6->setMesh(cubeMesh);
	Rigidbody* physCubeRb6 = physCube6->addComponent<Rigidbody>();
	physCubeRb6->setCollider(cubeCollider);
	physCubeRb6->setMass(1.0f);
}

void MainScene::update() {

}

void MainScene::destroy() {
	Scene::destroy();
	delete cube;
	delete cubeMesh;
	delete player;
}
