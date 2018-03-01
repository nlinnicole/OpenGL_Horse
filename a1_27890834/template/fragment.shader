#version 330 core

uniform vec4 color = vec4(1.0, 1.0, 1.0, 1.0);
out vec4 outputF;

in vec3 fragPosition;
in vec3 outNormal;

void main()
{
	//vec3 lightColor = vec3(0.0f, 1.0f, 0.0f);
	//
	////AMBIENT LIGHT
	//float amb_strength = 0.5f;
	//vec3 amb_contribution = amb_strength * lightColor;

	////DIFFUSE LIGHT
	//vec3 light_position = vec3(0.0f, 20.0f, 0.0f);
	//vec3 norm = normalize(outNormal);
	//vec3 light_direction = normalize(light_position - fragPosition);
	//float degree = max(dot(norm, light_direction), 0.0f);
	//vec3 diffuse_contribution = degree * lightColor;

	//vec3 result_color = (amb_contribution + diffuse_contribution) * color;
	//outputF = result_color;

	outputF = color;
}