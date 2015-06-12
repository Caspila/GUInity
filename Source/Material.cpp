
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
        switch (it->second) {
            case TEXTURE:
                params.insert(std::pair<string, Holder>(it->first, Holder(TEXTURE, GraphicsSystem::getInstance()->getDefaultTexture())));
                break;
            case VEC4:
                params.insert(std::pair<string, Holder>(it->first, Holder(VEC4, glm::vec4(1,1,1,1))));
            case VEC2:
                params.insert(std::pair<string, Holder>(it->first, Holder(VEC2, glm::vec2(0,0))));
            default:
                cout << "Error: Unknown variable type for material param" << endl;
                break;
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

/** Set a vec2 param that has name paramName*/
void Material::setParamVec2(string paramName,const glm::vec2& paramValue)
{
    
	auto found = params.find(paramName);
	if (found != params.end())
		params[paramName] = Holder(VEC2,paramValue);
    
	else
		cerr << "Material error: " << paramName << " does not exist" << endl;
}

/** Set a vec2 param that has name paramName*/
glm::vec2 Material::getParamVec2(string paramName)
{
	auto found = params.find(paramName);
	if (found != params.end())
    {
        if(!found->second.isVec2())
            cerr << "Material error: " << paramName << " is not a vec2" << endl;
        return found->second.getVec2();
    }
    
	cerr << "Material error: " << paramName << " does not exist" << endl;
    return glm::vec2(0,0);
}

/** Set a vec4 param that has name paramName*/
void Material::setParamVec4(string paramName,const glm::vec4& paramValue)
{
    
	auto found = params.find(paramName);
	if (found != params.end())
		params[paramName] = Holder(VEC4,paramValue);
    
	else
		cerr << "Material error: " << paramName << " does not exist" << endl;
}

/** Set a float param that has name paramName*/
void Material::setParamFloat(string paramName, float paramValue)
{
    
	auto found = params.find(paramName);
	if (found != params.end())
		params[paramName] = Holder(VEC4, paramValue);
    
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

/** Gets all Vec4 params*/
vector<Material::StringVec4Pair> Material::getAllVec4Params()
{
	vector<Material::StringVec4Pair>result;
    
	auto it = params.begin();
    
	while (it != params.end())
	{
		if (it->second.isVec4())
		{
			result.push_back(Material::StringVec4Pair(it->first, it->second.getVec4()));
		}
		it++;
	}
    
	return result;
    
}

/** Gets all Vec2 params*/
vector<Material::StringVec2Pair> Material::getAllVec2Params()
{
	vector<Material::StringVec2Pair>result;
    
	auto it = params.begin();
    
	while (it != params.end())
	{
		if (it->second.isVec2())
		{
			result.push_back(Material::StringVec2Pair(it->first, it->second.getVec2()));
		}
		it++;
	}
    
	return result;
    
}