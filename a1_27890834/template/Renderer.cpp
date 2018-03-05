#include "stdafx.h"
#include "Renderer.h"


Renderer::Renderer()
{

}

Renderer::Renderer(GLuint tl, GLuint cl, GLuint sp, Horse h)
{
	transformLoc = tl;
	colorLoc = cl;
	shaderProgram = sp;
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

void Renderer::drawHorse() {
	for (int i = 0; i < h.components.size(); ++i) {
		glProgramUniform4fv(shaderProgram, colorLoc, 1, h.components[i]->colour);
		glUniformMatrix4fv(transformLoc, 1, GL_FALSE, glm::value_ptr(h.components[i]->matrix));
		glDrawArrays(GL_TRIANGLES, 0, 12 * 3);
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