#version 420
#pragma pass opaque

layout (location = 0) in vec3 vertexPos;

layout (std140, binding = 1) uniform CameraMatrices {
	mat4x4 projectionMatrix;
	mat4x4 viewMatrix;
	ivec2 resolution;
};

layout (std140, binding = 10) uniform Material {
	vec4 color;
};

uniform mat4x4 modelMatrix;

out vec4 vColor;

void main() {
	vColor = color;
	gl_Position = projectionMatrix * viewMatrix * modelMatrix * vec4(vertexPos, 1.0);
}
