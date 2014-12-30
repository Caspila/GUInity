#pragma once

#include "Module.hpp"
#include <fstream>
#include <vector>
#include <map>
#include <glm/glm.hpp>
#include "Holder.hpp"
#include "Asset.hpp"

class Shader : public Asset
#ifdef GUINITY_DEBUG
	,public StaticCounter<Shader>
#endif
{
public:
    Shader();
	Shader(string vertex_file_path, string fragment_file_path);
	~Shader();

    string vsFilename;
    string fsFilename;
    
	//vector<string> floatParam;
	//vector<string> vec3Params;

	map<string, ShaderParamType> params;
	map<string, GLuint> paramID;

	void LoadShaders();
	void checkLine(const string& Line);
	void createUniformLocation();
	GLuint programID;
};

