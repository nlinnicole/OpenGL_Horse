//Nicole Lin 27890834
//COMP 371 Assignment 1

#include "stdafx.h"

#include "..\glew\glew.h"	// include GL Extension Wrangler
#include "..\glfw\glfw3.h"	// include GLFW helper library
#include "glm.hpp"
#include "gtc/matrix_transform.hpp"
#include "gtc/type_ptr.hpp"
#include "ShaderLoader.h"
#include "Renderer.h"

#include <stdio.h>
#include <iostream>
#include <string>
#include <fstream>
#include <stack>
#include <vector>

using namespace std;

// Window dimensions
//const GLfloat WIDTH = 800;
//const GLfloat HEIGHT = 800;
GLFWwindow* window;
int windowWidth = 800;
int windowHeight= 800;

//Gobal view variables
glm::vec3 c_pos = glm::vec3(0.0f, 3.0f, 15.0f);
glm::vec3 c_eye = glm::normalize(glm::vec3(0.0f, 0.0f, -15.0f));
glm::vec3 c_up = glm::vec3(0.0f, 1.0f, 0.0f);
glm::mat4 viewMatrix;
glm::mat4 projectionMatrix;

float zoom = 45.0f;

bool firstMouse = true;
float yaw = -90.0f;
float pitch = 0.0f;
float lastX = (float)windowWidth / 2.0;
float lastY = (float)windowHeight / 2.0;

float deltaTime = 0.0f;
float lastFrame = 0.0f;

float horizontalAngle = 3.14f;
float verticalAngle = 0.0f;
float speed = 3.0f;
float mouseSpeed = 0.0005f;

//Global horse variables
glm::vec3 horseScale = glm::vec3(2.0f, 1.0f, 1.0f);
glm::vec3 horseRotation = glm::vec3(0.0f, 0.0f, 1.0f);
glm::vec3 horseTranslation = glm::vec3(0.0f, 4.0f, 0.0f);
float horseRotateAngle = 0.0f;

GLenum renderMode = GL_TRIANGLES;

// Update view
void update() {
	viewMatrix = glm::lookAt(c_pos, c_pos + c_eye, c_up);
	glfwGetWindowSize(window, &windowWidth, &windowHeight);
	projectionMatrix = glm::perspective(zoom, (float)windowWidth / windowHeight, 0.0f, 100.0f);
}

