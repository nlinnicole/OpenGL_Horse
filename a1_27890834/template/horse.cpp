//Lab 1
//modified from http://learnopengl.com/

#include "stdafx.h"

#include "..\glew\glew.h"	// include GL Extension Wrangler
#include "..\glfw\glfw3.h"	// include GLFW helper library
#include "glm.hpp"
#include "gtc/matrix_transform.hpp"
#include "gtc/type_ptr.hpp"

#include <stdio.h>
#include <iostream>
#include <string>
#include <fstream>
#include <stack>
#include <vector>


using namespace std;

// Window dimensions
const GLuint WIDTH = 800;
const GLuint HEIGHT = 800;
GLFWwindow* window;

//Gobal variables
glm::vec3 c_pos = glm::vec3(0.0f, 3.0f, 15.0f);
glm::vec3 c_eye = glm::normalize(glm::vec3(0.0f, 0.0f, -15.0f));
glm::vec3 c_up = glm::vec3(0.0f, 1.0f, 0.0f);

glm::mat4 viewMatrix;
glm::mat4 projectionMatrix;

float zoom = 45.0f;

glm::vec3 horseScale = glm::vec3(2.0f, 1.0f, 1.0f);
glm::vec3 horseRotation = glm::vec3(0.0f, 0.0f, 1.0f);
glm::vec3 horseTranslation = glm::vec3(0.0f, 4.0f, 0.0f);
float horseRotateAngle = 0.0f;

GLenum renderMode = GL_TRIANGLES;

int xPos;
int yPos;
//glfwGetMousePos(&xPos, &yPos);

GLuint loadShaders(std::string vertex_shader_path, std::string fragment_shader_path) {
	// Read the Vertex Shader code from the file
	string VertexShaderCode;
	std::ifstream VertexShaderStream(vertex_shader_path, ios::in);

	if (VertexShaderStream.is_open()) {
		string Line = "";
		while (getline(VertexShaderStream, Line))
			VertexShaderCode += "\n" + Line;
		VertexShaderStream.close();
	}
	else {
		printf("Impossible to open %s. Are you in the right directory ?\n", vertex_shader_path.c_str());
		getchar();
		return -1;
	}

	// Read the Fragment Shader code from the file
	std::string FragmentShaderCode;
	std::ifstream FragmentShaderStream(fragment_shader_path, std::ios::in);

	if (FragmentShaderStream.is_open()) {
		std::string Line = "";
		while (getline(FragmentShaderStream, Line))
			FragmentShaderCode += "\n" + Line;
		FragmentShaderStream.close();
	}
	else {
		printf("Impossible to open %s. Are you in the right directory?\n", fragment_shader_path.c_str());
		getchar();
		return -1;
	}

	GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
	char const * VertexSourcePointer = VertexShaderCode.c_str();
	glShaderSource(vertexShader, 1, &VertexSourcePointer, NULL);
	glCompileShader(vertexShader);
	// Check for compile time errors
	GLint success;
	GLchar infoLog[512];
	glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
		std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;
		return -1;
	}

	// Fragment shader
	GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	char const * FragmentSourcePointer = FragmentShaderCode.c_str();
	glShaderSource(fragmentShader, 1, &FragmentSourcePointer, NULL);
	glCompileShader(fragmentShader);
	// Check for compile time errors
	glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		glGetShaderInfoLog(fragmentShader, 512, NULL, infoLog);
		std::cout << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n" << infoLog << std::endl;
		return -1;
	}
	// Link shaders
	GLuint shaderProgram = glCreateProgram();
	glAttachShader(shaderProgram, vertexShader);
	glAttachShader(shaderProgram, fragmentShader);
	glLinkProgram(shaderProgram);

	// Check for linking errors
	glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
	if (!success) {
		glGetProgramInfoLog(shaderProgram, 512, NULL, infoLog);
		std::cout << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n" << infoLog << std::endl;
		return -1;
	}
	glDeleteShader(vertexShader); //free up memory
	glDeleteShader(fragmentShader);

	return shaderProgram;
}

// Update view
void update() {
	viewMatrix = glm::lookAt(c_pos, c_pos + c_eye, c_up);
	projectionMatrix = glm::perspective(zoom, (GLfloat)WIDTH / (GLfloat)HEIGHT, 0.0f, 100.0f);
}

