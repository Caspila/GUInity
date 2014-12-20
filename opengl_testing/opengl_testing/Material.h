#pragma once

#include <GL\glew.h>
#include <GLFW\glfw3.h>
#include "Module.h"
#include "Shader.h"
#include <memory>
#include <map>
#include "Holder.h"
#include "AnyClass.h"

class Material
#ifdef GUINITY_DEBUG
	: public StaticCounter<Material>
#endif
{	
public:
	shared_ptr<Shader> shader;

	GLuint getShaderProgram();

	map<string, Holder> params;
//	vector<tuple<string, glm::vec3>> params;

	bool paramExists(string paramName);
	void setParamVec3(string paramName, glm::vec3 paramValue);
	void setParamFloat(string paramName, float paramValue);

	Material(shared_ptr<Shader> s);
	~Material();

};

