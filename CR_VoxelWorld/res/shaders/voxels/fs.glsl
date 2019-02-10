#version 400

in vec3 worldPos;
in vec3 normal;

out vec4 fragColor;

void main() {
	fragColor = vec4(vec3(.66, .40, .21) * max(0.1, dot(normal, normalize(vec3(1.5, -2, -1)))), 1.0);
}
