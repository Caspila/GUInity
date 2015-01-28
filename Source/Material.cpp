
#include "Material.hpp"
#include "Shader.hpp"

Material::Material(shared_ptr<Shader> shader)
{
	this->shader = shader;


	/*for (int i = 0; i < shader->params.size(); i++)
	{
		pair<string, ShaderParamType> &param = shader->params.at(i);
	}
*/

	std::map<string, ShaderParamType>::iterator it = shader->params.begin();

	for (; it != shader->params.end(); it++)
	{
		if (it->second == TEXTURE)
		{
			params.insert(std::pair<string, Holder>(it->first, Holder(TEXTURE, nullptr)));
		}
		/*else if (it->second == VEC3)
		{
			params.insert(std::pair<string, Holder>(it->first, Holder(VEC3, glm::vec3())));

		}*/

	}

	/*for each(pair<string,ShaderParamType> param in shader->params)
	{

		if (param.second == FLOAT)
		{
			params.insert(std::pair<string, Holder>(param.first, Holder(FLOAT,1)));
		}
		else if (param.second == VEC3)
		{
			params.insert(std::pair<string, Holder>(param.first, Holder(VEC3, glm::vec3())));
		
		}


	}*/

#ifdef GUINITY_DEBUG
	nCount++;
#endif
}


Material::~Material()
{
#ifdef GUINITY_DEBUG
	nCount--;
	cout << "Material destroyed (" << nCount << " remaining)" << endl;
#endif
	
}


void Material::setShader(shared_ptr<Shader> shader)
{
    this->shader = shader;
}

GLuint Material::getShaderProgram()
{
	return shader.get()->programID;
}

bool Material::paramExists(string paramName)
{
//	for each (tuple<string,glm::vec3> var in params)
//	{
//		if (get<0>(var).compare(paramName) == 0)
//			return true;
//	}

	//auto it = std::find(params.begin(), params.end(), paramName);
	//
	//return it != params.end();

	std::map<string, ShaderParamType>::iterator it = shader->params.begin();

	for (; it != shader->params.end(); it++)
	{
		if (it->first.compare(paramName))
			return true;
	}


	return false;
}

void Material::setParamVec3(string paramName, glm::vec3 paramValue)
{

	auto found = params.find(paramName);
	if (found != params.end())
		params[paramName] = Holder(VEC3,paramValue);

	else
		cerr << "Material error: " << paramName << " does not exist" << endl;
}

void Material::setParamFloat(string paramName, float paramValue)
{

	auto found = params.find(paramName);
	if (found != params.end())
		params[paramName] = Holder(VEC3, paramValue);

	else
		cerr << "Material error: " << paramName << " does not exist" << endl;
}

void Material::setParamTexture(string paramName, shared_ptr<Texture> paramValue)
{

	auto found = params.find(paramName);
	if (found != params.end())
		params[paramName] = Holder(TEXTURE, paramValue);

	else
		cerr << "Material error: " << paramName << " does not exist" << endl;
}

shared_ptr<Texture> Material::getTextureParam()
{
	auto it = params.begin();

	while (it != params.end())
	{
		if (it->second.isTexture())
		{
			return it->second.operator std::weak_ptr<Texture>().lock();
		}
	}

	return nullptr;
}