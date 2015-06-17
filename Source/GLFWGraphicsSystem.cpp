//
//  GLFWGraphicsSystem.cpp
//  opengl_testing_mag
//
//  Created by Guilherme Cunha on 2015-01-10.
//  Copyright (c) 2015 Guilherme Cunha. All rights reserved.
//

#include "GLFWGraphicsSystem.hpp"
#include "GraphicsSystem.hpp"
#include "Mesh.hpp"
#include "MeshRenderer.hpp"
#include "MeshFilter.hpp"
#include "Actor.hpp"
#include "Transform.hpp"
#include "Camera.hpp"
#include "Light.hpp"
#include "Material.hpp"
#include "Shader.hpp"
#include "AssetDatabase.hpp"
#include "Texture.hpp"
#include "Time.hpp"
#include <glm/common.hpp>
#include <glm/gtc/type_ptr.hpp>

/** Initialize the system, create the window and such
 @param[in] width The width of the screen
 @param[in] height The height of the screen
 */
int GLFWGraphicsSystem::init(int width, int height)
{
    screenWidth = width;
    screenHeight = height;
    
    if (!glfwInit()) {
		fprintf(stderr, "ERROR: could not start GLFW3\n");
		return 1;
	}
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 0);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
    
	window.reset(glfwCreateWindow(screenWidth, screenHeight, "Hello Triangle", NULL, NULL), glfwDestroyWindow);
	if (!window) {
		fprintf(stderr, "ERROR: could not open window with GLFW3\n");
		glfwTerminate();
		return 1;
	}
	glfwMakeContextCurrent(window.get());
	// start GLEW extension handler
	glewExperimental = GL_TRUE;
	glewInit();
	const GLubyte* renderer = glGetString(GL_RENDERER); // get renderer string
	const GLubyte* version = glGetString(GL_VERSION); // version as a string
	printf("Renderer: %s\n", renderer);
	printf("OpenGL version supported %s\n", version);
	// tell GL to only draw onto a pixel if the shape is closer to the viewer
	glEnable(GL_DEPTH_TEST); // enable depth-testing
	glDepthFunc(GL_LESS); // depth-testing interprets a smaller value as "closer"
	
    glEnable(GL_CULL_FACE);
    glFrontFace(GL_CCW);
    
    createDebugShader();
    
	defaultTexture = AssetDatabase::createTexture("white.png");
    
	return 0;
    
}
/** Shutdown the system, destroy window and release any allocated memory*/
void GLFWGraphicsSystem::shutdown()
{
    debugMaterial.reset();
	debugShader.reset();
    
    guiMaterial.reset();
	guiShader.reset();
	
    glfwTerminate();
    
}
/** Swap buffers*/
void GLFWGraphicsSystem::swap()
{
    glfwPollEvents();
    // put the stuff we've been drawing onto the display
    glfwSwapBuffers(window.get());
    
}
/** Clear buffers*/
void GLFWGraphicsSystem::clear()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

/** create debug shader to display Physics information on the screen*/
void GLFWGraphicsSystem::createDebugShader()
{
    debugShader = make_shared<Shader>(CommonData("vs.vs").c_str(),CommonData("fs.fragmentshader").c_str());
    debugMaterial = make_shared<Material>(debugShader);
    
    guiShader = make_shared<Shader>(CommonData("vsOrtho.vs").c_str(),CommonData("fsOrtho.fragmentshader").c_str());
    guiMaterial = make_shared<Material>(guiShader);
    
    
    GUIMatrix = glm::ortho(0.0f, (float)screenWidth, (float)screenHeight, 0.0f, -5.0f, 5.0f);
}

/** screen width Getter
 @return Screen width*/
int GLFWGraphicsSystem::getScreenWidth()
{
    return screenWidth;
}
/** screen height Getter
 @return Screen height*/
int GLFWGraphicsSystem::getScreenHeight()
{
    return screenHeight;
}


/** Renders meshes on the screen from the camera point of view
 @param[in] camera The camera that's being used to render
 @param[in] renderers The renderers that will be rendered
 @param[in] lights The lights of the world
 */
