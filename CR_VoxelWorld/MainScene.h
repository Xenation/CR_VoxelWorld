#pragma once
#include <Scene.h>

class Mesh;
class Entity;
class ShaderProgram;
class Material;

class MainScene : public Scene {
public:
	MainScene();
	~MainScene();

	virtual void load() override;
	virtual void update() override;
	virtual void destroy() override;

private:
	Entity* player;
	Entity* cube;
	Mesh* cubeMesh;
	Entity* worldEntity;
};

