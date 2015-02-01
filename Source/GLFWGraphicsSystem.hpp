#ifndef GLFWGRAPHICSYSTEM_H
#define GLFWGRAPHICSYSTEM_H

#include "GraphicsSystem.hpp"


class GLFWGraphicsSystem : public GraphicsSystem
{
public:
	/** Default Destructor */
	virtual ~GLFWGraphicsSystem() {};
	/** Default Constructor. Virtual because it inherits from GraphicsSystem */
	GLFWGraphicsSystem() {};

	/** Initialize the system, create the window and such*/
    virtual int init() override;
	/** Shutdown the system, destroy window and release any allocated memory*/
    virtual void shutdown() override;
	/** Swap buffers*/
    virtual void swap() override;
	/** Clear buffers*/
	virtual void clear() override;
	/** create debug shader to display Physics information on the screen*/
    virtual void createDebugShader() override;

    
	/** Renders Physics information on screen from the camera point of view */
	virtual void render(shared_ptr<Camera> camera, const  physx::PxRenderBuffer& rb, const glm::vec4& color) override;
	/** Renders meshes on the screen from the camera point of view */
	virtual void render(shared_ptr<Camera> camera, vector < shared_ptr<MeshRenderer>>& renderers, vector<shared_ptr<Light>>& lights) override;
	/** Render Widgets on screen */
	virtual void renderGUI(vector<shared_ptr<UIWidget>> uiWidgetVector)override;

	/** Generates a new Vertex Array - Used for mesh vertice data */
    virtual void generateVertexArrays(const GLuint id, GLuint& vao) override;

	/** Generates a new Buffer Array */
	virtual void generateBuffer(const GLuint id,GLuint& bo,GLenum type,int size,void *dataPointer, GLenum drawType) override;
	/** Release buffer */
	virtual void deleteBuffer(GLuint size, GLuint &bo) override;

	/** Creates a new shader */
    virtual GLuint createShader(GLenum shaderType) override;
	/** Release shader */
	virtual void deleteShader(GLuint shaderID) override;
	/** Compile the shader */
    virtual void compileShader(GLuint shaderID, GLuint size,const char* dataPointer) override;
	/** Merge VertexShader and FragmentShader to one */
	virtual void attachAndLinkShader(GLuint ProgramID, GLuint VertexShaderID, GLuint FragmentShaderID) override;
	/** Creates a new shader program */
    virtual GLuint createShaderProgram() override;

	/** Gets the uniform location for a string in a shader */
    virtual GLint getUniformLocation(GLuint programID,const char* name) override;

	
};

#endif // GLFWGRAPHICSYSTEM_H