void GLFWGraphicsSystem::render(shared_ptr<Camera> camera, vector < shared_ptr<MeshRenderer>>& renderers, vector<shared_ptr<Light>>& lights)
//void GraphicsSystem::render(World& world)
{
    camera->computeModelViewMatrix();
    
    //glEnable(GL_BLEND);
    //glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    
    shared_ptr<MeshRenderer> meshRenderer;
    shared_ptr<Actor> actor;
    shared_ptr<MeshComponent> meshComponent;
    shared_ptr<Material> material;
    for (int i = 0; i < renderers.size(); i++)
    {
        //                Time::stopwatchStart();
        
        meshRenderer = renderers[i];
        
        if(!meshRenderer->getIsActive())
            continue;
        
        actor = meshRenderer->getActor();
        
		meshComponent = meshRenderer->getMeshComponent();
		if (!meshComponent)
			continue;
        material = meshRenderer->getMaterial();
        
        
        GLuint shaderProgram = material->getShaderProgram();
        //        cout << "Get data:" <<       Time::stopwatchEnd() << endl;
        
        //        Time::stopwatchStart();
        
        //        glLinkProgram(shaderProgram);
        
        //        cout << "Link shader:" <<       Time::stopwatchEnd() << endl;
        glUseProgram(shaderProgram);
        
        
        
        
        
        //                Time::stopwatchStart();
        float ambientLight = 0.1f;
        glm::vec3 ambientLightColor(1.0, 1.0, 1.0);
        
		setUniform3fv(shaderProgram, "ambientLightColor", 1, glm::value_ptr(ambientLightColor));
		setUniform1fv(shaderProgram, "ambientLightIntensity",1, &ambientLight);
        
        
        
		setUniformMatrix4fv(shaderProgram, "camera", 1, GL_FALSE, &camera->getMVPMatrix()[0][0]);
		setUniformMatrix4fv(shaderProgram, "model", 1, GL_FALSE, &actor->transform->getModelMatrix()[0][0]);
        
        
        
        for (int j = 0; j < lights.size(); j++)
        {
            shared_ptr<Light> light = lights[j];
            
			setUniform3fv(shaderProgram, "lightPos", 1, &light->getActor()->transform->position[0]);
			setUniform3fv(shaderProgram, "lightIntensity", 1, &light->getColor()[0]);
            
        }
        
        disableNonUsedTextures(material->getNTextureParams());
        
        const map<string,Holder> materialParams = material->getAllParams();
        
        applyMaterialParams(shaderProgram, materialParams);
        
        
		glBindVertexArray(meshComponent->getMesh()->getVertexArrayID());
        
        glEnableVertexAttribArray(0);
		glBindBuffer(GL_ARRAY_BUFFER, meshComponent->getMesh()->getVertexBuffer());
        
        //Vertex
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(MeshVertex), (void*)(0));
        
        int beginNormal = sizeof(glm::vec3) + sizeof(glm::vec2);
        
        //Normal
        glEnableVertexAttribArray(2);
        glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, sizeof(MeshVertex), (void*)(beginNormal));
        
        int beginUV = sizeof(glm::vec3);
        
        //UV
        glEnableVertexAttribArray(3);
        glVertexAttribPointer(3, 2, GL_FLOAT, GL_FALSE, sizeof(MeshVertex), (void*)(beginUV));
        
		
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, meshComponent->getMesh()->getTrianglesBuffer());
        
        // draw points 0-3 from the currently bound VAO with current in-use shader
		glDrawElements(GL_TRIANGLES, meshComponent->getMesh()->getTrianglesCount(), GL_UNSIGNED_SHORT, NULL);
        
        glDisableVertexAttribArray(0);
        glDisableVertexAttribArray(2);
        glDisableVertexAttribArray(3);
        
    }
    
}

/** Renders Physics information on screen from the camera point of view
 @param[in] camera The camera that's being used to render
 @param[in] rb Physics render buffer
 @param[in] color Color of the lines
 */
void GLFWGraphicsSystem::renderPhysicsDebug(shared_ptr<Camera> camera,const physx::PxRenderBuffer& rb,const glm::vec4& color)
{
    float *points = new float[rb.getNbLines() * 6];
    
    //glDisable(GL_BLEND);
    
    
    for (PxU32 i = 0; i < rb.getNbLines(); i++)
    {
        
        const PxDebugLine& line = rb.getLines()[i];
        // render the line
        
        points[i * 6] = line.pos0.x;
        points[i * 6+1] = line.pos0.y;
        points[i * 6+2] = line.pos0.z;
        points[i * 6+3] = line.pos1.x;
        points[i * 6+4] = line.pos1.y;
        points[i * 6+5] = line.pos1.z;
        
        
    }
    
    GLuint vbo = 0;
    glGenBuffers(1, &vbo);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData(GL_ARRAY_BUFFER, 6 * rb.getNbLines() * sizeof(float), points, GL_STATIC_DRAW);
    
    GLuint vao = 0;
    glGenVertexArrays(1, &vao);
    glBindVertexArray(vao);
    glEnableVertexAttribArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, NULL);
    
    
    glLinkProgram(debugMaterial->getShaderProgram());
    glUseProgram(debugMaterial->getShaderProgram());
    
    glBindVertexArray(vao);
    
	
    glUniform3fv(getUniformLocation(debugMaterial->getShaderProgram(), "difuse") , 1, &color[0]);
    
    
	glUniformMatrix4fv(getUniformLocation(debugMaterial->getShaderProgram(), "MVP"), 1, GL_FALSE, &camera->getMVPMatrix()[0][0]);
    
    glDrawArrays(GL_LINES, 0, 2 * rb.getNbLines());
    
    glBindVertexArray(0); // Unbind our Vertex Array Object
    
    glDisableVertexAttribArray(0);
    
    glDeleteBuffers(1, &vbo);
    glDeleteVertexArrays(1, &vao);
    
    delete []points;
}

