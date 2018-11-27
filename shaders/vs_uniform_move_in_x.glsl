#version 410

layout(location = 0) in vec3 vertex_position;
uniform float x;
vec3 vertexPosition = vec3(x,0.0,0.0);

void main() {
	gl_Position = vec4(vertex_position + vertexPosition, 1.0);
}
