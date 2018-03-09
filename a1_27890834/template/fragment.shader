#version 330 core

uniform vec4 color = vec4(1.0, 1.0, 1.0, 1.0);
out vec4 outputF;

in vec3 outNormal;
in vec3 fragPosition;
in vec2 outUV;

uniform sampler2D tex;

void main()
{


	//outputF = color;
	outputF = texture(tex, outUV);
}