#include "stdafx.h"
#include "Renderer.h"


Renderer::Renderer()
{

}

Renderer::Renderer(GLuint tl, GLuint cl, GLuint sp, GLuint txL, Horse h)
{
	transformLoc = tl;
	colorLoc = cl;
	shaderProgram = sp;
	texLoc = txL;
	horse = h;
}

Renderer::~Renderer()
{
}

void Renderer::setShaderProgram(GLuint sp) {
	shaderProgram = sp;
}

void Renderer::setTransformLoc(GLuint tl) {
	transformLoc = tl;
}

void Renderer::setVAO(GLuint v) {
	VAO = v;
	glBindVertexArray(VAO);
}

void Renderer::drawHorse(GLenum renderMode, GLuint texture) {
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, texture);
	glUniform1i(texLoc, 0);
	for (int i = 0; i < horse.components.size(); ++i) {
		glProgramUniform4fv(shaderProgram, colorLoc, 1, horse.components[i]->colour);
		glUniformMatrix4fv(transformLoc, 1, GL_FALSE, glm::value_ptr(horse.components[i]->matrix));
		glDrawArrays(renderMode, 0, 12 * 3);
	}
};

void Renderer::drawGround(float colValues[4], glm::mat4 matrix, GLuint texture) {
	glm::mat4 translate = glm::translate(matrix, glm::vec3(-50.0f, 0.0f, -50.0f));
	matrix *= translate;
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, texture);
	glUniform1i(texLoc, 0);
	glProgramUniform4fv(shaderProgram, colorLoc, 1, colValues);
	glUniformMatrix4fv(transformLoc, 1, GL_FALSE, glm::value_ptr(matrix));
	glDrawArrays(GL_TRIANGLES, 0, 800);
};

void Renderer::drawAxis(glm::vec3 colours, glm::mat4 matrix, int i) {
	float colValues[4] = { colours.x, colours.y, colours.z , 1.0f};
	glProgramUniform4fv(shaderProgram, colorLoc, 1, colValues);
	glUniformMatrix4fv(transformLoc, 1, GL_FALSE, glm::value_ptr(matrix));
	glDrawArrays(GL_LINES, i, 2);
};

void Renderer::drawSkyBox(glm::mat4 matrix, GLuint texture, GLuint transformLoc, GLuint skyTexLoc) {
	//glm::mat4 scale = glm::scale(matrix, glm::vec3(5.0, 5.0, 5.0));
	//matrix *= scale;
	glActiveTexture(GL_TEXTURE1);
	glBindTexture(GL_TEXTURE_CUBE_MAP, texture);
	glUniform1i(skyTexLoc, 1);
	glUniformMatrix4fv(transformLoc, 1, GL_FALSE, glm::value_ptr(matrix));
	glDrawArrays(GL_TRIANGLES, 0, 12 * 3);
}
