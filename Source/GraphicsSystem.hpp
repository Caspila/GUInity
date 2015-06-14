#pragma once


#include <vector>
#include "Module.hpp"
//#include "Actor.h"
//#include "Camera.h"
#include <PxPhysicsAPI.h>
//#include "print.h"
//#include "Light.h"
#include "Ray.hpp"
#include "World.hpp"
#include <glm/glm.hpp>
//#include "GLFWGraphicsSystem.hpp"
class Camera;
class Actor;
class Light;
class Shader;
class Material;
class MeshRenderer;
class GLFWGraphicsSystem;
class QOpenGLVertexArrayObject;
class UIWidget;
class Texture;
struct MeshVertex;


using namespace physx;

/** GraphicsSystem handles the Graphics of the Engine.

	The idea behind creating an abstract class would be to allow for different Graphic API's to
	handle how images are drawn. For example, change from OpenGL to DirectX easily.

	This is the class that knows how to draw images on the screen.
*/
class GraphicsSystem

{

protected:
	/** Handle to the window*/
	shared_ptr<GLFWwindow> window;
	
	/** Shader used to debug Physics Information*/
	shared_ptr<Shader> debugShader;
	/** Material used to debug Physics Information*/
	shared_ptr<Material> debugMaterial;

	/** Shader used to render GUI*/
	shared_ptr<Shader> guiShader;
	/** Material used to render GUI*/
	shared_ptr<Material> guiMaterial;

	glm::mat4 GUIMatrix;
public:

    static GraphicsSystem* getInstance();

	GraphicsSystem() {}; // Constructor? (the {} brackets) are needed here.
	// Dont forget to declare these two. You want to make sure they
	// are unaccessable otherwise you may accidently get copies of
	// your singleton appearing.
	GraphicsSystem(GraphicsSystem const&);              // Don't Implement
	void operator=(GraphicsSystem const&); // Don't implement

	virtual ~GraphicsSystem();

	/** Initialize the system, create the window and such
     @param[in] width The width of the screen
     @param[in] height The height of the screen
     */
    virtual int init(int width, int height) = 0;
	/** Shutdown the system, destroy window and release any allocated memory*/
    virtual void shutdown() = 0;
	/** Swap buffers*/
    virtual void swap() = 0;
	/** Clear buffers*/
    virtual void clear() = 0;
	/** Create debug shader to display Physics information on the screen*/
	virtual void createDebugShader() = 0;

    /** screen width Getter
     @return Screen width*/
    virtual int getScreenWidth() = 0;
    /** screen height Getter
     @return Screen height*/
    virtual int getScreenHeight() = 0;
    
	/** Renders Physics information on screen from the camera point of view
     @param[in] camera The camera that's being used to render
     @param[in] rb Physics render buffer
     @param[in] color Color of the lines
     */
    virtual void renderPhysicsDebug(shared_ptr<Camera> camera, const  physx::PxRenderBuffer& rb, const glm::vec4& color)=0;
	/** Renders meshes on the screen from the camera point of view
     @param[in] camera The camera that's being used to render
     @param[in] renderers The renderers that will be rendered
     @param[in] lights The lights of the world
     */
	virtual void render(shared_ptr<Camera> camera, vector < shared_ptr<MeshRenderer>>& renderers, vector<shared_ptr<Light>>& lights)=0;



    /** Generates a new Vertex Array - Used for mesh vertice data
     @param[in] size Number of vertex arrays to generate
     @param[out] vao The created vertex array
     */
    virtual void generateVertexArrays(const GLuint size, GLuint& vao) = 0;

	/** Generates a new Buffer Array
     @param[in] size Number of buffers arrays to generate
     @param[out] bo The created buffer
     @param[in] dataSize The size of the dataBuffer
     @param[in] dataPointer The data
     @param[in] usage The usage type of the buffer
     */
    virtual void generateBuffer(const GLuint size, GLuint& bo, GLenum type, int dataSize, void *dataPointer, GLenum drawType) =0;
	/** Release buffer
     @param[in] size Number of buffers to delete
     @param[in] bo Buffers to delete
     */
	virtual void deleteBuffer(GLuint size, GLuint &bo) = 0;

	/** Creates a new shader
     @param[in] shaderType The type of the shader
     @return Created shaderID
     */
    virtual GLuint createShader(GLenum shaderType) = 0;
    /** Release shader
     @param[in] shaderID Shader to release
     */
	virtual void deleteShader(GLuint shaderID) = 0;
	/** Compile a shader
     @param[in] shaderID Shader to compile
     @param[in] size Size of the data buffer
     @param[in] dataPointer Shader data
     */
	virtual void compileShader(GLuint shaderID, GLuint size,const char* dataPointer) = 0;
	/** Creates a new shader program
     @return The shader program */
    virtual GLuint createShaderProgram() = 0;
	/** Merge VertexShader and FragmentShader to one
     @param[in] programID Program ID that holds both shaders
     @param[in] vertexShaderID Vertex Shader
     @param[in] fragmentShaderID Fragment Shader
     */
	virtual void attachAndLinkShader(GLuint ProgramID,GLuint VertexShaderID,GLuint FragmentShaderID) = 0;

	/** Gets the uniform location for a string in a shader
     @param[in] programID The shader program
     @param[in] name The name of the uniform location
     @return The uniform location ID*/
    virtual GLint getUniformLocation(GLuint programID,const char* name) = 0;
    
	/** Gets a reference to a default white texture
     @return Reference to white texture */
	virtual shared_ptr<Texture> getDefaultTexture() = 0;

	/** window Getter */
	virtual shared_ptr<GLFWwindow> getWindow() { return window; }
  
    
    /** Render Widgets on screen */
	virtual void renderGUI(vector<shared_ptr<UIWidget>> uiWidgetVector) = 0;
};

