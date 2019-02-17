#pragma once
#include <ZOrder.h>
#include "VMath.h"

inline unsigned int zorder(const Vec3c& vec) {
	return zorder(vec.x, vec.y, vec.z);
}
