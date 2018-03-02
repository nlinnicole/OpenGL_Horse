#include "stdafx.h"
#include "BufferLoader.h"


BufferLoader::BufferLoader()
{
	setHorseVAO();
	setAxisVAO();
	setGroundVAO();
}

BufferLoader::~BufferLoader()
{
}

GLuint BufferLoader::getHorseVAO()
{
	return VAO[0];
}

GLuint BufferLoader::getGroundVAO() {
	return VAO[1];
}

GLuint BufferLoader::getAxisVAO() {
	return VAO[2];
}

void BufferLoader::setHorseVAO() {
	GLfloat horseVertices[] = {
		-1.0f,-1.0f,-1.0f, // Cube begin
		-1.0f,-1.0f, 1.0f,
		-1.0f, 1.0f, 1.0f,
		1.0f, 1.0f,-1.0f,
		-1.0f,-1.0f,-1.0f,
		-1.0f, 1.0f,-1.0f,
		1.0f,-1.0f, 1.0f,
		-1.0f,-1.0f,-1.0f,
		1.0f,-1.0f,-1.0f,
		1.0f, 1.0f,-1.0f,
		1.0f,-1.0f,-1.0f,
		-1.0f,-1.0f,-1.0f,
		-1.0f,-1.0f,-1.0f,
		-1.0f, 1.0f, 1.0f,
		-1.0f, 1.0f,-1.0f,
		1.0f,-1.0f, 1.0f,
		-1.0f,-1.0f, 1.0f,
		-1.0f,-1.0f,-1.0f,
		-1.0f, 1.0f, 1.0f,
		-1.0f,-1.0f, 1.0f,
		1.0f,-1.0f, 1.0f,
		1.0f, 1.0f, 1.0f,
		1.0f,-1.0f,-1.0f,
		1.0f, 1.0f,-1.0f,
		1.0f,-1.0f,-1.0f,
		1.0f, 1.0f, 1.0f,
		1.0f,-1.0f, 1.0f,
		1.0f, 1.0f, 1.0f,
		1.0f, 1.0f,-1.0f,
		-1.0f, 1.0f,-1.0f,
		1.0f, 1.0f, 1.0f,
		-1.0f, 1.0f,-1.0f,
		-1.0f, 1.0f, 1.0f,
		1.0f, 1.0f, 1.0f,
		-1.0f, 1.0f, 1.0f,
		1.0f,-1.0f, 1.0f //Cube end
	};

	glGenVertexArrays(1, &VAO[0]);
	glBindVertexArray(VAO[0]);
	glGenBuffers(1, &VBO[0]);
	glBindBuffer(GL_ARRAY_BUFFER, VBO[0]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(horseVertices), horseVertices, GL_STATIC_DRAW);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), (GLvoid*)0);
	glEnableVertexAttribArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);

	//std::vector<glm::vec3> normals;
	//for (int i = 0; i < sizeof(horseVertices); ++i) {
	//	glm::vec3 a, b;
	//	a.x = horseVertices[i];
	//	a.y = horseVertices[i + 1];
	//	a.y = horseVertices[i + 2];
	//	b.x = horseVertices[i + 3];
	//	b.y = horseVertices[i + 4];
	//	b.y = horseVertices[i + 5];
	//	glm::vec3 cross = glm::cross(a, b);
	//	cross = glm::normalize(cross);
	//	normals.push_back(cross);
	//}

	//glGenVertexArrays(1, &VAO[0]);
	//glBindVertexArray(VAO[0]);
	//glGenBuffers(1, &VBO[1]);
	//glBindBuffer(GL_ARRAY_BUFFER, VBO[1]);
	//glBufferData(GL_ARRAY_BUFFER, sizeof(glm::vec3)*normals.size(), &normals[0], GL_STATIC_DRAW);
	//glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, 0);
	//glEnableVertexAttribArray(0);
	//glBindBuffer(GL_ARRAY_BUFFER, 0);
	//glBindVertexArray(0);
}

void BufferLoader::setAxisVAO() {
	GLfloat axis[] = {
		0.0f, 0.0f, 0.0f,
		5.0f, 0.0f, 0.0f, //X-Axis
		0.0f, 0.0f, 0.0f,
		0.0f, 5.0f, 0.0f, //Y-Axis
		0.0f, 0.0f, 0.0f,
		0.0f, 0.0f, 5.0f //Z-Axis
	};

	glGenVertexArrays(1, &VAO[1]);
	glBindVertexArray(VAO[1]);
	glGenBuffers(1, &VBO[2]);
	glBindBuffer(GL_ARRAY_BUFFER, VBO[2]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(axis), axis, GL_STATIC_DRAW);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), (GLvoid*)0);
	glEnableVertexAttribArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);
}

void BufferLoader::setGroundVAO() {
	std::vector<glm::vec3> ground;
	for (int i = -100; i < 100; ++i) {
		float x = i;
		float y = 0;
		float z = 100;
		ground.push_back(glm::vec3(x, y, z));
		x = i;
		z = -100;
		ground.push_back(glm::vec3(x, y, z));
	}
	for (int i = -100; i < 100; ++i) {
		float x = 100;
		float y = 0;
		float z = i;
		ground.push_back(glm::vec3(x, y, z));
		x = -100;
		z = i;
		ground.push_back(glm::vec3(x, y, z));
	}

	glGenVertexArrays(1, &VAO[2]);
	glBindVertexArray(VAO[2]);
	glGenBuffers(1, &VBO[3]);
	glBindBuffer(GL_ARRAY_BUFFER, VBO[3]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(glm::vec3)*ground.size(), &ground[0], GL_STATIC_DRAW);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
	glEnableVertexAttribArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);
}
