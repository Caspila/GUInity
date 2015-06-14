//
//  Material.cpp
//  GUInity Project - A 3D component-based one-man game engine
//
//  Created by Guilherme Cunha on 2014-12-30.
//  Copyright (c) 2014 Guilherme Cunha. All rights reserved.
//

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

/** Constructor
 @param[in] the Shader of this Material */
Material::Material(shared_ptr<Shader> shader) :
shader {shader}
{
    map<string, ShaderParamType> shaderParams = shader->getShaderParameters();
    
    // Create value slots for each parameter of the shader
	std::map<string, ShaderParamType>::iterator it = shaderParams.begin();
    
	for (; it != shaderParams.end(); it++)
	{
        switch (it->second)
        {
            case TEXTURE:
                params.insert(std::pair<string, Holder>(it->first, Holder(TEXTURE, GraphicsSystem::getInstance()->getDefaultTexture())));
                break;
            case VEC4:
                params.insert(std::pair<string, Holder>(it->first, Holder(VEC4, glm::vec4(1,1,1,1))));
                break;
            case VEC2:
                params.insert(std::pair<string, Holder>(it->first, Holder(VEC2, glm::vec2(0,0))));
                break;
            default:
                cout << "Error: Unknown variable type for material param" << endl;
                break;
                }
                }
                
#ifdef GUINITY_DEBUG
                nCount++;
#endif
                }
                
                /** Default Destructor */
                Material::~Material()
                {
#ifdef GUINITY_DEBUG
                    nCount--;
                    cout << "Material destroyed (" << nCount << " remaining)" << endl;
#endif
                    
                }
                
                /** shader Setter
                 @param[in] shader the Shader of this Material*/
                void Material::setShader(shared_ptr<Shader> shader)
                {
                    this->shader = shader;
                }
                /** shader Getter
                 @return the Shader of this Material*/
                const shared_ptr<Shader> Material::getShader() const
                {
                    return shader;
                }
                /** Get the Shader program (OpenGL specific)
                 @return the OpenGL specific program ID of the Shader
                 */
                GLuint Material::getShaderProgram()
                {
                    return shader->getProgramID();
                }
                
                /** Checks if param exists on params map
                 @param[in] paramName the name of the parameter
                 @return true if paramName exists, false otherwise
                 */
                bool Material::paramExists(const string paramName)
                {
                    std::map<string, Holder>::iterator it = params.begin();
                    
                    for (; it != params.end(); it++)
                    {
                        if (it->first.compare(paramName))
                            return true;
                    }
                    
                    return false;
                }
                
                /** Set a vec2 value for a Shader parameter
                 @param[in] paramName the name of the parameter
                 @param[in] paramValue the value of the parameter
                 */
                void Material::setParamVec2(const string paramName,const glm::vec2& paramValue)
                {
                    
                    auto found = params.find(paramName);
                    if (found != params.end())
                        params[paramName] = Holder(VEC2,paramValue);
                    
                    else
                        cerr << "Material error: " << paramName << " does not exist" << endl;
                }
                
                /** Set a vec4 value for a Shader parameter
                 @param[in] paramName the name of the parameter
                 @param[in] paramValue the value of the parameter
                 */
                glm::vec2 Material::getParamVec2(const string paramName)
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
                
                /** Set a vec4 value for a Shader parameter
                 @param[in] paramName the name of the parameter
                 @param[in] paramValue the value of the parameter
                 */
                void Material::setParamVec4(string paramName,const glm::vec4& paramValue)
                {
                    
                    auto found = params.find(paramName);
                    if (found != params.end())
                        params[paramName] = Holder(VEC4,paramValue);
                    
                    else
                        cerr << "Material error: " << paramName << " does not exist" << endl;
                }
                
                /** Set a float value for a Shader parameter
                 @param[in] paramName the name of the parameter
                 @param[in] paramValue the value of the parameter
                 */
                void Material::setParamFloat(string paramName, float paramValue)
                {
                    
                    auto found = params.find(paramName);
                    if (found != params.end())
                        params[paramName] = Holder(VEC4, paramValue);
                    
                    else
                        cerr << "Material error: " << paramName << " does not exist" << endl;
                }
                
                /** Set a Texture reference value for a Shader parameter
                 @param[in] paramName the name of the parameter
                 @param[in] paramValue the value of the parameter
                 */
                void Material::setParamTexture(string paramName, shared_ptr<Texture> paramValue)
                {
                    
                    auto found = params.find(paramName);
                    if (found != params.end())
                        params[paramName] = Holder(TEXTURE, paramValue);
                    
                    else
                        cerr << "Material error: " << paramName << " does not exist" << endl;
                }
                
                
                /** Gets all Texture params
                 @return a vector with all the parameters of the Material that are of the type Texture
                 */
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
                
                /** Gets all Texture params
                 @return a vector with all the parameters of the Material that are of the type vec4
                 */
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
                
                /** Gets all Texture params
                 @return a vector with all the parameters of the Material that are of the type vec2
                 */
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