#include "MainScene.h"

#include <Entity.h>
#include <Camera.h>
#include <NoclipController.h>
#include <MeshRenderer.h>
#include <ShaderProgram.h>
#include <Mesh.h>



MainScene::MainScene() {}

MainScene::~MainScene() {}


void MainScene::load() {
	Scene::load();
	camera = new Entity();
	camera->addComponent<Camera>();
	camera->addComponent<NoclipController>();
	camera->transform->setPosition({0, 0, -3});

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

	cube = new Entity();
	MeshRenderer* cubeRend = cube->addComponent<MeshRenderer>();
	ShaderProgram::find("basic")->load();
	cubeRend->setShaderProgram(ShaderProgram::find("basic"));
	cubeRend->setMesh(cubeMesh);
}

void MainScene::update() {

}

void MainScene::destroy() {
	Scene::destroy();
	delete cube;
	delete cubeMesh;
	delete camera;
}
