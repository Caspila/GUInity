#include "Shader.hpp"
#include <sstream>
#include "GraphicsSystem.hpp"
#include <regex>

/** Default Constructor */
Shader::Shader()
{
    
#ifdef GUINITY_DEBUG
	nCount++;
#endif
}

/** Constructor
 @param vertexShaderFilename The filename of the vertex shader
 @param fragShaderFilename The filename of the fragment shader
 */
Shader::Shader(string vertexShaderFilename, string fragShaderFilename)
: vertexShaderFilename {vertexShaderFilename}, fragShaderFilename{fragShaderFilename}
{
    
    
	loadShaders();
#ifdef GUINITY_DEBUG
	nCount++;
#endif
}

/** Default Destructor */
Shader::~Shader()
{
    glDeleteProgram(programID);
    
#ifdef GUINITY_DEBUG
	nCount--;
	cout << "Shader destroyed (" << nCount << " remaining)" << endl;
#endif
}

/** params Getter
 @return reference to the shader parameter types
 */
const map<string, ShaderParamType>& Shader::getShaderParameters() const
{
    return params;
}

/** programID Getter
 @return OpenGL-specific shader program ID
 */
GLuint Shader::getProgramID() const
{
    return programID;
}


/** Load and compile the shaders */
void Shader::loadShaders(){
    
    GLuint vertexShaderID = GraphicsSystem::getInstance()->createShader(GL_VERTEX_SHADER);
    GLuint fragmentShaderID = GraphicsSystem::getInstance()->createShader(GL_FRAGMENT_SHADER);
    
	// Read the Vertex Shader code from the file
	std::string vertexShaderCode;
	std::ifstream vertexShaderStream(vertexShaderFilename, std::ios::in);
	if (vertexShaderStream.is_open())
	{
		std::string Line = "";
		while (getline(vertexShaderStream, Line))
		{
			vertexShaderCode += "\n" + Line;
            
			checkLineFormUniformParam(Line);
            
		}
		vertexShaderStream.close();
	}
    
	// Read the Fragment Shader code from the file
	std::string fragmentShaderCode;
	std::ifstream fragmentShaderStream(fragShaderFilename, std::ios::in);
	if (fragmentShaderStream.is_open()){
		std::string Line = "";
		while (getline(fragmentShaderStream, Line))
		{
			fragmentShaderCode += "\n" + Line;
            
			checkLineFormUniformParam(Line);
            
		}
		fragmentShaderStream.close();
	}
    
    
	// Compile Vertex Shader
	printf("Compiling shader : %s\n", vertexShaderFilename.c_str());
	char const * vertexSourcePointer = vertexShaderCode.c_str();
    
    GraphicsSystem::getInstance()->compileShader(vertexShaderID,1,vertexSourcePointer);
    
	// Compile Fragment Shader
	printf("Compiling shader : %s\n", fragShaderFilename.c_str());
	char const * fragmentSourcePointer = fragmentShaderCode.c_str();
    
    GraphicsSystem::getInstance()->compileShader(fragmentShaderID,1,fragmentSourcePointer);
    
    
	// Link the program
	fprintf(stdout, "Linking program\n");
    
    programID = GraphicsSystem::getInstance()->createShaderProgram();
    GraphicsSystem::getInstance()->attachAndLinkShader(programID,vertexShaderID,fragmentShaderID);
    
    createUniformLocationMap();
}

/** Checks a line for uniform parameters that begins with a "_" Ex.: uniform vec4 _parameter
 @param[in] line the line that's being checked
 */
void Shader::checkLineFormUniformParam(const string& line)
{
	std::regex vec3Regex("uniform +(vec2|vec4|sampler2D) +(_[a-z|A-Z|0-9]+) *;");// [a - z | A - Z | 0 - 9] + +; ");// (sub)(.*)");
	std::smatch res;
	if (std::regex_search(line, res, vec3Regex))
	{
		// 0 is the full line
		// 1 is the type
		// 2 is the var name
		if (res.size() == 3)
		{
			if (res[1].str().compare("vec4")==0)
				params.insert(pair<string, ShaderParamType>(res[2].str(), ShaderParamType::VEC4));
			else if (res[1].str().compare("sampler2D")==0)
				params.insert(pair<string, ShaderParamType>(res[2].str(), ShaderParamType::TEXTURE));
            else if (res[1].str().compare("vec2")==0)
				params.insert(pair<string, ShaderParamType>(res[2].str(), ShaderParamType::VEC2));
		}
        
	}
    
}

/** Gets the OpenGL-specific uniform location IDs for each custom parameter */
void Shader::createUniformLocationMap()
{
	std::map<string, ShaderParamType>::iterator it = params.begin();
    
	for (; it != params.end(); it++)
	{
		const char* name = it->first.c_str();
        
        GLint uniformLocation = GraphicsSystem::getInstance()->getUniformLocation(programID, name);
        paramID.insert(pair<string, GLuint>(it->first,uniformLocation) );
	}
    
}


/** vertexShaderFilename Setter
 @param[in] vertexShaderFilename the filename of the vertex shader
 */
void Shader::setVertexShaderFilename(string vertexShaderFilename)
{
    this->vertexShaderFilename = vertexShaderFilename;
}
/** vertexShaderFilename Getter
 @return the filename of the vertex shader
 */
string Shader::getVertexShaderFilename() const
{
    return vertexShaderFilename;
}


/** fragShaderFilename Setter
 @param[in] fragShaderFilename the filename of the fragment shader
 */
void Shader::setFragShaderFilename(string fragShaderFilename)
{
    this-> fragShaderFilename = fragShaderFilename;
}
/** fragShaderFilename Getter
 @return the filename of the fragment shader
 */
string Shader::getFragShaderFilename() const
{
    return fragShaderFilename;
}

