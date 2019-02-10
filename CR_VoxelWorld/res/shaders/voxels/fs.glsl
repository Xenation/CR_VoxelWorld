#version 400

in vec3 normal;
in vec4 color;

out vec4 fragColor;

void main() {
	fragColor = color * max(0.1, dot(normal, normalize(vec3(1.5, -2, -1))));
}
