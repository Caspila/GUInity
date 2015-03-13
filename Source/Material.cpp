
#include "Material.hpp"
#include "Shader.hpp"
#include "GraphicsSystem.hpp"

/** Default Constructor */
Material::Material()
{
	
#ifdef GUINITY_DEBUG
	nCount++;
#endif
}

/** Constructor for a Shader */
Material::Material(shared_ptr<Shader> shader)
{
	this->shader = shader;

	std::map<string, ShaderParamType>::iterator it = shader->params.begin();

	for (; it != shader->params.end(); it++)
	{
		if (it->second == TEXTURE)
		{
			params.insert(std::pair<string, Holder>(it->first, Holder(TEXTURE, GraphicsSystem::getInstance()->getDefaultTexture())));
		}
		else if (it->second == VEC3)
		{
			params.insert(std::pair<string, Holder>(it->first, Holder(VEC3, glm::vec3(1,1,1))));

		}

	}

#ifdef GUINITY_DEBUG
	nCount++;
#endif
}

/** Default Destructor. Virtual because inherits from Asset */
Material::~Material()
{
#ifdef GUINITY_DEBUG
	nCount--;
	cout << "Material destroyed (" << nCount << " remaining)" << endl;
#endif
	
}

/** shader Setter*/
void Material::setShader(shared_ptr<Shader> shader)
{
    this->shader = shader;
}
/** shader Getter*/
shared_ptr<Shader> Material::getShader() const
{
	return shader;
}
/** Get the shader program*/
GLuint Material::getShaderProgram()
{
	return shader.get()->programID;
}

/** Checks if param exists on params map*/
bool Material::paramExists(string paramName)
{
	std::map<string, ShaderParamType>::iterator it = shader->params.begin();

	for (; it != shader->params.end(); it++)
	{
		if (it->first.compare(paramName))
			return true;
	}

	return false;
}

/** Set a vec3 param that has name paramName*/
void Material::setParamVec3(string paramName, glm::vec3 paramValue)
{

	auto found = params.find(paramName);
	if (found != params.end())
		params[paramName] = Holder(VEC3,paramValue);

	else
		cerr << "Material error: " << paramName << " does not exist" << endl;
}

/** Set a float param that has name paramName*/
void Material::setParamFloat(string paramName, float paramValue)
{

	auto found = params.find(paramName);
	if (found != params.end())
		params[paramName] = Holder(VEC3, paramValue);

	else
		cerr << "Material error: " << paramName << " does not exist" << endl;
}

/** Set a Texture param that has name paramName*/
void Material::setParamTexture(string paramName, shared_ptr<Texture> paramValue)
{

	auto found = params.find(paramName);
	if (found != params.end())
		params[paramName] = Holder(TEXTURE, paramValue);

	else
		cerr << "Material error: " << paramName << " does not exist" << endl;
}


/** Gets all Texture params*/
vector<Material::StringTexPair> Material::getAllTextureParams()
{
    vector<Material::StringTexPair>result;
    
    auto it = params.begin();
    
    while(it!= params.end())
    {
        if (it->second.isTexture())
        {
            result.push_back(Material::StringTexPair(it->first,it->second.getTexture()));
        }
        it++;
    }
    
    return result;

}

/** Gets all Vec3 params*/
vector<Material::StringVec3Pair> Material::getAllVec3Params()
{
	vector<Material::StringVec3Pair>result;

	auto it = params.begin();

	while (it != params.end())
	{
		if (it->second.isVec3())
		{
			result.push_back(Material::StringVec3Pair(it->first, it->second.getVec3()));
		}
		it++;
	}

	return result;

}