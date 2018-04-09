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
#include "BufferLoader.h"

#include <stdio.h>
#include <iostream>
#include <string>
#include <fstream>
#include <stack>
#include <vector>

using namespace std;

//--------------------------GLOBAL VARIABLES--------------------------
// Window dimensions
GLFWwindow* window;
int windowWidth = 800;
int windowHeight = 800;

// View variables
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

// Initial Horse Values
const glm::vec3 initScale = glm::vec3(2.0f, 1.0f, 1.0f);
const glm::vec3 initRotation = glm::vec3(0.0f, 0.0f, 1.0f);
const glm::vec3 initTranslation = glm::vec3(0.0f, 4.0f, 0.0f);
float initRotateAngle = 0.0f;

Horse h = Horse();
Horse *h1;
std::vector<Horse *> horses;

// Horse values used to transform horse
glm::vec3 newScale = initScale;
glm::vec3 newRotation = initRotation;
glm::vec3 newTranslation = initTranslation;
float newRotateAngle[12];

// Variables to set render style
GLenum renderMode = GL_TRIANGLES;
bool hasTexture = false;
bool hasAnimation = false;
bool hasShadow = false;
bool horseMoving = false;

//Light
glm::vec3 lightPos = glm::vec3(0.0f, 20.0f, 10.0f);

//--------------------------UPDATE VIEW--------------------------
void update() {
	viewMatrix = glm::lookAt(c_pos, c_pos + c_eye, c_up);
	glfwGetWindowSize(window, &windowWidth, &windowHeight);
	projectionMatrix = glm::perspective(zoom, (float)windowWidth / windowHeight, 0.0f, 100.0f);
}

