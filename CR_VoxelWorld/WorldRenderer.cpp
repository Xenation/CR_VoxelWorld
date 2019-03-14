#include "WorldRenderer.h"

#include <Debug.h>
#include <Engine.h>
#include <Pipeline.h>
#include <ShaderProgram.h>
#include <SpecializedShaderProgram.h>
#include <Material.h>
#include <unordered_map>
#include "Chunk.h"
#include "World.h"



WorldRenderer::WorldRenderer(Entity* entity) : Renderer(entity) {
	
}

WorldRenderer::~WorldRenderer() {}


void WorldRenderer::setMaterial(Material* mat) {
	Renderer::setMaterial(mat);
	modelMatrixLocation = material->specializedProgram->getUniformLocation("modelMatrix");
}

void WorldRenderer::render() {
	if (world == nullptr) return;

	isTransparent = material->specializedProgram->getRenderPass() == Engine::pipeline->renderPasses[1];
	for (std::pair<Vec3i, Chunk*> pair : world->chunks) {
		if (isTransparent && pair.second->transparentMesh == nullptr) continue;
		else if (!isTransparent && pair.second->opaqueMesh == nullptr) continue;
		Matrix4x4f chkModel = Matrix4x4f::translation(Vec3f(pair.second->position.x * CHUNK_SIZE, pair.second->position.y * CHUNK_SIZE, pair.second->position.z * CHUNK_SIZE));
		material->specializedProgram->loadMatrix4x4f(modelMatrixLocation, chkModel);

		if (isTransparent) {
			pair.second->transparentMesh->render();
		} else {
			pair.second->opaqueMesh->render();
		}
	}

}
