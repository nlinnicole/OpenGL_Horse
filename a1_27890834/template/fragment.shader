#version 330 core

uniform vec4 color = vec4(1.0, 1.0, 1.0, 1.0);
uniform vec3 lightPos;
uniform vec3 cameraPos;

uniform sampler2D tex;

out vec4 outputF;

in vec3 outNormal;
in vec3 fragPosition;
in vec2 outUV;

void main()
{
	vec4 texCol = texture(tex, outUV);
	vec3 lightCol = vec3(1.0, 1.0, 1.0);
	vec3 ambient = 0.3 * lightCol;

	vec3 ld = normalize(lightPos - fragPosition);
	vec3 n = normalize(outNormal);
	float angle = dot(n, ld);
	float diff = max(0.0, angle);
	vec3 diffuse = diff * lightCol;

	vec3 vd = normalize(cameraPos - fragPosition);
	vec3 rf = reflect(-ld, n);
	float an = dot(rf, vd);
	float spec = max(an, 0.0);
	vec3 specular = 0.5f * pow(spec, 256.0) * lightCol;

	vec4 result = vec4(diffuse + ambient + specular, 1);
	//outputF = result * texCol;
	outputF = result * color;

}