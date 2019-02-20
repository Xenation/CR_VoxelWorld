#version 420

in vec3 normal;
in vec4 color;

out vec4 fragColor;

void main() {
	vec3 lightDir = normalize(vec3(1.5, -2, -1));
	vec4 diffuse = vec4(color.rgb * max(0.2, dot(normal, lightDir)), color.a);

	//float spec = dot(normalize(vec3(0, -1, 1)), normalize(lightDir + normal));
	
	fragColor = diffuse;
}
