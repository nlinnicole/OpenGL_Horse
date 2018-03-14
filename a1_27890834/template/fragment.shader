#version 330 core

uniform vec4 color = vec4(1.0, 1.0, 1.0, 1.0);
uniform vec3 lightPos;
uniform vec3 cameraPos;

uniform int hasTexture;

uniform sampler2D tex;
uniform sampler2D shadow;

out vec4 outputF;

in vec3 outNormal;
in vec3 fragPosition;
in vec2 outUV;
in vec4 fragPosLightSpace;

void main()
{
	vec4 texCol = texture(tex, outUV);
	vec3 lightCol = vec3(1.0, 1.0, 1.0);

	//AMBIENT LIGHT
	float amb = 0.15f;
	vec3 ambient = amb * lightCol;

	//DIffUSE LIGHT
	vec3 ld = normalize(lightPos - fragPosition);
	vec3 n = normalize(outNormal);
	float angle = dot(n, ld);
	float diff = max(0.0, angle);
	vec3 diffuse = diff * lightCol;

	//SPECULAR LIGHT
	vec3 vd = normalize(cameraPos - fragPosition);
	vec3 rf = reflect(-ld, n);
	float an = dot(rf, vd);
	float spec = max(an, 0.0);
	vec3 specular = 0.5f * pow(spec, 256.0) * lightCol;

	//SHADOW
	//float shadow = shadowCalc(fragPosLightSpace);

	vec4 lightResult = vec4(diffuse + ambient + specular, 1);
	//vec4 lightResult = (ambient + (1.0 - shadow) * (diffuse + specular));

	if (hasTexture == 1) {
		outputF = lightResult * texCol;
	}
	else {
		outputF = lightResult * color;
	}
}

//float shadowCalc(vec4 fragPosLightSpace) {
//	vec3 projCoords = fragPosLightSpace.xyz / fragPosLightSpace.w;
//	projCoords = projCoords * 0.5 + 0.5;
//	float closestDepth = texture(shadow, projCoords.xy).r;
//	float currentDepth = projCoords.z;
//	float shadow = currentDepth > closestDepth ? 1.0 : 0.0;
//	return shadow;
//}