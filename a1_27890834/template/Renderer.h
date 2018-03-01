#pragma once
#include "stdafx.h"
#include "glm.hpp"
#include "gtc/matrix_transform.hpp"
#include "gtc/type_ptr.hpp"


class Renderer
{
public:
	Renderer();
	Renderer(GLuint transformLoc, GLuint colorLoc, GLuint VAO, GLuint shaderProgram);
	~Renderer();
	
	void setTransformLoc(GLuint t);
	void setColorLoc(GLuint c);
	void setVAO(GLuint V);
	void setShaderProgram(GLuint sP);
	void setMode(GLenum m);

	void drawCube(float colValues[4], glm::mat4 matrix);
	void drawGround(float colValues[4], glm::mat4 matrix);
	void drawAxis(float colValues[4], glm::mat4 matrix, int n);
	
private:
	GLuint transformLoc;
	GLuint colorLoc;
	GLuint VAO;
	GLuint shaderProgram;
	GLenum mode;

	GLuint getTransformLoc();
	GLuint getColorLoc();
	GLuint getVAO();
	GLuint getShaderProgram();
};

