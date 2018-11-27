#version 410

layout(location = 0) in vec3 vertex_position;
uniform float x;
uniform float y;

void main() {
	gl_Position = vec4(vertex_position + vec3(x,y,0), 1.0);
}
