#version 330 core

uniform vec4 color = vec4(1.0, 1.0, 1.0, 1.0);
uniform vec3 lightPos;
uniform vec3 cameraPos;

uniform int renderStyle;

uniform sampler2D tex;
uniform sampler2D shadowMap;

in vec3 outNormal;
in vec3 fragPosition;
in vec2 outUV;
in vec4 fragPosLightSpace;

out vec4 outputF;

float shadowCalc(vec4 fragPosLightSpace) {
	float shadowVal = 0.0;
	vec3 projCoords = fragPosLightSpace.xyz / fragPosLightSpace.w;
	projCoords = projCoords * 0.5 + 0.5;

	float closestDepth = texture(shadowMap, projCoords.xy).r;
	float currentDepth = projCoords.z;
	shadowVal = currentDepth > closestDepth ? 1.0 : 0.0;
	return shadowVal;
}

void main()
{
	vec2 UV2 = outUV;
	UV2 = UV2 * 3 + 3;
	vec4 texCol = texture(tex, UV2);
	vec3 lightCol = vec3(1.0, 1.0, 1.0);

	//AMBIENT LIGHT
	float amb = 0.15;
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
	vec3 specular = 0.5 * pow(spec, 256.0) * lightCol;

	//SHADOW
	float sh = shadowCalc(fragPosLightSpace);
	float shadow = 1 - sh;
	vec4 lightResult = vec4(diffuse + ambient + specular, 1);

	//vec4 shadowLightResult = vec4(ambient + shadow * (diffuse + specular), 1);
	vec4 shadowLightResult = vec4(ambient + (shadow * diffuse) + (shadow * specular), 1);

	if (renderStyle == 1) {
		//Texture, no shadow
		outputF = lightResult * texCol;
	}
	else if (renderStyle == 2){
		//No texture, shadow
		outputF = shadowLightResult * color;
	}
	else if (renderStyle == 3) {
		//Texture and shadow
		outputF = shadowLightResult * texCol;
	}
	else {
		outputF = lightResult * color;
	}
}

