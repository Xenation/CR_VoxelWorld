#version 400

layout(triangles) in;
layout(triangle_strip, max_vertices = 3) out;

in vec4 worldPos[];
in vec4 vColor[];

out vec3 normal;
out vec4 color;

void main() {
	normal = normalize(cross(worldPos[1].xyz - worldPos[0].xyz, worldPos[2].xyz - worldPos[0].xyz));
	
	gl_Position = gl_in[0].gl_Position;
	color = vColor[0];
	EmitVertex();
	gl_Position = gl_in[1].gl_Position;
	color = vColor[1];
	EmitVertex();
	gl_Position = gl_in[2].gl_Position;
	color = vColor[2];
	EmitVertex();

	EndPrimitive();
}
