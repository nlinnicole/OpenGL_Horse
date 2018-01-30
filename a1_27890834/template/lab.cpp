//Lab 1
//modified from http://learnopengl.com/

#include "stdafx.h"

#include "..\glew\glew.h"	// include GL Extension Wrangler
#include "..\glfw\glfw3.h"	// include GLFW helper library
#include <stdio.h>
#include <iostream>
#include <string>
#include <fstream>

#include "glm.hpp"
#include "gtc/matrix_transform.hpp"
#include "gtc/type_ptr.hpp"

using namespace std;

// Window dimensions
const GLuint WIDTH = 800;
const GLuint HEIGHT = 800;
GLFWwindow* window;

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

// Is called whenever a key is pressed/released via GLFW
void key_callback(GLFWwindow* window, int key, int scancode, int action, int mode)
{
	std::cout << key << std::endl;
	if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
		glfwSetWindowShouldClose(window, GL_TRUE);
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

	GLfloat vertices[] = {
		1.0f,-1.0f, 1.0f, //Cube begin
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
		//100.0f, 0.0f, 100.0f, //Ground begin
		//-100.0f, 0.0f, 100.0f,
		//-100.0f, 0.0f, -100.0f,
		//100.0f, 0.0f, -100.0f //Ground end
	};
	GLuint VAO;
	glGenVertexArrays(1, &VAO);
	glBindVertexArray(VAO);

	GLuint VBO;
	glGenBuffers(1, &VBO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), (GLvoid*)0);
	glEnableVertexAttribArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, 0); 
	glBindVertexArray(0);

	//Model Matrix
	glm::mat4 scale;
	glm::mat4 translate;
	glm::mat4 rotate;
	GLuint transformLoc = glGetUniformLocation(shaderProgram, "model_matrix");

	//View Matrix
	glm::mat4 viewMatrix = glm::lookAt(glm::vec3(0.0f, 0.0f, 15.0f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f));
	
	GLuint viewMatrixLoc = glGetUniformLocation(shaderProgram, "view_matrix");

	//Projection Matrix
	glm::mat4 projectionMatrix = glm::perspective(45.0f, (GLfloat)width / (GLfloat)height, 0.0f, 100.0f);
	GLuint projectionLoc = glGetUniformLocation(shaderProgram, "projection_matrix");

	glUniformMatrix4fv(viewMatrixLoc, 1, GL_FALSE, glm::value_ptr(viewMatrix));
	glUniformMatrix4fv(projectionLoc, 1, GL_FALSE, glm::value_ptr(projectionMatrix));
	glClearColor(0.7f, 0.7f, 0.7f, 0.0f);

	// Game loop
	while (!glfwWindowShouldClose(window))
	{
		glfwPollEvents();

		// Render
		// Clear the colorbuffer
		glClear(GL_COLOR_BUFFER_BIT);

		//GROUND
		/*glBindVertexArray(VAO);
		glDrawArrays(GL_TRIANGLES, 0, 4);
		glBindVertexArray(0);
		glm::mat4 ground;
		glUniformMatrix4fv(transformLoc, 1, GL_FALSE, glm::value_ptr(ground));*/


		//HEAD
		glBindVertexArray(VAO);
		glDrawArrays(GL_TRIANGLES, 0, 12*3);
		glBindVertexArray(0);

		glm::mat4 head;
		rotate = glm::rotate(head, 45.0f, glm::vec3(0.0f, 0.0f, 1.0f));
		scale = glm::scale(head, glm::vec3(1.0f, 0.5f, 1.0f));
		translate = glm::translate(head, glm::vec3(-5.0f, 5.0f, 0.0f));
		head = head * rotate * translate * scale;
		glUniformMatrix4fv(transformLoc, 1, GL_FALSE, glm::value_ptr(head));

		//NECK
		glBindVertexArray(VAO);
		glDrawArrays(GL_TRIANGLES, 0, 12 * 3);
		glBindVertexArray(0);

		glm::mat4 neck;
		rotate = glm::rotate(neck, 20.0f, glm::vec3(0.0f, 0.0f, 1.0f));
		scale = glm::scale(neck, glm::vec3(0.6f, 1.0f, 1.0f));
		translate = glm::translate(neck, glm::vec3(0.0f, 2.5f, 0.0f));
		neck = neck * rotate * scale * translate;
		glUniformMatrix4fv(transformLoc, 1, GL_FALSE, glm::value_ptr(neck));

		//TORSO
		glBindVertexArray(VAO);
		glDrawArrays(GL_TRIANGLES, 0, 12 * 3);
		glBindVertexArray(0);

		glm::mat4 torso;
		scale = glm::scale(torso, glm::vec3(2.0f, 1.0f, 1.0f));
		torso *= scale;
		glUniformMatrix4fv(transformLoc, 1, GL_FALSE, glm::value_ptr(torso));

		//UPPER ARM L
		glBindVertexArray(VAO);
		glDrawArrays(GL_TRIANGLES, 0, 12 * 3);
		glBindVertexArray(0);

		glm::mat4 upperArmL;
		scale = glm::scale(upperArmL, glm::vec3(0.3f, 0.7f, 0.3f));
		translate = glm::translate(upperArmL, glm::vec3(-6.0f, -2.5f, 0.0f));
		upperArmL *= scale * translate;
		glUniformMatrix4fv(transformLoc, 1, GL_FALSE, glm::value_ptr(upperArmL));

		//LOWER ARM L
		glBindVertexArray(VAO);
		glDrawArrays(GL_TRIANGLES, 0, 12 * 3);
		glBindVertexArray(0);

		glm::mat4 lowerArmL;
		scale = glm::scale(lowerArmL, glm::vec3(0.3f, 0.7f, 0.3f));
		translate = glm::translate(lowerArmL, glm::vec3(-6.0f, -4.5f, 0.0f));
		lowerArmL *= scale * translate;
		glUniformMatrix4fv(transformLoc, 1, GL_FALSE, glm::value_ptr(lowerArmL));

		//UPPER LEG L
		glBindVertexArray(VAO);
		glDrawArrays(GL_TRIANGLES, 0, 12 * 3);
		glBindVertexArray(0);

		glm::mat4 upperLegL;
		scale = glm::scale(upperLegL, glm::vec3(0.3f, 0.7f, 0.3f));
		translate = glm::translate(upperLegL, glm::vec3(6.0f, -2.5f, 0.0f));
		upperLegL *= scale * translate;
		glUniformMatrix4fv(transformLoc, 1, GL_FALSE, glm::value_ptr(upperLegL));

		//LOWER LEG L
		glBindVertexArray(VAO);
		glDrawArrays(GL_TRIANGLES, 0, 12 * 3);
		glBindVertexArray(0);

		glm::mat4 lowerLegL;
		scale = glm::scale(lowerLegL, glm::vec3(0.3f, 0.7f, 0.3f));
		translate = glm::translate(lowerLegL, glm::vec3(6.0f, -4.5f, 0.0f));
		lowerLegL *= scale * translate;
		glUniformMatrix4fv(transformLoc, 1, GL_FALSE, glm::value_ptr(lowerLegL));		

		//TAIL
		glBindVertexArray(VAO);
		glDrawArrays(GL_TRIANGLES, 0, 12 * 3);
		glBindVertexArray(0);

		glm::mat4 tail;
		scale = glm::scale(tail, glm::vec3(2.0f, 0.3f, 0.3f));
		translate = glm::translate(tail, glm::vec3(4.0f, 0.5f, 0.0f));
		rotate = glm::rotate(tail, 45.0f, glm::vec3(0.0f, 0.0f, 1.0f));
		tail *= rotate * translate * scale;
		glUniformMatrix4fv(transformLoc, 1, GL_FALSE, glm::value_ptr(tail));
		
		// Swap the screen buffers
		glfwSwapBuffers(window);
	}

	// Terminate GLFW, clearing any resources allocated by GLFW.
	glfwTerminate();
	return 0;
}