// Is called whenever a key is pressed/released via GLFW
void key_callback(GLFWwindow* window, int key, int scancode, int action, int mode)
{
	//--------------------------CAMERA CONTROLS--------------------------
	//Close window
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
		update();
	}
	//Reset scene
	if (key == GLFW_KEY_HOME && action == GLFW_PRESS) {
		c_pos = glm::vec3(0.0f, 3.0f, 15.0f);
		c_eye = glm::normalize(glm::vec3(0.0f, 0.0f, -15.0f));
		c_up = glm::vec3(0.0f, 1.0f, 0.0f);
		for (int i = 0; i < sizeof(newRotateAngle) / sizeof(newRotateAngle[0]); ++i) {
			newRotateAngle[i] = 0.0f;
		}
		h.resetHorse();
		hasAnimation = false;
		update();
	}
	//--------------------------RENDER MODE--------------------------
	//Change horse render mode to points
	if (key == GLFW_KEY_P && action == GLFW_PRESS) {
		renderMode = GL_POINTS;
	}
	//Change horse render mode to lines
	if (key == GLFW_KEY_L && action == GLFW_PRESS) {
		renderMode = GL_LINES;
	}
	//Change horse render mode to triangles
	if (key == GLFW_KEY_T && action == GLFW_PRESS) {
		renderMode = GL_TRIANGLES;
	}
	//--------------------------RENDER STYLE--------------------------
	//Toggle Texture
	if (key == GLFW_KEY_X && action == GLFW_PRESS) {
		hasTexture = !hasTexture;
	}
	//Toggle Shadow
	if (key == GLFW_KEY_B && action == GLFW_PRESS) {
		hasShadow = !hasShadow;
	}
	//Toggle Animation
	if (key == GLFW_KEY_R && action == GLFW_PRESS) {
		hasAnimation = !hasAnimation;
		if (!hasAnimation) {
			h.resetHorse();
		}
	}
	//--------------------------HORSE CONTROLS--------------------------
	//Scale horse up
	if (key == GLFW_KEY_U && action == GLFW_PRESS) {
		newScale.x += 0.2;
		newScale.y += 0.1;
		newScale.z += 0.1;
		h.scaleHorse(newScale);
		//h.setTorso(newScale, initRotateAngle, initRotation, initTranslation);
	}
	//Scale horse down
	if (key == GLFW_KEY_J && action == GLFW_PRESS) {
		newScale.x -= 0.2;
		newScale.y -= 0.1;
		newScale.z -= 0.1;
		h.scaleHorse(newScale);
	}
	//Move horse up
	if (key == GLFW_KEY_W && action == GLFW_PRESS) {
		if (mode == GLFW_MOD_SHIFT) {
			++newTranslation.y;
			h.translateHorse(newTranslation);
		}
		//Rotate horse upwards on z axis
		else {
			newRotateAngle[10] += 5.0f;
			newRotation = glm::vec3(0.0f, 0.0f, 1.0f);
			h.rotateHorse(newRotateAngle[10], newRotation);
		}
	}
	//Move horse down
	if (key == GLFW_KEY_S && action == GLFW_PRESS) {
		if (mode == GLFW_MOD_SHIFT) {
			--newTranslation.y;
			h.translateHorse(newTranslation);
		}
		//Rotate horse downwards on z axis
		else {
			newRotateAngle[10] -= 5.0f;
			newRotation = glm::vec3(0.0f, 0.0f, 1.0f);
			h.rotateHorse(newRotateAngle[10], newRotation);
		}
	}
	//Move horse left
	if (key == GLFW_KEY_A && action == GLFW_PRESS) {
		if (mode == GLFW_MOD_SHIFT) {
			--newTranslation.x;
			h.translateHorse(newTranslation);
		}
		//Rotate horse left on y axis
		else {
			newRotateAngle[11] -= 5.0f;
			newRotation = glm::vec3(0.0f, 1.0f, 0.0f);
			h.rotateHorse(newRotateAngle[11], newRotation);
		}
	}
	//Move horse right
	if (key == GLFW_KEY_D && action == GLFW_PRESS) {
		if (mode == GLFW_MOD_SHIFT) {
			++newTranslation.x;
			h.translateHorse(newTranslation);
		}
		//Rotate horse right on y axis
		else {
			newRotateAngle[11] += 5.0f;
			newRotation = glm::vec3(0.0f, 1.0f, 0.0f);
			h.rotateHorse(newRotateAngle[11], newRotation);
		}
	}
	//Move horse
	if (key == GLFW_KEY_H && action == GLFW_PRESS) {
		horseMoving = true;
		//h.moveHorse();
	}
	//Re-position horse to a random position on grid
	if (key == GLFW_KEY_SPACE && action == GLFW_PRESS) {
		float randX = rand() % 50;
		float randZ = rand() % 50;
		newTranslation = glm::vec3(randX, 0.0f, randZ);
		h.translateHorse(newTranslation);
	}
	//Rotate Head
	if (key == GLFW_KEY_0 && action == GLFW_PRESS) {
		if (mode == GLFW_MOD_SHIFT) {
			newRotateAngle[0] -= 5.0f;
		} else {
			newRotateAngle[0] += 5.0f;
		}
		h.setHead(newRotateAngle[0]);
	}
	//Rotate Neck
	if (key == GLFW_KEY_1 && action == GLFW_PRESS) {
		if (mode == GLFW_MOD_SHIFT) {
			newRotateAngle[1] -= 5.0f;
		} else {
			newRotateAngle[1] += 5.0f;
		}
		h.setNeck(newRotateAngle[1]);
	}
	//Rotate Right Arm
	if (key == GLFW_KEY_2 && action == GLFW_PRESS) {
		if (mode == GLFW_MOD_SHIFT) {
			newRotateAngle[2] -= 5.0f;
		} else {
			newRotateAngle[2] += 5.0f;
		}
		h.setUpperArmR(newRotateAngle[2]);
	}
	if (key == GLFW_KEY_3 && action == GLFW_PRESS) {
		if (mode == GLFW_MOD_SHIFT) {
			newRotateAngle[3] -= 5.0f;
		}
		else {
			newRotateAngle[3] += 5.0f;
		}
		h.setLowerArmR(newRotateAngle[3]);
	}
	//Rotate Right Leg
	if (key == GLFW_KEY_4 && action == GLFW_PRESS) {
		if (mode == GLFW_MOD_SHIFT) {
			newRotateAngle[4] -= 5.0f;
		}
		else {
			newRotateAngle[4] += 5.0f;
		}
		h.setUpperLegR(newRotateAngle[4]);
	}
	if (key == GLFW_KEY_5 && action == GLFW_PRESS) {
		if (mode == GLFW_MOD_SHIFT) {
			newRotateAngle[5] -= 5.0f;
		}
		else {
			newRotateAngle[5] += 5.0f;
		}
		h.setLowerLegR(newRotateAngle[5]);
	}
	//Rotate Left Arm
	if (key == GLFW_KEY_6 && action == GLFW_PRESS) {
		if (mode == GLFW_MOD_SHIFT) {
			newRotateAngle[6] -= 5.0f;
		}
		else {
			newRotateAngle[6] += 5.0f;
		}
		h.setUpperArmL(newRotateAngle[6]);
	}
	if (key == GLFW_KEY_7 && action == GLFW_PRESS) {
		if (mode == GLFW_MOD_SHIFT) {
			newRotateAngle[7] -= 5.0f;
		}
		else {
			newRotateAngle[7] += 5.0f;
		}
		h.setLowerArmL(newRotateAngle[7]);
	}
	//Rotate Left Leg
	if (key == GLFW_KEY_8 && action == GLFW_PRESS) {
		if (mode == GLFW_MOD_SHIFT) {
			newRotateAngle[8] -= 5.0f;
		}
		else {
			newRotateAngle[8] += 5.0f;
		}
		h.setUpperLegL(newRotateAngle[8]);
	}
	if (key == GLFW_KEY_9 && action == GLFW_PRESS) {
		if (mode == GLFW_MOD_SHIFT) {
			newRotateAngle[9] -= 5.0f;
		}
		else {
			newRotateAngle[9] += 5.0f;
		}
		h.setLowerLegL(newRotateAngle[9]);
	}
}

