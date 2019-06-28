#version 420
#pragma pass opaque transparent

layout (location = 0) in vec4 vertexPos;
layout (location = 1) in uint voxelType;

layout (std140, binding = 1) uniform CameraMatrices {
	mat4x4 projectionMatrix;
	mat4x4 viewMatrix;
	ivec2 resolution;
	uint sampleCount;
};
layout (std140, binding = 2) uniform GlobalVariables {
	float time;
};

layout (std140, binding = 10) uniform Material {
	vec4 liDir;
	float ambient;
};

uniform mat4x4 modelMatrix;

out vec4 worldPos;
out vec4 vColor;

const vec4 typeColors[5] = vec4[](
	vec4(0, 0, 0, 0),
	vec4(0.631, 0.631, 0.631, 1.0),
	vec4(0.660, 0.400, 0.210, 1.0),
	vec4(0.454, 0.717, 0.341, 1.0),
	vec4(0.223, 0.356, 0.917, 0.7)
);

void main() {
	vColor = typeColors[voxelType];
	worldPos = modelMatrix * vec4(vertexPos.xyz, 1.0);
	if (voxelType == 4) {
		worldPos.y -= 0.2;
		worldPos.y += sin(time + worldPos.x + worldPos.z) * 0.15;
		worldPos.y += sin(time * 2 + worldPos.x * 0.6) * 0.05;
	}
	gl_Position = projectionMatrix * viewMatrix * worldPos;
}
