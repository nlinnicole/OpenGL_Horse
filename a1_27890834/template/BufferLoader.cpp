#include "stdafx.h"
#include "BufferLoader.h"

BufferLoader::BufferLoader()
{
	loadOBJ("cube.obj", hVertices, hNormals, hUvCoord);
	loadOBJ("plane.obj", gVertices, gNormals, gUvCoord);
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

GLuint BufferLoader::getAxisVAO() {
	return VAO[1];
}

GLuint BufferLoader::getGroundVAO() {
	return VAO[2];
}

//GLuint BufferLoader::getGridVAO() {
//	return VAO[3];
//}

void BufferLoader::setHorseVAO() {
	glGenVertexArrays(1, &VAO[0]);
	glBindVertexArray(VAO[0]);

	glGenBuffers(1, &VBO[0]);
	glBindBuffer(GL_ARRAY_BUFFER, VBO[0]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(glm::vec3)*hVertices.size(), &hVertices[0], GL_STATIC_DRAW);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
	glEnableVertexAttribArray(0);

	//VBOnormals
	glGenBuffers(1, &VBO[1]);
	glBindBuffer(GL_ARRAY_BUFFER, VBO[1]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(glm::vec3)*hNormals.size(), &hNormals[0], GL_STATIC_DRAW);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, 0);
	glEnableVertexAttribArray(1);

	//UV
	glGenBuffers(1, &VBO[2]);
	glBindBuffer(GL_ARRAY_BUFFER, VBO[2]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(glm::vec2)*hUvCoord.size(), &hUvCoord[0], GL_STATIC_DRAW);
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 0, 0);
	glEnableVertexAttribArray(2);
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
	glGenBuffers(1, &VBO[3]);
	glBindBuffer(GL_ARRAY_BUFFER, VBO[3]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(axis), axis, GL_STATIC_DRAW);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), (GLvoid*)0);
	glEnableVertexAttribArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);
}

void BufferLoader::setGroundVAO() {
	glGenVertexArrays(1, &VAO[2]);
	glBindVertexArray(VAO[2]);

	glGenBuffers(1, &VBO[4]);
	glBindBuffer(GL_ARRAY_BUFFER, VBO[4]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(glm::vec3)*gVertices.size(), &gVertices[0], GL_STATIC_DRAW);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
	glEnableVertexAttribArray(0);

	//VBOnormals
	glGenBuffers(1, &VBO[5]);
	glBindBuffer(GL_ARRAY_BUFFER, VBO[5]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(glm::vec3)*gNormals.size(), &gNormals[0], GL_STATIC_DRAW);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, 0);
	glEnableVertexAttribArray(1);

	//UV
	glGenBuffers(1, &VBO[6]);
	glBindBuffer(GL_ARRAY_BUFFER, VBO[6]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(glm::vec2)*gUvCoord.size(), &gUvCoord[0], GL_STATIC_DRAW);
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 0, 0);
	glEnableVertexAttribArray(2);
}

//void BufferLoader::setGridVAO() {
//	for (int i = -100; i < 100; ++i) {
//		float x = i;
//		float y = 0;
//		float z = 100;
//		ground.push_back(glm::vec3(x, y, z));
//		x = i;
//		z = -100;
//		ground.push_back(glm::vec3(x, y, z));
//	}
//	for (int i = -100; i < 100; ++i) {
//		float x = 100;
//		float y = 0;
//		float z = i;
//		ground.push_back(glm::vec3(x, y, z));
//		x = -100;
//		z = i;
//		ground.push_back(glm::vec3(x, y, z));
//	}
//	
//	glGenVertexArrays(1, &VAO[3]);
//	glBindVertexArray(VAO[3]);
//	glGenBuffers(1, &VBO[7]);
//	glBindBuffer(GL_ARRAY_BUFFER, VBO[7]);
//	glBufferData(GL_ARRAY_BUFFER, sizeof(glm::vec3)*ground.size(), &ground[0], GL_STATIC_DRAW);
//	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
//	glEnableVertexAttribArray(0);
//	glBindBuffer(GL_ARRAY_BUFFER, 0);
//	glBindVertexArray(0);
//}

void BufferLoader::loadTex() {

	glGenTextures(2, tex);
	int width, height;
	unsigned char* image;

	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, tex[0]);
	image = SOIL_load_image("horseTEX.jpg", &width, &height, 0, SOIL_LOAD_RGB);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, image);
	SOIL_free_image_data(image);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);

	//glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, tex[1]);
	image = SOIL_load_image("groundTEX.jpg", &width, &height, 0, SOIL_LOAD_RGB);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, image);
	SOIL_free_image_data(image);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
}

GLuint BufferLoader::getHorseTex() {
	return tex[0];
}

GLuint BufferLoader::getGroundTex() {
	return tex[1];
}