void mouse_callback(GLFWwindow* window, double xpos, double ypos) {
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

//--------------------------DRAW GROUND AND HORSE--------------------------
void renderScene(Renderer r, BufferLoader b, GLuint groundTEX, GLuint horseTEX) {
	float colValues[4] = { 1.0, 1.0, 1.0, 1.0 };

	//GROUND
	r.setVAO(b.getGroundVAO());
	glm::mat4 ground;
	r.drawGround(renderMode, colValues, ground, groundTEX);
	r.setVAO(0);

	//HORSE
	r.setVAO(b.getCubeVAO());
	//for (std::vector<Horse *>::iterator it = horses.begin(); it != horses.end(); ++it) {
	//	r.drawHorse(renderMode, horseTEX, it);
	//}
	for (auto horse : horses) {
		r.drawHorse(renderMode, horseTEX, *horse);
	}
	r.setVAO(0);
}

void setHorses() {
	for (int i = 0; i < 20; ++i) {
		glm::vec3 t;
		float randX = rand() % 200 -100 ;
		float randZ = rand() % 200 -100;
		t = glm::vec3(randX, 0.0f, randZ);
		Horse *temp = new Horse();
		temp->translateHorse(t);
		horses.push_back(temp);
	}
	//h1 = new Horse();
	//Horse *h2 = new Horse();
	//horses.push_back(h2);
	//horses.push_back(h1);
	std::cout << horses.size() << std::endl;
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

	glClearColor(0.529f, 0.808f, 0.922f, 0.0f);

	//--------------------------LOAD AND CONFIGURE SHADERS--------------------------
	ShaderLoader s;
	GLuint shaderProgram = s.loadShaders("vertex.shader", "fragment.shader");
	GLuint depthShaderProgram = s.loadShaders("depthVertex.shader", "depthFragment.shader");
	//GLuint skyShaderProgram = s.loadShaders("skyVertex.shader", "skyFragment.shader");
	glUseProgram(shaderProgram);

	//View Matrix
	viewMatrix = glm::lookAt(c_pos, c_pos + c_eye, c_up);
	GLuint viewMatrixLoc = glGetUniformLocation(shaderProgram, "view_matrix");

	//Projection Matrix
	projectionMatrix = glm::perspective(zoom, (float)windowWidth / windowHeight, 0.0f, 100.0f);
	GLuint projectionLoc = glGetUniformLocation(shaderProgram, "projection_matrix");

	//Texture
	GLuint texLoc = glGetUniformLocation(shaderProgram, "tex");
	GLuint renderStyleLoc = glGetUniformLocation(shaderProgram, "renderStyle");

	//Model and Colour
	GLuint transformLoc = glGetUniformLocation(shaderProgram, "model_matrix");
	GLuint colorLoc = glGetUniformLocation(shaderProgram, "color");
	Renderer r = Renderer(transformLoc, colorLoc, shaderProgram, texLoc);

	//Light
	GLuint lightPosLoc = glGetUniformLocation(shaderProgram, "lightPos");
	GLuint cameraPosLoc = glGetUniformLocation(shaderProgram, "cameraPos");
	glUniform3fv(lightPosLoc, 1, glm::value_ptr(lightPos));
	glUniform3fv(cameraPosLoc, 1, glm::value_ptr(c_pos));

	//Buffer Loader
	BufferLoader b;

	setHorses();
	r.horses = horses;

	//Textures
	b.loadTex();
	GLuint horseTEX = b.getHorseTex();
	GLuint groundTEX = b.getGroundTex();
	//GLuint skyTEX = b.getSkyTex();

	//Shadows
	b.loadDepthMap();
	float near = 1.0f;
	float far = 7.5f;
	glm::mat4 lightProjection = glm::ortho(-10.0f, 10.0f, -10.0f, 10.0f, near, far);
	glm::vec3 lightInvEye = glm::vec3(0.0f, 5.0f, -2.0f);
	glm::mat4 lightView = glm::lookAt(lightInvEye, glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f));
	glm::mat4 lightModel = glm::mat4(1.0);
	glm::mat4 lightSpaceMat = lightProjection * lightView * lightModel;

	//Configure depthShaderProgram
	glUseProgram(depthShaderProgram);
	GLuint depthMap = b.getDepthMap();
	GLuint shadowLoc = glGetUniformLocation(shaderProgram, "shadowMap");

	glActiveTexture(GL_TEXTURE1);
	glBindTexture(GL_TEXTURE_2D, depthMap);
	glUniform1i(shadowLoc, 1);
	
	GLuint depthLightMatrixLoc = glGetUniformLocation(depthShaderProgram, "light_matrix");
	glUniformMatrix4fv(depthLightMatrixLoc, 1, GL_FALSE, glm::value_ptr(lightSpaceMat));
	GLuint depthModelLoc = glGetUniformLocation(depthShaderProgram, "model");

	//Configure normal shader
	glUseProgram(shaderProgram);
	GLuint lightMatrixLoc = glGetUniformLocation(shaderProgram, "light_matrix");
	glUniformMatrix4fv(lightMatrixLoc, 1, GL_FALSE, glm::value_ptr(lightSpaceMat));
	
	//Skybox
	//b.loadSkybox();
	//glm::mat4 sky;
	//GLuint skyTexLoc = glGetUniformLocation(skyShaderProgram, "tex");
	//GLuint skyProjectionLoc = glGetUniformLocation(skyShaderProgram, "projection_matrix");
	//GLuint skyTransformLoc = glGetUniformLocation(skyShaderProgram, "model_matrix");
	//GLuint skyViewLoc = glGetUniformLocation(skyShaderProgram, "view_matrix");
	//glUniformMatrix4fv(skyViewLoc, 1, GL_FALSE, glm::value_ptr(viewMatrix));
	//glUniformMatrix4fv(skyProjectionLoc, 1, GL_FALSE, glm::value_ptr(projectionMatrix));

	//--------------------------GAME LOOP--------------------------
	while (!glfwWindowShouldClose(window))
	{
		//--------------------------UPDATE VIEW--------------------------
		float currentFrame = glfwGetTime();
		deltaTime = currentFrame - lastFrame;
		lastFrame = currentFrame;
		glClear(GL_COLOR_BUFFER_BIT);
		
		glUniformMatrix4fv(viewMatrixLoc, 1, GL_FALSE, glm::value_ptr(viewMatrix));
		glUniformMatrix4fv(projectionLoc, 1, GL_FALSE, glm::value_ptr(projectionMatrix));

		//--------------------------RENDER STYLE--------------------------
		if (hasTexture && !hasShadow) {
			//Texture, no shadow
			glUniform1i(renderStyleLoc, 1); 
		}
		else if (!hasTexture && hasShadow) {
			//No texture, shadow
			glUniform1i(renderStyleLoc, 2);
		}
		else if (hasTexture && hasShadow) {
			//Has texture and shadow
			glUniform1i(renderStyleLoc, 3);
		}
		else {
			//No texture, no shadow
			glUniform1i(renderStyleLoc, 0); 
		}

		//--------------------------TOGGLE ANIMATION--------------------------
		if (hasAnimation)
			h.animateHorse();

		if (horseMoving)
			h.moveHorse();

		//--------------------------DRAW SCENE--------------------------
		//depth shader
		glUseProgram(depthShaderProgram);
		r.setShaderProgram(depthShaderProgram);
		r.setTransformLoc(depthModelLoc);

		glViewport(0, 0, 1024, 1024);
		glBindFramebuffer(GL_FRAMEBUFFER, b.getFBO());
		glClear(GL_DEPTH_BUFFER_BIT);
		renderScene(r, b, groundTEX, horseTEX);
		glBindFramebuffer(GL_FRAMEBUFFER, 0);

		//normal shader
		glUseProgram(shaderProgram);
		r.setShaderProgram(shaderProgram);
		r.setTransformLoc(transformLoc);

		glViewport(0, 0, windowWidth, windowHeight);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		glBindTexture(GL_TEXTURE_2D, depthMap);
		renderScene(r, b, groundTEX, horseTEX);

		//SKYBOX
		//glDepthMask(GL_FALSE);
		//glUseProgram(skyShaderProgram);
		//r.setVAO(b.getCubeVAO());
		//r.drawSkyBox(sky, skyTEX, skyTransformLoc, skyTexLoc);
		//r.setVAO(0);
		//glDepthMask(GL_TRUE);

		glfwSwapBuffers(window);
		glfwPollEvents();

	}
	// Terminate GLFW, clearing any resources allocated by GLFW.
	glfwTerminate();
	return 0;
}

