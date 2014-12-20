#pragma once

#include "Module.h"
#include <fstream>
#include <vector>
#include <map>
#include <glm\glm.hpp>
#include "Holder.h"

class Shader
{
public:
	Shader(const char * vertex_file_path, const char * fragment_file_path);
	~Shader();

	//vector<string> floatParam;
	//vector<string> vec3Params;

	map<string, ShaderParamType> params;
	map<string, GLuint> paramID;

	void LoadShaders(const char * vertex_file_path, const char * fragment_file_path);
	void checkLine(const string& Line);
	void createUniformLocation();
	GLuint programID;
};