// Is called whenever a key is pressed/released via GLFW
void key_callback(GLFWwindow* window, int key, int scancode, int action, int mode)
{
	std::cout << key << std::endl;
	if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
		glfwSetWindowShouldClose(window, GL_TRUE);
	if (key == GLFW_KEY_LEFT) {
		--c_pos.x;
		std::cout << c_pos.x << std::endl;
		update();
	}
	if (key == GLFW_KEY_RIGHT && action == GLFW_PRESS) {
		++c_pos.x;
		std::cout << c_pos.x << std::endl;
		update();
	}
	if (key == GLFW_KEY_UP && action == GLFW_PRESS) {
		++c_pos.y;
		std::cout << c_pos.y << std::endl;
		update();
	}
	if (key == GLFW_KEY_DOWN && action == GLFW_PRESS) {
		--c_pos.y;
		std::cout << c_pos.y << std::endl;
		update();
	}
	if (key == GLFW_KEY_HOME && action == GLFW_PRESS) {
		c_pos = glm::vec3(0.0f, 0.0f, 15.0f);
		update();
	}
	//if (key == GLFW_KEY_U && action == GLFW_PRESS) {
	//	std::cout << zoom << std::endl;
	//	zoom += 2;
	//	std::cout << zoom << std::endl;
	//	update_view();
	//}
	if (key == GLFW_KEY_U && action == GLFW_PRESS) {
		horseScale.x += 0.2;
		horseScale.y += 0.1;
		horseScale.z += 0.1;
	}
	if (key == GLFW_KEY_J && action == GLFW_PRESS) {
		horseScale.x -= 0.2;
		horseScale.y -= 0.1;
		horseScale.z -= 0.1;
	}
	if (key == GLFW_KEY_W && action == GLFW_PRESS) {
		if (mode == GLFW_MOD_SHIFT) {
			++horseTranslation.y;
		}
		else {
			horseRotation = glm::vec3(0.0f, 0.0f, 1.0f);
			horseRotateAngle += glm::radians(-5.0f);
		}
	}
	if (key == GLFW_KEY_A && action == GLFW_PRESS) {
		if (mode == GLFW_MOD_SHIFT) {
			--horseTranslation.x;
		}
		else {
			horseRotation = glm::vec3(0.0f, 1.0f, 0.0f);
			horseRotateAngle += glm::radians(-5.0f);
		}
	}
	if (key == GLFW_KEY_S && action == GLFW_PRESS) {
		if (mode == GLFW_MOD_SHIFT) {
			--horseTranslation.y;
		}
		else {
			horseRotation = glm::vec3(0.0f, 0.0f, 1.0f);
			horseRotateAngle += glm::radians(5.0f);
		}
	}
	if (key == GLFW_KEY_D && action == GLFW_PRESS) {
		if (mode == GLFW_MOD_SHIFT) {
			++horseTranslation.x;
		}
		else {
			horseRotation = glm::vec3(0.0f, 1.0f, 0.0f);
			horseRotateAngle += glm::radians(5.0f);
		}
	}
	if (key == GLFW_KEY_SPACE && action == GLFW_PRESS) {
		float randX = rand() % 100;
		float randZ = rand() % 100;
		horseTranslation = glm::vec3(randX, 0.0f, randZ);
		std::cout << horseTranslation.x << " " << horseTranslation.y << " " << horseTranslation.z << std::endl;
	}
	if (key == GLFW_KEY_P && action == GLFW_PRESS) {
		renderMode = GL_POINTS;
	}
	if (key == GLFW_KEY_L && action == GLFW_PRESS) {
		renderMode = GL_LINES;
	}
	if (key == GLFW_KEY_T && action == GLFW_PRESS) {
		renderMode = GL_TRIANGLES;
	}
}