/** Generates a new Vertex Array - Used for mesh vertice data */
void GLFWGraphicsSystem::generateVertexArrays(const GLuint size, GLuint& vao)
{
    glGenVertexArrays(size, &vao);
    glBindVertexArray(vao);
    
}

/** Generates a new Buffer Array
 @param[in] size Number of buffers arrays to generate
 @param[out] bo The created buffer
 @param[in] dataSize The size of the dataBuffer
 @param[in] dataPointer The data
 @param[in] usage The usage type of the buffer
 */
void GLFWGraphicsSystem::generateBuffer(const GLuint size, GLuint& bo, GLenum type, int dataSize, void *dataPointer, GLenum usage)
{
    glGenBuffers(size, &bo);
    glBindBuffer(type, bo);
    glBufferData(type, dataSize, dataPointer, usage);
    
}

/** Release buffer
 @param[in] size Number of buffers to delete
 @param[in] bo Buffers to delete
 */
void GLFWGraphicsSystem::deleteBuffer(GLuint size, GLuint &bo)
{
	glDeleteBuffers(size, &bo);
}

/** Creates a new shader
 @param[in] shaderType The type of the shader
 @return Created shaderID
 */
GLuint GLFWGraphicsSystem::createShader(GLenum shaderType)
{
    return glCreateShader(shaderType);
}

/** Release shader
 @param[in] shaderID Shader to release
 */
void GLFWGraphicsSystem::deleteShader(GLuint shaderID)
{
	glDeleteShader(shaderID);
}

/** Compile a shader
 @param[in] shaderID Shader to compile
 @param[in] size Size of the data buffer
 @param[in] dataPointer Shader data
 */
void GLFWGraphicsSystem::compileShader(GLuint shaderID, GLuint size,const char* dataPointer)
{
    int InfoLogLength;
    GLint Result = GL_FALSE;
    
    glShaderSource(shaderID, size, &dataPointer, NULL);
    glCompileShader(shaderID);
    
    glGetShaderiv(shaderID, GL_COMPILE_STATUS, &Result);
    glGetShaderiv(shaderID, GL_INFO_LOG_LENGTH, &InfoLogLength);
    std::vector<char> shaderErrorMessage(InfoLogLength);
    glGetShaderInfoLog(shaderID, InfoLogLength, NULL, &shaderErrorMessage[0]);
    fprintf(stdout, "%s\n", &shaderErrorMessage[0]);
    
}
/** Merge VertexShader and FragmentShader to one
 @param[in] programID Program ID that holds both shaders
 @param[in] vertexShaderID Vertex Shader
 @param[in] fragmentShaderID Fragment Shader
 */
void GLFWGraphicsSystem::attachAndLinkShader(GLuint programID, GLuint vertexShaderID, GLuint fragmentShaderID)
{
	glAttachShader(programID, vertexShaderID);
	glAttachShader(programID, fragmentShaderID);
	glLinkProgram(programID);
}

/** Creates a new shader program
 @return The shader program */
GLuint GLFWGraphicsSystem::createShaderProgram()
{
    return glCreateProgram();
}


/** Gets the uniform location for a string in a shader
 @param[in] programID The shader program
 @param[in] name The name of the uniform location
 @return The uniform location ID*/
GLint GLFWGraphicsSystem::getUniformLocation(const GLuint shaderProgram, const GLchar* uniformName) {
	
	if (!uniformName)
    {
//        cout << "Warning: Trying to get Uniform Location with null uniform name " << endl;
		return -1;
    }

    
	GLint uniform = glGetUniformLocation(shaderProgram, uniformName);
//	if (uniform == -1)
//        cout << "Warning: Shader uniform " << uniformName << " not found " << endl;
    
	return uniform;
}

/** Gets a reference to a default white texture
 @return Reference to white texture */
shared_ptr<Texture> GLFWGraphicsSystem::getDefaultTexture()
{
    
	return defaultTexture;
}





/** Disable Textures that have are not needed for the current draw call
 @param[in] nTextures Number of textures that will be used */
void GLFWGraphicsSystem::disableNonUsedTextures(int nTextures) const
{
    int startingIndex = currentTexturesUsed -(currentTexturesUsed - nTextures);
    
    for(int i = startingIndex; i < currentTexturesUsed; i++)
    {
        glActiveTexture(GL_TEXTURE0+i);
        glDisable(GL_TEXTURE_2D);
    }
}



