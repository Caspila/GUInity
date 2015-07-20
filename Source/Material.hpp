//
//  Material.hpp
//  GUInity Project - A 3D component-based one-man game engine
//
//  Created by Guilherme Cunha on 2014-12-30.
//  Copyright (c) 2014 Guilherme Cunha. All rights reserved.
//

#pragma once


#include "Module.hpp"
#include <map>
#include <vector>
#include "Holder.hpp"
#include "Asset.hpp"


class Shader;
class Texture;

/** Material is an Asset that allows the same Shader to be used several times with different parameters.
 For example, a Textured Diffuse Shader could be use for both a crate and the floor, the only thing that changes is the Texture.
 
 Currently, the only parameters supported by Shaders and therefore Materials are Textures, vec4 and vec2.
 */
class Material : public Asset
#ifdef GUINITY_DEBUG
,public StaticCounter<Material>
#endif
{
private:
	/** The Shader */
	shared_ptr<Shader> shader;
	/** The Shader parameters for this Material */
	map<string, Holder> params;
    
    /** Number of texture parameters of this Material */
    int nTextureParams;
    
public:
	/** Default Constructor */
	Material();
	/** Constructor
     @param[in] the Shader of this Material */
	Material(shared_ptr<Shader> shader);
	/** Default Destructor */
	virtual ~Material();
    
	/** shader Setter
     @param[in] shader the Shader of this Material*/
	void setShader(shared_ptr<Shader> shader);
	/** shader Getter
     @return the Shader of this Material*/
	const shared_ptr<Shader> getShader() const;
    
	/** Get the Shader program (OpenGL specific)
     @return the OpenGL specific program ID of the Shader
     */
	GLuint getShaderProgram();
    
	/** Checks if param exists on params map
     @param[in] paramName the name of the parameter
     @return true if paramName exists, false otherwise
     */
	bool paramExists(const string paramName);
    /** Set a vec2 value for a Shader parameter
     @param[in] paramName the name of the parameter
     @param[in] paramValue the value of the parameter
     */
    void setParamVec2(const string paramName,const glm::vec2& paramValue);
    /** Get the value for a Shader parameter
     @param[in] paramName the name of the parameter
     @return the value of the parameter paramName
     */
    glm::vec2 getParamVec2(const string paramName);
    /** Set a vec4 value for a Shader parameter
     @param[in] paramName the name of the parameter
     @param[in] paramValue the value of the parameter
     */
	void setParamVec4(string paramName, const glm::vec4& paramValue);
    /** Set a float value for a Shader parameter
     @param[in] paramName the name of the parameter
     @param[in] paramValue the value of the parameter
     */
    void setParamFloat(string paramName, float paramValue);
    /** Set a Texture reference value for a Shader parameter
     @param[in] paramName the name of the parameter
     @param[in] paramValue the value of the parameter
     */
	void setParamTexture(string paramName, shared_ptr<Texture> paramValue);
    
    /** Typedefs to make it easier to user parameters */
    typedef pair<string, shared_ptr<Texture>> StringTexPair;
	typedef pair<string, glm::vec4> StringVec4Pair;
   	typedef pair<string, glm::vec2> StringVec2Pair;
    
    
    /** nTextures Getter
     @return The number of Texture parameters of this Material
     */
    int getNTextureParams() const;
    
    /** params Getter
     @return Map of all the parameters 
     */
    const map<string,Holder>& getAllParams()const ;
    
	/** Gets all Texture params
     @return a vector with all the parameters of the Material that are of the type Texture
     */
	vector<StringTexPair> getAllTextureParams();
	/** Gets all vec4 params
     @return a vector with all the parameters of the Material that are of the type vec4
     */
	vector<StringVec4Pair> getAllVec4Params();
	/** Gets all vec2 params
     @return a vector with all the parameters of the Material that are of the type vec2
     */
    vector<StringVec2Pair> getAllVec2Params();
    
    
    
};