void drawHorse(GLuint shaderProgram, GLenum mode) {
	//Model Matrix
	float colValues[4] = { 0.0f, 0.0f, 0.0f, 1.0f };
	glm::mat4 scale;
	glm::mat4 translate;
	glm::mat4 rotate;

	std::stack<glm::mat4> transformations;

	////TORSO
	glDrawArrays(mode, 0, 12 * 3);

	glm::mat4 torso;
	scale = glm::scale(torso, horseScale);
	rotate = glm::rotate(torso, horseRotateAngle, horseRotation);
	translate = glm::translate(torso, horseTranslation);
	torso *= scale * rotate * translate;
	transformations.push(torso); //push torso to transformations
	colValues[0] = 0.275f;
	colValues[1] = 0.510f;
	colValues[2] = 0.706f;
	GLuint transformLoc = glGetUniformLocation(shaderProgram, "model_matrix");
	GLuint colorLoc = glGetUniformLocation(shaderProgram, "color");
	glProgramUniform4fv(shaderProgram, colorLoc, 1, colValues);
	glUniformMatrix4fv(transformLoc, 1, GL_FALSE, glm::value_ptr(torso));

	//NECK
	glDrawArrays(mode, 0, 12 * 3);

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

	//HEAD
	glDrawArrays(mode, 0, 12 * 3);

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

	//UPPER ARM L
	glDrawArrays(mode, 0, 12 * 3);

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

	//LOWER ARM L
	glDrawArrays(mode, 0, 12 * 3);

	glm::mat4 lowerArmL;
	scale = glm::scale(lowerArmL, glm::vec3(1.2f, 1.0f, 1.2f));
	translate = glm::translate(lowerArmL, glm::vec3(0.0f, -2.0f, 0.0f));
	lowerArmL *= transformations.top() * scale * translate; //use UpperArmL
	colValues[0] = 0.392f;
	colValues[1] = 0.584f;
	colValues[2] = 0.929f;
	glProgramUniform4fv(shaderProgram, colorLoc, 1, colValues);
	glUniformMatrix4fv(transformLoc, 1, GL_FALSE, glm::value_ptr(lowerArmL));

	//UPPER ARM R
	glDrawArrays(mode, 0, 12 * 3);

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

	//LOWER ARM R
	glDrawArrays(mode, 0, 12 * 3);

	glm::mat4 lowerArmR;
	scale = glm::scale(lowerArmR, glm::vec3(1.2f, 1.0f, 1.2f));
	translate = glm::translate(lowerArmR, glm::vec3(0.0f, -2.0f, 0.0f));
	lowerArmR *= transformations.top() * scale * translate; //use UpperArmR
	colValues[0] = 0.392f;
	colValues[1] = 0.584f;
	colValues[2] = 0.929f;
	glProgramUniform4fv(shaderProgram, colorLoc, 1, colValues);
	glUniformMatrix4fv(transformLoc, 1, GL_FALSE, glm::value_ptr(lowerArmR));

	//UPPER LEG L
	glDrawArrays(mode, 0, 12 * 3);

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

	//LOWER LEG L
	glDrawArrays(mode, 0, 12 * 3);

	glm::mat4 lowerLegL;
	scale = glm::scale(lowerLegL, glm::vec3(1.2f, 1.0f, 1.2f));
	translate = glm::translate(lowerLegL, glm::vec3(0.0f, -2.0f, 0.0f));
	lowerLegL *= transformations.top() * scale * translate; //use UpperLegL
	colValues[0] = 0.392f;
	colValues[1] = 0.584f;
	colValues[2] = 0.929f;
	glProgramUniform4fv(shaderProgram, colorLoc, 1, colValues);
	glUniformMatrix4fv(transformLoc, 1, GL_FALSE, glm::value_ptr(lowerLegL));

	//UPPER LEG R
	glDrawArrays(mode, 0, 12 * 3);

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

	//LOWER LEG R
	glDrawArrays(mode, 0, 12 * 3);

	glm::mat4 lowerLegR;
	scale = glm::scale(lowerLegR, glm::vec3(1.2f, 1.0f, 1.2f));
	translate = glm::translate(lowerLegR, glm::vec3(0.0f, -2.0f, 0.0f));
	lowerLegR *= transformations.top() * scale * translate; //use UpperLegR
	colValues[0] = 0.392f;
	colValues[1] = 0.584f;
	colValues[2] = 0.929f;
	glProgramUniform4fv(shaderProgram, colorLoc, 1, colValues);
	glUniformMatrix4fv(transformLoc, 1, GL_FALSE, glm::value_ptr(lowerLegR));

	//TAIL
	glDrawArrays(mode, 0, 12 * 3);

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
}

void drawAxes(GLuint shaderProgram) {
	float groundAxisColValues[4] = { 1.0, 1.0, 1.0, 1.0 };
	GLuint transformLoc2 = glGetUniformLocation(shaderProgram, "model_matrix");
	GLuint colorLoc2 = glGetUniformLocation(shaderProgram, "color");

	glDrawArrays(GL_LINES, 0, 2);
	glm::mat4 xAxis;
	groundAxisColValues[0] = 0.0f;
	groundAxisColValues[1] = 1.0f;
	groundAxisColValues[2] = 0.0f;
	glProgramUniform4fv(shaderProgram, colorLoc2, 1, groundAxisColValues);
	glUniformMatrix4fv(transformLoc2, 1, GL_FALSE, glm::value_ptr(xAxis));

	glDrawArrays(GL_LINES, 2, 2);
	glm::mat4 yAxis;
	groundAxisColValues[0] = 0.0f;
	groundAxisColValues[1] = 0.0f;
	groundAxisColValues[2] = 1.0f;
	glProgramUniform4fv(shaderProgram, colorLoc2, 1, groundAxisColValues);
	glUniformMatrix4fv(transformLoc2, 1, GL_FALSE, glm::value_ptr(yAxis));

	glDrawArrays(GL_LINES, 4, 2);
	glm::mat4 zAxis;
	groundAxisColValues[0] = 1.0f;
	groundAxisColValues[1] = 0.0f;
	groundAxisColValues[2] = 0.0f;
	glProgramUniform4fv(shaderProgram, colorLoc2, 1, groundAxisColValues);
	glUniformMatrix4fv(transformLoc2, 1, GL_FALSE, glm::value_ptr(zAxis));
	glBindVertexArray(0);
}

