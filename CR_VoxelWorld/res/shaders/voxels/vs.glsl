#version 400

layout (location = 0) in vec4 vertexPos;
layout (location = 1) in uint voxelType;

uniform mat4x4 projectionMatrix;
uniform mat4x4 viewMatrix;
uniform mat4x4 modelMatrix;

out vec4 worldPos;
out vec4 vColor;

const vec4 typeColors[5] = vec4[](
	vec4(0, 0, 0, 0),
	vec4(0.631, 0.631, 0.631, 1.0),
	vec4(0.660, 0.400, 0.210, 1.0),
	vec4(0.454, 0.717, 0.341, 1.0),
	vec4(0.223, 0.356, 0.917, 1.0)
);

void main() {
	vColor = typeColors[voxelType];
	worldPos = modelMatrix * vec4(vertexPos.xyz, 1.0);
	if (voxelType == 4) {
		worldPos.y -= 0.1;
	}
	gl_Position = projectionMatrix * viewMatrix * worldPos;
}