/** Apply Materials to current rendering pass
 @param shaderProgram The OpenGL shader program
 @param parameters The parameters that will be applied
 */
void GLFWGraphicsSystem::applyMaterialParams(GLuint shaderProgram, const std::map<string,Holder>& parameters)
{
    
    
    int texCount = 0;
    for(auto&parameter : parameters)
    {
        
        switch (parameter.second.getType()) {
            case ShaderParamType::FLOAT:
                
                break;
            case ShaderParamType::TEXTURE:
            {
                glActiveTexture(GL_TEXTURE0+texCount);
                glBindTexture(GL_TEXTURE_2D, parameter.second.getTexture()->getTextureID());
                glUniform1i(getUniformLocation(shaderProgram, parameter.first.c_str()), 0);
                break;
            }
            case ShaderParamType::VEC2:
            {
                glm::vec2 vec = parameter.second.getVec2();
                setUniform2fv(shaderProgram, parameter.first.c_str(), 1, glm::value_ptr(vec));
                break;
            }
            case ShaderParamType::VEC4:
            {
                glm::vec4 vec4 = parameter.second.getVec4();
                setUniform4fv(shaderProgram, parameter.first.c_str(), 1, glm::value_ptr(vec4));
                break;
            }
            default:
                
                break;
        }
        
    }
    currentTexturesUsed = texCount;
}

/** Set a value for a uniform2fv value
 @param[in] shaderProgram The shader program
 @param[in] count The number of values
 @param[in] value The values
 @return true if could set the value, false if could not find the uniform location in the shader program
 */
bool  GLFWGraphicsSystem::setUniform2fv(const GLuint shaderProgram, const GLchar* uniformName, int count, GLfloat* value)
{
	GLint uniformLocation = getUniformLocation(shaderProgram, uniformName);
    
	if (uniformLocation != -1)
	{
		glUniform2fv(uniformLocation, count, value);
		return true;
	}
    
	return false;
}
/** Set a value for a uniform4fv value
 @param[in] shaderProgram The shader program
 @param[in] count The number of values
 @param[in] value The values
 @return true if could set the value, false if could not find the uniform location in the shader program
 */
bool  GLFWGraphicsSystem::setUniform4fv(const GLuint shaderProgram, const GLchar* uniformName, int count, GLfloat* value)
{
	GLint uniformLocation = getUniformLocation(shaderProgram, uniformName);
    
	if (uniformLocation != -1)
	{
		glUniform4fv(uniformLocation, count, value);
		return true;
	}
    
	return false;
}
/** Set a value for a uniform3fv value
 @param[in] shaderProgram The shader program
 @param[in] count The number of values
 @param[in] value The values
 @return true if could set the value, false if could not find the uniform location in the shader program
 */
bool  GLFWGraphicsSystem::setUniform3fv(const GLuint shaderProgram, const GLchar* uniformName, int count, GLfloat* value)
{
	GLint uniformLocation = getUniformLocation(shaderProgram, uniformName);
    
	if (uniformLocation != -1)
	{
		glUniform3fv(uniformLocation, count, value);
		return true;
	}
    
	return false;
}

/** Set a value for a uniform1fv value
 @param[in] shaderProgram The shader program
 @param[in] count The number of values
 @param[in] value The values
 @return true if could set the value, false if could not find the uniform location in the shader program
 */
bool  GLFWGraphicsSystem::setUniform1fv(const GLuint shaderProgram, const GLchar* uniformName,int vertexSize, GLfloat* vertex)
{
	GLint uniformLocation = getUniformLocation(shaderProgram, uniformName);
    
	if (uniformLocation != -1)
	{
		glUniform1fv(uniformLocation,vertexSize, &vertex[0]);
		return true;
	}
    
	return false;
}
/** Set a value for a uniform4fv value
 @param[in] shaderProgram The shader program
 @param[in] count The number of values
 @param[in] value The values
 @return true if could set the value, false if could not find the uniform location in the shader program
 */
bool  GLFWGraphicsSystem::setUniformMatrix4fv(const GLuint shaderProgram, const GLchar* uniformName, int count, GLboolean transpose, GLfloat* value)
{
	GLint uniformLocation = getUniformLocation(shaderProgram, uniformName);
    
	if (uniformLocation != -1)
	{
		glUniformMatrix4fv(uniformLocation, count, transpose, value);
		return true;
	}
    
	return false;
}


bool  GLFWGraphicsSystem::setUniform1iv(const GLuint shaderProgram, const GLchar* uniformName, int count,GLint *value)
{
	GLint uniformLocation = getUniformLocation(shaderProgram, uniformName);
    
	if (uniformLocation != -1)
	{
		glUniform1iv(uniformLocation,count, value);
		return true;
	}
    
	return false;
}