int init() {
	std::cout << "Starting GLFW context, OpenGL 3.3" << std::endl;
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);

	// Create a GLFWwindow object that we can use for GLFW's functions
	window = glfwCreateWindow(WIDTH, HEIGHT, "Horse", nullptr, nullptr);
	if (window == nullptr)
	{
		std::cout << "Failed to create GLFW window" << std::endl;
		glfwTerminate();
		return -1;
	}

	glfwSetKeyCallback(window, key_callback);
	glfwMakeContextCurrent(window);
	glewExperimental = GL_TRUE;

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
	// Define the viewport dimensions
	int width, height;
	glfwGetFramebufferSize(window, &width, &height);

	glViewport(0, 0, width, height);

	GLuint shaderProgram = loadShaders("vertex.shader", "fragment.shader");
	glUseProgram(shaderProgram);

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

	GLfloat vertices2[] = {
		100.0f, 0.0f, 100.0f,
		100.0f, 0.0f, -100.0f,
		-100.0f, 0.0f, -100.0f,
		-100.0f, 0.0f, 100.0f
	};

	GLfloat axis[] = {
		0.0f, 0.0f, 0.0f,
		5.0f, 0.0f, 0.0f,
		0.0f, 0.0f, 0.0f,
		0.0f, 5.0f, 0.0f,
		0.0f, 0.0f, 0.0f,
		0.0f, 0.0f, 5.0f
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

	glGenVertexArrays(1, &VAO[1]);
	glBindVertexArray(VAO[1]);
	GLuint groundVBO;
	glGenBuffers(1, &groundVBO);
	glBindBuffer(GL_ARRAY_BUFFER, groundVBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices2), vertices2, GL_STATIC_DRAW);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), (GLvoid*)0);
	glEnableVertexAttribArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, 0); 
	glBindVertexArray(0);

	glGenVertexArrays(1, &VAO[2]);
	glBindVertexArray(VAO[2]);

	GLuint axisVBO;
	glGenBuffers(1, &axisVBO);
	glBindBuffer(GL_ARRAY_BUFFER, axisVBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(axis), axis, GL_STATIC_DRAW);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), (GLvoid*)0);
	glEnableVertexAttribArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);

	//View Matrix
	viewMatrix = glm::lookAt(c_pos, c_pos + c_eye, c_up);
	GLuint viewMatrixLoc = glGetUniformLocation(shaderProgram, "view_matrix");

	//Projection Matrix
	projectionMatrix = glm::perspective(zoom, (GLfloat)width / (GLfloat)height, 0.0f, 100.0f);
	GLuint projectionLoc = glGetUniformLocation(shaderProgram, "projection_matrix");

	glClearColor(0.7f, 0.7f, 0.7f, 0.0f);

	// Game loop
	while (!glfwWindowShouldClose(window))
	{
		glfwPollEvents();
		glfwSwapBuffers(window);
		glClear(GL_COLOR_BUFFER_BIT);

		//Update View
		glUniformMatrix4fv(viewMatrixLoc, 1, GL_FALSE, glm::value_ptr(viewMatrix));
		glUniformMatrix4fv(projectionLoc, 1, GL_FALSE, glm::value_ptr(projectionMatrix));

		//HORSE
		glBindVertexArray(VAO[0]);
		drawHorse(shaderProgram, renderMode);
		glBindVertexArray(0);

		//GROUND
		/*glBindVertexArray(VAO[1]);
		glDrawArrays(GL_TRIANGLES, 0, 4);
		glm::mat4 ground;
		GLuint transformLoc2 = glGetUniformLocation(shaderProgram, "model_matrix");
		GLuint colorLoc2 = glGetUniformLocation(shaderProgram, "color");
		glProgramUniform4fv(shaderProgram, colorLoc2, 1, colValues2);
		glUniformMatrix4fv(transformLoc2, 1, GL_FALSE, glm::value_ptr(ground));
		glBindVertexArray(0);*/

		//AXIS
		glBindVertexArray(VAO[2]);
		drawAxes(shaderProgram);
		glBindVertexArray(0);

	}

	// Terminate GLFW, clearing any resources allocated by GLFW.
	glfwTerminate();
	return 0;

	
}
