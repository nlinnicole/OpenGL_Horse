#include "stdafx.h"
#include "Renderer.h"


Renderer::Renderer()
{

}

Renderer::Renderer(GLuint tl, GLuint cl, GLuint sp)
{
	transformLoc = tl;
	colorLoc = cl;
	shaderProgram = sp;
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

void Renderer::drawCube(float colValues[4], glm::mat4 matrix) {
	glProgramUniform4fv(shaderProgram, colorLoc, 1, colValues);
	glUniformMatrix4fv(transformLoc, 1, GL_FALSE, glm::value_ptr(matrix));
	glDrawArrays(mode, 0, 12 * 3);
};

void Renderer::drawGround(float colValues[4], glm::mat4 matrix) {
	glProgramUniform4fv(shaderProgram, colorLoc, 1, colValues);
	glUniformMatrix4fv(transformLoc, 1, GL_FALSE, glm::value_ptr(matrix));
	glDrawArrays(GL_LINES, 0, 800);
};

void Renderer::drawAxis(float colValues[4], glm::mat4 matrix, int n) {
	glProgramUniform4fv(shaderProgram, colorLoc, 1, colValues);
	glUniformMatrix4fv(transformLoc, 1, GL_FALSE, glm::value_ptr(matrix));
	glDrawArrays(GL_LINES, n, 2);
	//put drawAxis in a for loop and increment n 
};