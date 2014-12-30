#pragma once

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include "Module.hpp"
//#include "Shader.h"
#include <memory>
#include <map>
#include "Holder.hpp"
#include "Asset.hpp"
//#include "AnyClass.h"

class Shader;

class Material : public Asset
#ifdef GUINITY_DEBUG
    ,public StaticCounter<Material>
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

