#version 330

in vec3 outUV;

out vec4 fragColor;

uniform samplerCube tex;

void main() {
	fragColor = texture(tex, outUV);
}