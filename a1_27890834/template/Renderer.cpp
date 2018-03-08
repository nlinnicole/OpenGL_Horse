#include "stdafx.h"
#include "Renderer.h"


Renderer::Renderer()
{

}

Renderer::Renderer(GLuint tl, GLuint cl, GLuint texL, GLuint sp, Horse h)
{
	transformLoc = tl;
	colorLoc = cl;
	shaderProgram = sp;
	texLoc = texL;
	this->h = h;
}

Renderer::~Renderer()
{
}

void Renderer::setTransformLoc(GLuint t) {
	transformLoc = t;
}

void Renderer::setColorLoc(GLuint c) {
	colorLoc = c;
}

void Renderer::setVAO(GLuint v) {
	VAO = v;
	glBindVertexArray(VAO);
}

void Renderer::setShaderProgram(GLuint sp) {
	shaderProgram = sp;
}

void Renderer::setMode(GLenum m) {
	mode = m;
}

GLuint Renderer::getTransformLoc() {
	return transformLoc;
}

GLuint Renderer::getColorLoc() {
	return colorLoc;
}

GLuint Renderer::getVAO() {
	return VAO;
}

GLuint Renderer::getShaderProgram() {
	return shaderProgram;
}

void Renderer::horseInit() {

}

void Renderer::drawHorse(GLenum renderMode) {
	for (int i = 0; i < h.components.size(); ++i) {
		glProgramUniform4fv(shaderProgram, colorLoc, 1, h.components[i]->colour);
		glUniformMatrix4fv(transformLoc, 1, GL_FALSE, glm::value_ptr(h.components[i]->matrix));
		glDrawArrays(renderMode, 0, 12 * 3);
	}
};

void Renderer::drawGround(float colValues[4], glm::mat4 matrix) {
	glProgramUniform4fv(shaderProgram, colorLoc, 1, colValues);
	glUniformMatrix4fv(transformLoc, 1, GL_FALSE, glm::value_ptr(matrix));
	glDrawArrays(GL_LINES, 0, 800);
};

void Renderer::drawAxis(glm::vec3 colours, glm::mat4 matrix, int i) {
	float colValues[4] = { colours.x, colours.y, colours.z , 1.0f};
	glProgramUniform4fv(shaderProgram, colorLoc, 1, colValues);
	glUniformMatrix4fv(transformLoc, 1, GL_FALSE, glm::value_ptr(matrix));
	glDrawArrays(GL_LINES, i, 2);
};


void Renderer::loadTex() {
	glActiveTexture(GL_TEXTURE0);

	GLuint horseTex;
	glGenTextures(1, &horseTex);
	glBindTexture(GL_TEXTURE_2D, horseTex);
	glEnableVertexAttribArray(texLoc);
	glVertexAttribPointer(texLoc, 2, GL_FLOAT, GL_FALSE, 7 * sizeof(float), (void*)(5 * sizeof(float)));

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	int texWidth, texHeight;
	unsigned char* image = SOIL_load_image("ground_tex.jpg", &texWidth, &texHeight, 0, SOIL_LOAD_RGB);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, texWidth, texHeight, 0, GL_RGB, GL_UNSIGNED_BYTE, image);
	SOIL_free_image_data(image);
}