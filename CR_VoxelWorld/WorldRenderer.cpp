#include "WorldRenderer.h"

#include <ShaderProgram.h>
#include <unordered_map>
#include "Chunk.h"
#include "World.h"



WorldRenderer::WorldRenderer(Entity* entity) : Renderer(entity) {}

WorldRenderer::~WorldRenderer() {}


void WorldRenderer::render() {
	if (world == nullptr) return;

	shaderProgram->use();
	for (std::pair<Vec3i, Chunk*> pair : world->chunks) {
		Matrix4x4f chkModel = Matrix4x4f::translation(Vec3f(pair.second->position.x * CHUNK_SIZE, pair.second->position.y * CHUNK_SIZE, pair.second->position.z * CHUNK_SIZE));
		shaderProgram->loadModelMatrix(chkModel);

		pair.second->mesh->render();
	}

	shaderProgram->unuse();
}