// Is called whenever a key is pressed/released via GLFW
void key_callback(GLFWwindow* window, int key, int scancode, int action, int mode)
{
	std::cout << key << std::endl;
	if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
		glfwSetWindowShouldClose(window, GL_TRUE);

	//Move camera left
	if (key == GLFW_KEY_LEFT) {
		--c_pos.x;
		std::cout << c_pos.x << std::endl;
		update();
	}
	//Move camera right
	if (key == GLFW_KEY_RIGHT && action == GLFW_PRESS) {
		++c_pos.x;
		std::cout << c_pos.x << std::endl;
		update();
	}
	//Move camera up
	if (key == GLFW_KEY_UP && action == GLFW_PRESS) {
		++c_pos.y;
		std::cout << c_pos.y << std::endl;
		update();
	}
	//Move camera down
	if (key == GLFW_KEY_DOWN && action == GLFW_PRESS) {
		--c_pos.y;
		std::cout << c_pos.y << std::endl;
		update();
	}
	//Reset camera position
	if (key == GLFW_KEY_HOME && action == GLFW_PRESS) {
		c_pos = glm::vec3(0.0f, 3.0f, 15.0f);
		c_eye = glm::normalize(glm::vec3(0.0f, 0.0f, -15.0f));
		c_up = glm::vec3(0.0f, 1.0f, 0.0f);
		horseScale = glm::vec3(2.0f, 1.0f, 1.0f);
		horseRotation = glm::vec3(0.0f, 0.0f, 1.0f);
		horseTranslation = glm::vec3(0.0f, 4.0f, 0.0f);
		horseRotateAngle = 0.0f;
		update();
	}
	//Scale horse up
	if (key == GLFW_KEY_U && action == GLFW_PRESS) {
		horseScale.x += 0.2;
		horseScale.y += 0.1;
		horseScale.z += 0.1;
	}
	//Scale horse down
	if (key == GLFW_KEY_J && action == GLFW_PRESS) {
		horseScale.x -= 0.2;
		horseScale.y -= 0.1;
		horseScale.z -= 0.1;
	}
	//Move horse down
	if (key == GLFW_KEY_W && action == GLFW_PRESS) {
		if (mode == GLFW_MOD_SHIFT) {
			++horseTranslation.y;
		}
		//Rotate horse upwards on z axis
		else {
			horseRotation = glm::vec3(0.0f, 0.0f, 1.0f);
			horseRotateAngle += glm::radians(-5.0f);
		}
	}
	//Move horse left
	if (key == GLFW_KEY_A && action == GLFW_PRESS) {
		if (mode == GLFW_MOD_SHIFT) {
			--horseTranslation.x;
		}
		//Rotate horse left on y axis
		else {
			horseRotation = glm::vec3(0.0f, 1.0f, 0.0f);
			horseRotateAngle -= glm::radians(5.0f);
		}
	}
	//Move horse down
	if (key == GLFW_KEY_S && action == GLFW_PRESS) {
		if (mode == GLFW_MOD_SHIFT) {
			--horseTranslation.y;
		}
		//Rotate horse downwards on z axis
		else {
			horseRotation = glm::vec3(0.0f, 0.0f, 1.0f);
			horseRotateAngle += glm::radians(5.0f);
		}
	}
	//Move horse right
	if (key == GLFW_KEY_D && action == GLFW_PRESS) {
		if (mode == GLFW_MOD_SHIFT) {
			++horseTranslation.x;
		}
		//Rotate horse right on y axis
		else {
			horseRotation = glm::vec3(0.0f, 1.0f, 0.0f);
			horseRotateAngle += glm::radians(5.0f);
		}
	}
	//Re-position horse to a random position on grid
	if (key == GLFW_KEY_SPACE && action == GLFW_PRESS) {
		float randX = rand() % 50;
		float randZ = rand() % 50;
		horseTranslation = glm::vec3(randX, 0.0f, randZ);
		std::cout << horseTranslation.x << " " << horseTranslation.y << " " << horseTranslation.z << std::endl;
	}
	//Change render mode to points
	if (key == GLFW_KEY_P && action == GLFW_PRESS) {
		renderMode = GL_POINTS;
	}
	//Change render mode to lines
	if (key == GLFW_KEY_L && action == GLFW_PRESS) {
		renderMode = GL_LINES;
	}
	//Change render mode to triangles
	if (key == GLFW_KEY_T && action == GLFW_PRESS) {
		renderMode = GL_TRIANGLES;
	}
}

void mouse_callback(GLFWwindow* window, double xpos, double ypos){
	if (firstMouse) {
		lastX = xpos;
		lastY = ypos;
		firstMouse = false;
	}
	float xoffset = xpos - lastX;
	float yoffset = lastY - ypos;
	lastX = xpos;
	lastY = ypos;
	float sensitivity = 0.1f;

	if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT) == GLFW_PRESS) {
		//if (zoom >= 1.0f && zoom <= 45.0f)
		if (zoom >= 100.0f)
				zoom -= yoffset * deltaTime * sensitivity;
		if (zoom <= 100.0f)
			zoom += yoffset * deltaTime * sensitivity;
		update();
	}
	if ((glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_MIDDLE) || (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT) && (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_RIGHT)))) == GLFW_PRESS) {
		horizontalAngle += xoffset * deltaTime * sensitivity;
		verticalAngle += yoffset * deltaTime * sensitivity;
		if (verticalAngle > 89.0f)
			verticalAngle = 89.0f;
		if (verticalAngle < -89.0f)
			verticalAngle = -89.0f;
		c_eye = glm::vec3(cos(verticalAngle)*sin(horizontalAngle), sin(verticalAngle), cos(verticalAngle)*cos(horizontalAngle));
		glm::vec3 right = glm::vec3(sin(horizontalAngle - 3.14f / 2.0f), 0, cos(horizontalAngle - 3.14f / 2.0f));
		c_up = glm::cross(right, c_eye);;
		update();
	}
	if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_RIGHT) == GLFW_PRESS) {
		if (c_pos.x >= 100.0f) 
			c_pos.x -= xoffset * deltaTime * sensitivity;
		if (c_pos.x <= 100.0f)
			c_pos.x += xoffset * deltaTime * sensitivity;
		update();
	}
}

