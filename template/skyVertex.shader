#version 330

layout(location = 0) in vec3 vertex;
//in vec3 vertex;

out vec3 outUV;

uniform mat4 model_matrix;
uniform mat4 view_matrix;
uniform mat4 projection_matrix;

void main() {
	outUV = vertex;

	gl_Position = projection_matrix * view_matrix * model_matrix * vec4(vertex, 1.0f);
}