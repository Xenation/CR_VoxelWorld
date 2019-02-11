#version 400

layout (location = 0) in vec4 vertexPos;
layout (location = 1) in uint voxelType;

uniform mat4x4 projectionMatrix;
uniform mat4x4 viewMatrix;
uniform mat4x4 modelMatrix;

out vec4 worldPos;
out vec4 vColor;

const vec4 typeColors[4] = vec4[](
	vec4(0, 0, 0, 0),
	vec4(0.631, 0.631, 0.631, 1.0),
	vec4(0.66, 0.40, 0.21, 1.0),
	vec4(0.454, 0.717, 0.341, 1.0)
);

void main() {
	vColor = typeColors[voxelType];
	worldPos = modelMatrix * vec4(vertexPos.xyz, 1.0);
	gl_Position = projectionMatrix * viewMatrix * worldPos;
}
