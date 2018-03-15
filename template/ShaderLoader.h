#pragma once
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
class ShaderLoader
{
public:
	ShaderLoader();
	~ShaderLoader();
	GLuint loadShaders(std::string vertex_shader_path, std::string fragment_shader_path);

};

