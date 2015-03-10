#pragma once

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include "Module.hpp"
#include <map>
#include <vector>
#include "Holder.hpp"
#include "Asset.hpp"

class Shader;
class Texture;

/** Material is an Asset that allows the same shader to be used several times with different parameters.
For example, a Textured Diffuse Shader could be use for both a crate and the floor, the only thing that changes is the Texture.

Currently, the only parameter supported by Shaders and therefore Materials is the Texture type.
*/
class Material : public Asset
#ifdef GUINITY_DEBUG
    ,public StaticCounter<Material>
#endif
{	
private:
	/** The shader*/
	shared_ptr<Shader> shader;
	/** The shader params for this material*/
	map<string, Holder> params;

public:
	/** Default Constructor */
	Material();
	/** Constructor for a Shader */
	Material(shared_ptr<Shader> s);
	/** Default Destructor. Virtual because inherits from Asset */
	virtual ~Material();

	/** shader Setter*/
	void setShader(shared_ptr<Shader> shader);
	/** shader Getter*/
	shared_ptr<Shader> getShader() const;

	/** Get the shader program*/
	GLuint getShaderProgram();

	/** Checks if param exists on params map*/
	bool paramExists(string paramName);
	/** Set a vec3 param that has name paramName*/
	void setParamVec3(string paramName, glm::vec3 paramValue);
	/** Set a float param that has name paramName*/
	void setParamFloat(string paramName, float paramValue);
	/** Set a Texture param that has name paramName*/
	void setParamTexture(string paramName, shared_ptr<Texture> paramValue);
    
    typedef pair<string, shared_ptr<Texture>> StringTexPair;
	typedef pair<string, glm::vec3> StringVec3Pair;
	/** Gets all Texture params*/
	vector<StringTexPair> getAllTextureParams();
	/** Gets all Vec3 params*/
	vector<StringVec3Pair> getAllVec3Params();


};

