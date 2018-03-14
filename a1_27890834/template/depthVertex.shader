#version 330 core

layout(location = 0) in vec3 pos;
layout(location = 1) in vec2 UV;

out vec2 outUV;

uniform mat4 light_matrix;
uniform mat4 model;

void main()
{
	gl_Position = light_matrix * model * vec4(pos, 1.0);

	outUV = UV;
}