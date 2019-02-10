#version 400

layout (location = 0) in vec3 vertexPos;
layout (location = 1) in vec4 color;

uniform mat4x4 projectionMatrix;
uniform mat4x4 viewMatrix;
uniform mat4x4 modelMatrix;

out vec4 worldPos;
out vec4 vColor;

void main() {
	vColor = color;
	worldPos = modelMatrix * vec4(vertexPos, 1.0);
	gl_Position = projectionMatrix * viewMatrix * worldPos;
}
