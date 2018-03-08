#version 330 core

uniform vec4 color = vec4(1.0, 1.0, 1.0, 1.0);
out vec4 outputF;

in vec3 outNormal;
in vec3 fragPosition;
in vec2 outUV;

uniform sampler2D tex;

void main()
{
	//mat3 normalMatrix = transpose(inverse(mat3(model_matrix)));
	//vec3 normal = normalize(normalMatrix * fragNormal);

	//vec3 fragPosition = vec3(model_matrix * vec4(fragVert, 1));

	//vec3 surfaceToLight = light.position - fragPosition;

	//float brightness = dot(normal, surfaceToLight) / (length(surfaceToLight) * length(normal));
	//brightness = clamp(brightness, 0, 1);

	//outputF = vec4(brightness * light.intensities);


	//vec3 lightColor = vec3(0.0f, 1.0f, 0.0f);
	
	//AMBIENT LIGHT
	//float amb_strength = 0.5f;
	//vec3 amb_contribution = amb_strength * lightColor;

	////DIFFUSE LIGHT
	//vec3 light_position = vec3(0.0f, 20.0f, 0.0f);
	//vec3 norm = normalize(outNormal);
	//vec3 light_direction = normalize(light_position - fragPosition);
	//float degree = max(dot(norm, light_direction), 0.0f);
	//vec3 diffuse_contribution = degree * lightColor;

	//vec3 result_color = (amb_contribution + diffuse_contribution) * color;
	//outputF = vec4(result_color, 1.0f);


	outputF = color;
	//outputF = texture(tex, outUV);
}