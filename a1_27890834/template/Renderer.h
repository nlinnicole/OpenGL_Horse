#pragma once
#include "stdafx.h"
#include "glm.hpp"
#include "gtc/matrix_transform.hpp"
#include "gtc/type_ptr.hpp"
#include "Horse.h"


class Renderer
{
public:
	Renderer();
	Renderer(GLuint transformLoc, GLuint colorLoc, GLuint shaderProgram, Horse h);
	~Renderer();
	
	void setTransformLoc(GLuint t);
	void setColorLoc(GLuint c);
	void setVAO(GLuint v);
	void setShaderProgram(GLuint sP);
	void setMode(GLenum m);

	void drawHorse(GLenum renderMode);
	void drawGround(float colValues[4], glm::mat4 matrix);
	void drawAxis(glm::vec3 colours, glm::mat4 matrix, int i);
	
private:
	GLuint transformLoc;
	GLuint colorLoc;
	GLuint VAO;
	GLuint shaderProgram;
	GLenum mode;

	Horse h;

	GLuint getTransformLoc();
	GLuint getColorLoc();
	GLuint getVAO();
	GLuint getShaderProgram();
	void horseInit();
};

