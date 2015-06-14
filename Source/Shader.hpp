#pragma once

#include "Module.hpp"
#include <fstream>
#include <vector>
#include <map>
#include <glm/glm.hpp>
#include "Holder.hpp"
#include "Asset.hpp"

/** Shader is an Asset that holds the OpenGL-specific shader compilation data and parses the Vertex Shader and Fragment Shader looking for custom parameters that can be sent to the GPU */
class Shader : public Asset
#ifdef GUINITY_DEBUG
,public StaticCounter<Shader>
#endif
{
private:
    /** The filename of the Vertex shader */
    string vertexShaderFilename;
    /** The filename of the Fragment shader */
    string fragShaderFilename;
    
    /** The OpenGL-specific Program ID*/
    GLuint programID;
    
    /** Map each parameter name to a parameter type */
    map<string, ShaderParamType> params;
    /** Map each parameter name to OpenGL-specific uniform location ID */
	map<string, GLuint> paramID;
    

    
    /** Checks a line for uniform parameters that begins with a "_" Ex.: uniform vec4 _parameter
     @param[in] line the line that's being checked
     */
	void checkLineFormUniformParam(const string& line);
    /** Gets the OpenGL-specific uniform location IDs for each custom parameter */
	void createUniformLocationMap();
    
    
public:
    /** Default Constructor */
    Shader();
    /** Constructor
     @param vertexShaderFilename The filename of the vertex shader
     @param fragShaderFilename The filename of the fragment shader
     */
	Shader(string vertexShaderFilename, string fragShaderFilename);
    /** Default Destructor */
	virtual ~Shader();
    
    /** vertexShaderFilename Setter
     @param[in] vertexShaderFilename the filename of the vertex shader
     */
    void setVertexShaderFilename(string vertexShaderFilename);
    /** vertexShaderFilename Getter
     @return the filename of the vertex shader
     */
    string getVertexShaderFilename() const;

    
    /** fragShaderFilename Setter
     @param[in] fragShaderFilename the filename of the fragment shader
     */
    void setFragShaderFilename(string fragShaderFilename);
    /** fragShaderFilename Getter
     @return the filename of the fragment shader
     */
    string getFragShaderFilename() const;

    /** params Getter
     @return reference to the shader parameter types */
    const map<string, ShaderParamType>& getShaderParameters() const;
    
    /** programID Getter
     @return OpenGL-specific shader program ID
     */
    GLuint getProgramID() const;
    
    
    /** Load and compile the shaders */
	void loadShaders();


    
    
};

