#pragma once

#include "Module.hpp"
#include <fstream>
#include <vector>
#include <map>
#include <glm/glm.hpp>
#include "Holder.hpp"

class Shader
#ifdef GUINITY_DEBUG
	:public StaticCounter<Shader>
#endif
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

