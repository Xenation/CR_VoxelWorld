#version 420

in vec3 normal;
in vec4 color;

layout (std140, binding = 10) uniform Material {
	mat4x4 modelMatrix;
	vec4 liDir;
	float ambient;
};

out vec4 fragColor;

void main() {
	vec3 lightDir = normalize(liDir.xyz);
	vec4 diffuse = vec4(color.rgb * max(ambient, dot(normal, lightDir)), color.a);
	//float spec = dot(normalize(vec3(0, -1, 1)), normalize(lightDir + normal));
	
	fragColor = diffuse;
}
