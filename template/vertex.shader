#version 330 core

layout(location = 0) in vec3 position;
layout(location = 1) in vec3 normal;
layout(location = 2) in vec2 UV;
layout(location = 3) in vec3 aOffset;

uniform mat4 model_matrix;
uniform mat4 view_matrix;
uniform mat4 projection_matrix;
uniform mat4 light_matrix;

out vec3 outNormal;
out vec2 outUV;
out vec3 fragPosition;
out vec4 fragPosLightSpace;

void main()
{
	fragPosition = vec3(model_matrix * vec4(position, 1.0f));
	outNormal = vec3(transpose(inverse(model_matrix)) * vec4(normal, 1.0f));
	
	outUV = UV;

	fragPosLightSpace = light_matrix * vec4(fragPosition, 1.0);
	gl_Position = projection_matrix * view_matrix * model_matrix * vec4(position, 1.0f);
	//gl_Position = projection_matrix * view_matrix * model_matrix * vec4(position + aOffset, 1.0f);
}