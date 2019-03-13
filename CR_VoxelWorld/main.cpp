#include <iostream>
#include <Engine.h>

#include "VoxelWorldGame.h"
#include "MainScene.h"

int main(int argc, char** args) {

	Engine::initialize(new VoxelWorldGame());
	Engine::scene = new MainScene();
	Engine::scene->load();

	Engine::loop();

	Engine::destroy();

	system("pause");
	return 0;
}
