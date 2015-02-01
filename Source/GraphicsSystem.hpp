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

	/** Initialize the system, create the window and such*/
    virtual int init() = 0;
	/** Shutdown the system, destroy window and release any allocated memory*/
    virtual void shutdown() = 0;
	/** Swap buffers*/
    virtual void swap() = 0;
	/** Clear buffers*/
    virtual void clear() = 0;
	/** create debug shader to display Physics information on the screen*/
	virtual void createDebugShader() = 0;

	
    
	/** Renders Physics information on screen from the camera point of view */
    virtual void render(shared_ptr<Camera> camera, const  physx::PxRenderBuffer& rb, const glm::vec4& color)=0;
	/** Renders meshes on the screen from the camera point of view */
	virtual void render(shared_ptr<Camera> camera, vector < shared_ptr<MeshRenderer>>& renderers, vector<shared_ptr<Light>>& lights)=0;
	/** Render Widgets on screen */
	virtual void renderGUI(vector<shared_ptr<UIWidget>> uiWidgetVector) = 0;


	/** Generates a new Vertex Array - Used for mesh vertice data */
    virtual void generateVertexArrays(const GLuint size, GLuint& vao) = 0;

	/** Generates a new Buffer Array */
    virtual void generateBuffer(const GLuint size, GLuint& bo, GLenum type, int dataSize, void *dataPointer, GLenum drawType) =0;
	/** Release buffer */
	virtual void deleteBuffer(GLuint size, GLuint &bo) = 0;

	/** Creates a new shader */
    virtual GLuint createShader(GLenum shaderType) = 0;
	/** Compile the shader */
	virtual void compileShader(GLuint shaderID, GLuint size,const char* dataPointer) = 0;
	/** Creates a new shader program */
    virtual GLuint createShaderProgram() = 0;
	/** Merge VertexShader and FragmentShader to one */
	virtual void attachAndLinkShader(GLuint ProgramID,GLuint VertexShaderID,GLuint FragmentShaderID) = 0;
	/** Release shader */
	virtual void deleteShader(GLuint shaderID) = 0;

	/** Gets the uniform location for a string in a shader */
    virtual GLint getUniformLocation(GLuint programID,const char* name) = 0;

	/** window Getter */
	virtual shared_ptr<GLFWwindow> getWindow() { return window; }
  
};

