#pragma once
#include "objloader.hpp"
#include "SOIL.h"
#include <stdio.h>
#include <iostream>

class BufferLoader
{
public:
	BufferLoader();
	~BufferLoader();

	GLuint getCubeVAO();
	GLuint getGroundVAO();
	GLuint getAxisVAO();
	GLuint getGridVAO();
	GLuint getTreeVAO();

	GLuint getFBO();
	GLuint getDepthMap();

	GLuint getHorseTex();
	GLuint getGroundTex();
	GLuint getSkyTex();

	void loadTex();
	void loadDepthMap();
	void loadSkybox();

	glm::vec3 translations[20];

private:
	GLuint VAO[5];
	GLuint VBO[13];
	GLuint EBO;
	GLuint tex[2];
	GLuint skyTex;

	GLuint FBO;
	GLuint depthMap;

	std::vector<glm::vec3> hVertices;
	std::vector<glm::vec3> hNormals;
	std::vector<glm::vec2> hUvCoord;

	std::vector<glm::vec3> gVertices;
	std::vector<glm::vec3> gNormals;
	std::vector<glm::vec2> gUvCoord;

	std::vector<glm::vec3> tVertices;
	std::vector<glm::vec3> tNormals;
	std::vector<glm::vec2> tUvCoord;

	std::vector<glm::vec3> ground;

	void setCubeVAO();
	void setGroundVAO();
	void setAxisVAO();
	void setTreeVAO();
	void setInstancing();
};

