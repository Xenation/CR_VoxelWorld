#include "WorldRenderer.h"

#include <Debug.h>
#include <ShaderProgram.h>
#include <unordered_map>
#include "Chunk.h"
#include "World.h"



WorldRenderer::WorldRenderer(Entity* entity) : Renderer(entity) {}

WorldRenderer::~WorldRenderer() {}


void WorldRenderer::render() {
	if (world == nullptr) return;

	for (std::pair<Vec3i, Chunk*> pair : world->chunks) {
		if (isTransparent && pair.second->transparentMesh == nullptr) continue;
		else if (!isTransparent && pair.second->opaqueMesh == nullptr) continue;
		Matrix4x4f chkModel = Matrix4x4f::translation(Vec3f(pair.second->position.x * CHUNK_SIZE, pair.second->position.y * CHUNK_SIZE, pair.second->position.z * CHUNK_SIZE));
		shaderProgram->loadModelMatrix(chkModel);

		if (isTransparent) {
			pair.second->transparentMesh->render();
		} else {
			pair.second->opaqueMesh->render();
		}
	}

}
