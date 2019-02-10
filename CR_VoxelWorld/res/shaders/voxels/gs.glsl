#version 400

layout(triangles) in;
layout(triangle_strip, max_vertices = 3) out;

in vec4 worldPos[];

out vec3 normal;
out vec3 fWorldPos;

void main() {
	normal = normalize(cross(worldPos[1].xyz - worldPos[0].xyz, worldPos[2].xyz - worldPos[0].xyz));

	gl_Position = gl_in[0].gl_Position;
	fWorldPos = worldPos[0].xyz;
	EmitVertex();
	gl_Position = gl_in[1].gl_Position;
	fWorldPos = worldPos[1].xyz;
	EmitVertex();
	gl_Position = gl_in[2].gl_Position;
	fWorldPos = worldPos[2].xyz;
	EmitVertex();

	EndPrimitive();
}