void framebuffer_size_callback(GLFWwindow* window, int width, int height) {
	glViewport(0, 0, width, height);
	windowWidth = width;
	windowHeight = height;
	update();
}

//Function to draw the horse
void drawHorse(GLuint shaderProgram, GLenum mode, GLuint VAO) {
	//Initial values
	float colValues[4] = { 0.0f, 0.0f, 0.0f, 1.0f };
	glm::mat4 scale;
	glm::mat4 translate;
	glm::mat4 rotate;

	GLuint transformLoc = glGetUniformLocation(shaderProgram, "model_matrix");
	GLuint colorLoc = glGetUniformLocation(shaderProgram, "color");

	//Transformation stack
	std::stack<glm::mat4> transformations;

	glBindVertexArray(0);
	glBindVertexArray(VAO);

	////TORSO
	glm::mat4 torso;
	scale = glm::scale(torso, horseScale);
	rotate = glm::rotate(torso, horseRotateAngle, horseRotation);
	translate = glm::translate(torso, horseTranslation);
	torso *= scale * rotate * translate;
	transformations.push(torso); //push torso to transformations
	colValues[0] = 0.275f;
	colValues[1] = 0.510f;
	colValues[2] = 0.706f;
	glProgramUniform4fv(shaderProgram, colorLoc, 1, colValues);
	glUniformMatrix4fv(transformLoc, 1, GL_FALSE, glm::value_ptr(torso));
	glDrawArrays(mode, 0, 12 * 3);

	//NECK
	glm::mat4 neck;
	scale = glm::scale(neck, glm::vec3(0.5f, 0.5f, 0.5f));
	rotate = glm::rotate(neck, glm::radians(-25.0f), glm::vec3(0.0f, 0.0f, 1.0f));
	translate = glm::translate(neck, glm::vec3(-3.2f, 0.5f, 0.0f));
	neck *= transformations.top() * scale * rotate * translate;
	transformations.push(neck); //push neck to transformations
	colValues[0] = 0.529f;
	colValues[1] = 0.808f;
	colValues[2] = 0.922f;
	glProgramUniform4fv(shaderProgram, colorLoc, 1, colValues);
	glUniformMatrix4fv(transformLoc, 1, GL_FALSE, glm::value_ptr(neck));
	glDrawArrays(mode, 0, 12 * 3);

	//HEAD
	glm::mat4 head;
	scale = glm::scale(head, glm::vec3(0.5f, 0.8f, 0.8f));
	rotate = glm::rotate(head, glm::radians(160.0f), glm::vec3(0.0f, 0.0f, 1.0f));
	translate = glm::translate(head, glm::vec3(1.0f, 2.0f, 0.0f));
	head *= transformations.top() * scale * rotate * translate; //use neck
	colValues[0] = 0.690f;
	colValues[1] = 0.878f;
	colValues[2] = 0.902f;
	glProgramUniform4fv(shaderProgram, colorLoc, 1, colValues);
	glUniformMatrix4fv(transformLoc, 1, GL_FALSE, glm::value_ptr(head));
	glDrawArrays(mode, 0, 12 * 3);

	//UPPER ARM L
	transformations.pop(); //pop neck from transformations
	glm::mat4 upperArmL;
	scale = glm::scale(upperArmL, glm::vec3(0.15f, 0.9f, 0.15f));
	translate = glm::translate(upperArmL, glm::vec3(-5.4f, -1.5f, 3.0f));
	upperArmL *= transformations.top() * scale * translate; //use torso
	transformations.push(upperArmL); //push upperArmL to transformations
	colValues[0] = 0.690f;
	colValues[1] = 0.769f;
	colValues[2] = 0.871f;
	glProgramUniform4fv(shaderProgram, colorLoc, 1, colValues);
	glUniformMatrix4fv(transformLoc, 1, GL_FALSE, glm::value_ptr(upperArmL));
	glDrawArrays(mode, 0, 12 * 3);

	//LOWER ARM L
	glm::mat4 lowerArmL;
	scale = glm::scale(lowerArmL, glm::vec3(1.2f, 1.0f, 1.2f));
	translate = glm::translate(lowerArmL, glm::vec3(0.0f, -2.0f, 0.0f));
	lowerArmL *= transformations.top() * scale * translate; //use UpperArmL
	colValues[0] = 0.392f;
	colValues[1] = 0.584f;
	colValues[2] = 0.929f;
	glProgramUniform4fv(shaderProgram, colorLoc, 1, colValues);
	glUniformMatrix4fv(transformLoc, 1, GL_FALSE, glm::value_ptr(lowerArmL));
	glDrawArrays(mode, 0, 12 * 3);

	//UPPER ARM R
	transformations.pop(); //pop UpperArmL
	glm::mat4 upperArmR;
	scale = glm::scale(upperArmR, glm::vec3(0.15f, 0.9f, 0.15f));
	translate = glm::translate(upperArmR, glm::vec3(-5.4f, -1.5f, -3.0f));
	upperArmR *= transformations.top() * scale * translate; //use torso
	transformations.push(upperArmR); // push upperArmR to transformations
	colValues[0] = 0.690f;
	colValues[1] = 0.769f;
	colValues[2] = 0.871f;
	glProgramUniform4fv(shaderProgram, colorLoc, 1, colValues);
	glUniformMatrix4fv(transformLoc, 1, GL_FALSE, glm::value_ptr(upperArmR));
	glDrawArrays(mode, 0, 12 * 3);

	//LOWER ARM R
	glm::mat4 lowerArmR;
	scale = glm::scale(lowerArmR, glm::vec3(1.2f, 1.0f, 1.2f));
	translate = glm::translate(lowerArmR, glm::vec3(0.0f, -2.0f, 0.0f));
	lowerArmR *= transformations.top() * scale * translate; //use UpperArmR
	colValues[0] = 0.392f;
	colValues[1] = 0.584f;
	colValues[2] = 0.929f;
	glProgramUniform4fv(shaderProgram, colorLoc, 1, colValues);
	glUniformMatrix4fv(transformLoc, 1, GL_FALSE, glm::value_ptr(lowerArmR));
	glDrawArrays(mode, 0, 12 * 3);

	//UPPER LEG L
	transformations.pop(); //pop UpperArmR
	glm::mat4 upperLegL;
	scale = glm::scale(upperLegL, glm::vec3(0.15f, 0.9f, 0.15f));
	translate = glm::translate(upperLegL, glm::vec3(5.4f, -1.5f, 3.0f));
	upperLegL *= transformations.top() * scale * translate; //use torso
	transformations.push(upperLegL); // push upperLegL to transformations
	colValues[0] = 0.690f;
	colValues[1] = 0.769f;
	colValues[2] = 0.871f;
	glProgramUniform4fv(shaderProgram, colorLoc, 1, colValues);
	glUniformMatrix4fv(transformLoc, 1, GL_FALSE, glm::value_ptr(upperLegL));
	glDrawArrays(mode, 0, 12 * 3);

	//LOWER LEG L
	glm::mat4 lowerLegL;
	scale = glm::scale(lowerLegL, glm::vec3(1.2f, 1.0f, 1.2f));
	translate = glm::translate(lowerLegL, glm::vec3(0.0f, -2.0f, 0.0f));
	lowerLegL *= transformations.top() * scale * translate; //use UpperLegL
	colValues[0] = 0.392f;
	colValues[1] = 0.584f;
	colValues[2] = 0.929f;
	glProgramUniform4fv(shaderProgram, colorLoc, 1, colValues);
	glUniformMatrix4fv(transformLoc, 1, GL_FALSE, glm::value_ptr(lowerLegL));
	glDrawArrays(mode, 0, 12 * 3);

	//UPPER LEG R
	transformations.pop(); //pop UpperLegL
	glm::mat4 upperLegR;
	scale = glm::scale(upperLegR, glm::vec3(0.15f, 0.9f, 0.15f));
	translate = glm::translate(upperLegR, glm::vec3(5.4f, -1.5f, -3.0f));
	upperLegR *= transformations.top() * scale * translate; //use torso
	transformations.push(upperLegR); // push upperLegL to transformations
	colValues[0] = 0.690f;
	colValues[1] = 0.769f;
	colValues[2] = 0.871f;
	glProgramUniform4fv(shaderProgram, colorLoc, 1, colValues);
	glUniformMatrix4fv(transformLoc, 1, GL_FALSE, glm::value_ptr(upperLegR));
	glDrawArrays(mode, 0, 12 * 3);

	//LOWER LEG R
	glm::mat4 lowerLegR;
	scale = glm::scale(lowerLegR, glm::vec3(1.2f, 1.0f, 1.2f));
	translate = glm::translate(lowerLegR, glm::vec3(0.0f, -2.0f, 0.0f));
	lowerLegR *= transformations.top() * scale * translate; //use UpperLegR
	colValues[0] = 0.392f;
	colValues[1] = 0.584f;
	colValues[2] = 0.929f;
	glProgramUniform4fv(shaderProgram, colorLoc, 1, colValues);
	glUniformMatrix4fv(transformLoc, 1, GL_FALSE, glm::value_ptr(lowerLegR));
	glDrawArrays(mode, 0, 12 * 3);

	//TAIL
	transformations.pop(); //pop UpperLegR
	glm::mat4 tail;
	scale = glm::scale(tail, glm::vec3(0.5f, 0.3f, 0.3f));
	rotate = glm::rotate(tail, glm::radians(10.0f), glm::vec3(0.0f, 0.0f, 1.0f));
	translate = glm::translate(tail, glm::vec3(3.0f, 1.5f, 0.0f));
	tail *= transformations.top() * scale * rotate * translate;
	colValues[0] = 0.118f;
	colValues[1] = 0.565f;
	colValues[2] = 1.000f;
	glProgramUniform4fv(shaderProgram, colorLoc, 1, colValues);
	glUniformMatrix4fv(transformLoc, 1, GL_FALSE, glm::value_ptr(tail));
	glDrawArrays(mode, 0, 12 * 3);
	
	glBindVertexArray(0);
}

