#version 330 core
out vec4 fragColor;

in vec2 outUV;

uniform sampler2D depthMap;

void main()
{
	float depthValue = texture(depthMap, outUV).r;
	fragColor = vec4(vec3(depthValue), 1.0);
}