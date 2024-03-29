#include "Chunk.h"

#include <Collider.h>
#include "World.h"



Chunk::Chunk(Vec3i pos, World* world) : position(pos), world(world) {
	linkAdjacentChunks();
	collider = Collider::empty;
}

Chunk::~Chunk() {
	unlinkAdjacentChunks();
	if (collider != Collider::empty) {
		delete collider;
	}
}


void Chunk::linkAdjacentChunks() {
	if (north == nullptr) {
		north = world->getChunkAt(position + Vec3i::north);
		if (north != nullptr) {
			north->south = this;
		}
	}
	if (east == nullptr) {
		east = world->getChunkAt(position + Vec3i::east);
		if (east != nullptr) {
			east->west = this;
		}
	}
	if (south == nullptr) {
		south = world->getChunkAt(position + Vec3i::south);
		if (south != nullptr) {
			south->north = this;
		}
	}
	if (west == nullptr) {
		west = world->getChunkAt(position + Vec3i::west);
		if (west != nullptr) {
			west->east = this;
		}
	}
	if (top == nullptr) {
		top = world->getChunkAt(position + Vec3i::up);
		if (top != nullptr) {
			top->bottom = this;
		}
	}
	if (bottom == nullptr) {
		bottom = world->getChunkAt(position + Vec3i::down);
		if (bottom != nullptr) {
			bottom->top = this;
		}
	}
}

void Chunk::unlinkAdjacentChunks() {
	if (north != nullptr) {
		north->south = nullptr;
	}
	if (east != nullptr) {
		east->west = nullptr;
	}
	if (south != nullptr) {
		south->north = nullptr;
	}
	if (west != nullptr) {
		west->east = nullptr;
	}
	if (top != nullptr) {
		top->bottom = nullptr;
	}
	if (bottom != nullptr) {
		bottom->top = nullptr;
	}
}