int init() {
	std::cout << "Starting GLFW context, OpenGL 3.3" << std::endl;
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_RESIZABLE, GL_TRUE);

	// Create a GLFWwindow object that we can use for GLFW's functions
	window = glfwCreateWindow(windowWidth, windowHeight, "Horse", nullptr, nullptr);
	if (window == nullptr)
	{
		std::cout << "Failed to create GLFW window" << std::endl;
		glfwTerminate();
		return -1;
	}

	glfwSetKeyCallback(window, key_callback);
	glfwSetCursorPosCallback(window, mouse_callback);
	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
	//glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
	glfwMakeContextCurrent(window);

	glewExperimental = GL_TRUE;
	glEnable(GL_CULL_FACE);

	if (glewInit() != 0) {
		std::cout << "Failed to initialize GLEW" << std::endl;
		return -1;
	}
	return 0;
}

// The MAIN function, from here we start the application and run the game loop
int main()
{
	if (init() != 0) {
		std::cout << "Failed to initialize program" << std::endl;
		return -1;
	}

	ShaderLoader s;
	GLuint shaderProgram = s.loadShaders("vertex.shader", "fragment.shader");
	glUseProgram(shaderProgram);

	//Horse vertices
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

	GLuint VAO[3];
	glGenVertexArrays(1, &VAO[0]);
	glBindVertexArray(VAO[0]);
	GLuint horseVBO;
	glGenBuffers(1, &horseVBO);
	glBindBuffer(GL_ARRAY_BUFFER, horseVBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(horseVertices), horseVertices, GL_STATIC_DRAW);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), (GLvoid*)0);
	glEnableVertexAttribArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);

	//Horse Normals
	/*std::vector<glm::vec3> normals;
	for (int i = 0; i < sizeof(horseVertices); ++i) {
		glm::vec3 a, b;
		a.x = horseVertices[i];
		a.y = horseVertices[i + 1];
		a.y = horseVertices[i + 2];
		b.x = horseVertices[i + 3];
		b.y = horseVertices[i + 4];
		b.y = horseVertices[i + 5];
		glm::vec3 cross = glm::cross(a, b);
		cross = glm::normalize(cross);
		normals.push_back(cross);
	}

	glGenVertexArrays(1, &VAO[0]);
	glBindVertexArray(VAO[0]);
	GLuint normalVBO;
	glGenBuffers(1, &normalVBO);
	glBindBuffer(GL_ARRAY_BUFFER, normalVBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(glm::vec3)*normals.size(), &normals[0], GL_STATIC_DRAW);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, 0);
	glEnableVertexAttribArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);*/

	//Axes vertices
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
	GLuint axisVBO;
	glGenBuffers(1, &axisVBO);
	glBindBuffer(GL_ARRAY_BUFFER, axisVBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(axis), axis, GL_STATIC_DRAW);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), (GLvoid*)0);
	glEnableVertexAttribArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);

	//Grid vertices
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
	GLuint groundVBO;
	glGenBuffers(1, &groundVBO);
	glBindBuffer(GL_ARRAY_BUFFER, groundVBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(glm::vec3)*ground.size(), &ground[0], GL_STATIC_DRAW);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
	glEnableVertexAttribArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);

	//View Matrix
	viewMatrix = glm::lookAt(c_pos, c_pos + c_eye, c_up);
	GLuint viewMatrixLoc = glGetUniformLocation(shaderProgram, "view_matrix");

	//Projection Matrix
	projectionMatrix = glm::perspective(zoom, (float)windowWidth / windowHeight, 0.0f, 100.0f);
	GLuint projectionLoc = glGetUniformLocation(shaderProgram, "projection_matrix");

	//Initialize Renderer
	GLuint transformLoc = glGetUniformLocation(shaderProgram, "model_matrix");
	GLuint colorLoc = glGetUniformLocation(shaderProgram, "color");
	Renderer r = Renderer(transformLoc, colorLoc, shaderProgram);

	//GROUND
	float colValues[4] = { 1.0, 1.0, 1.0, 1.0 };

	//AXIS
	std::vector<glm::vec3> colors;

	glm::vec3 red = glm::vec3(1.0f, 0.0f, 0.0f);
	glm::vec3 green = glm::vec3(0.0f, 1.0f, 0.0f);
	glm::vec3 blue = glm::vec3(0.0f, 0.0f, 1.0f);
	colors.push_back(red);
	colors.push_back(green);
	colors.push_back(blue);

	glClearColor(0.7f, 0.7f, 0.7f, 0.0f);

	// Game loop
	while (!glfwWindowShouldClose(window))
	{
		float currentFrame = glfwGetTime();
		deltaTime = currentFrame - lastFrame;
		lastFrame = currentFrame;

		glfwPollEvents();
		glClear(GL_COLOR_BUFFER_BIT);

		//Update View
		glUniformMatrix4fv(viewMatrixLoc, 1, GL_FALSE, glm::value_ptr(viewMatrix));
		glUniformMatrix4fv(projectionLoc, 1, GL_FALSE, glm::value_ptr(projectionMatrix));

		//GROUND
		r.setVAO(VAO[2]);
		glm::mat4 ground;
		r.drawGround(colValues, ground);
		r.setVAO(0);

		//AXIS
		r.setVAO(VAO[1]);
		glm::mat4 axis;
		r.drawAxis(colors[0], axis, 0);
		r.drawAxis(colors[1], axis, 2);
		r.drawAxis(colors[2], axis, 4);
		r.setVAO(0);

		//HORSE
		drawHorse(shaderProgram, renderMode, VAO[0]);
		

		glfwSwapBuffers(window);

	}

	// Terminate GLFW, clearing any resources allocated by GLFW.
	glfwTerminate();
	return 0;

	
}
