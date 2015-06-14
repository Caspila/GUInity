#ifndef GLFWGRAPHICSYSTEM_H
#define GLFWGRAPHICSYSTEM_H

#include "GraphicsSystem.hpp"
#include "Holder.hpp"
#include <map>


class GLFWGraphicsSystem : public GraphicsSystem
{
private:
	/** Number of textures used on last draw call. Used to disable unused textures on OpenGL. */
    int currentTexturesUsed;
	/** Screen width */
	int screenWidth;
	/** Screen height */
	int screenHeight;
    
	/** Default white texture */
	shared_ptr<Texture> defaultTexture;
public:
	/** Default Destructor */
	virtual ~GLFWGraphicsSystem() {};
	/** Default Constructor */
	GLFWGraphicsSystem() {};
    
	/** Initialize the system, create the window and such
     @param[in] width The width of the screen
     @param[in] height The height of the screen
     */
    virtual int init(int width, int height) override;
	
    /** Shutdown the system, destroy window and release any allocated memory*/
    virtual void shutdown() override;
	/** Swap buffers*/
    virtual void swap() override;
	/** Clear buffers*/
	virtual void clear() override;
	/** Create debug shader to display Physics information on the screen*/
    virtual void createDebugShader() override;
    
    /** screen width Getter
     @return Screen width*/
    virtual int getScreenWidth() override;
    /** screen height Getter
     @return Screen height*/
    virtual int getScreenHeight() override;
    
	/** Renders Physics information on screen from the camera point of view
     @param[in] camera The camera that's being used to render
     @param[in] rb Physics render buffer
     @param[in] color Color of the lines
     */
	virtual void renderPhysicsDebug(shared_ptr<Camera> camera, const  physx::PxRenderBuffer& rb, const glm::vec4& color) override;
	/** Renders meshes on the screen from the camera point of view
     @param[in] camera The camera that's being used to render
     @param[in] renderers The renderers that will be rendered
     @param[in] lights The lights of the world
     */
	virtual void render(shared_ptr<Camera> camera, vector < shared_ptr<MeshRenderer>>& renderers, vector<shared_ptr<Light>>& lights) override;
    
	/** Generates a new Vertex Array - Used for mesh vertice data
     @param[in] size Number of vertex arrays to generate
     @param[out] vao The created vertex array
     */
    virtual void generateVertexArrays(const GLuint size, GLuint& vao) override;
    
	/** Generates a new Buffer Array
     @param[in] size Number of buffers arrays to generate
     @param[out] bo The created buffer
     @param[in] dataSize The size of the dataBuffer
     @param[in] dataPointer The data
     @param[in] usage The usage type of the buffer
     */
	virtual void generateBuffer(const GLuint size,GLuint& bo,GLenum type,int dataSize,void *dataPointer, GLenum usage) override;
	/** Release buffer
     @param[in] size Number of buffers to delete
     @param[in] bo Buffers to delete
     */
	virtual void deleteBuffer(GLuint size, GLuint &bo) override;
    
	/** Creates a new shader
     @param[in] shaderType The type of the shader
     @return Created shaderID
     */
    virtual GLuint createShader(GLenum shaderType) override;
	/** Release shader
     @param[in] shaderID Shader to release
     */
	virtual void deleteShader(GLuint shaderID) override;
	/** Compile a shader
     @param[in] shaderID Shader to compile
     @param[in] size Size of the data buffer
     @param[in] dataPointer Shader data
     */
    virtual void compileShader(GLuint shaderID, GLuint size,const char* dataPointer) override;
	/** Merge VertexShader and FragmentShader to one
     @param[in] programID Program ID that holds both shaders
     @param[in] vertexShaderID Vertex Shader
     @param[in] fragmentShaderID Fragment Shader
     */
	virtual void attachAndLinkShader(GLuint programID, GLuint vertexShaderID, GLuint fragmentShaderID) override;
	/** Creates a new shader program
     @return The shader program */
    virtual GLuint createShaderProgram() override;
    
	/** Gets the uniform location for a string in a shader
     @param[in] programID The shader program
     @param[in] name The name of the uniform location
     @return The uniform location ID*/
    virtual GLint getUniformLocation(GLuint programID,const char* name) override;
    
	/** Gets a reference to a default white texture 
     @return Reference to white texture */
	virtual shared_ptr<Texture> getDefaultTexture() override;
    
	
	/** Disable Textures that have are not needed for the current draw call 
     @param[in] nTextures Number of textures that will be used */
    void disableNonUsedTextures(int nTextures) const;
    
    /** Apply Materials to current rendering pass
     @param shaderProgram The OpenGL shader program
     @param parameters The parameters that will be applied
     */
    void applyMaterialParams(GLuint shaderProgram, const std::map<string,Holder>& parameters);
    
    /** Set a value for a uniform2fv value
     @param[in] shaderProgram The shader program
     @param[in] count The number of values
     @param[in] value The values
     @return true if could set the value, false if could not find they uniform location in the shader program
     */
    bool setUniform2fv(const GLuint shaderProgram, const GLchar* uniformName, int count, GLfloat* value);

    /** Set a value for a uniform4fv value
     @param[in] shaderProgram The shader program
     @param[in] count The number of values
     @param[in] value The values
     @return true if could set the value, false if could not find the uniform location in the shader program
     */
    bool  setUniform4fv(const GLuint shaderProgram, const GLchar* uniformName, int count, GLfloat* value);
    /** Set a value for a uniform3fv value
     @param[in] shaderProgram The shader program
     @param[in] count The number of values
     @param[in] value The values
     @return true if could set the value, false if could not find the uniform location in the shader program
     */
	bool  setUniform3fv(const GLuint shaderProgram, const GLchar* uniformName, int count, GLfloat* value);
    /** Set a value for a uniform1iv value
     @param[in] shaderProgram The shader program
     @param[in] count The number of values
     @param[in] value The values
     @return true if could set the value, false if could not find the uniform location in the shader program
     */
    bool  setUniform1iv(const GLuint shaderProgram, const GLchar* uniformName,int count, GLint* value);
    /** Set a value for a uniform4fv value
     @param[in] shaderProgram The shader program
     @param[in] count The number of values
     @param[in] value The values
     @return true if could set the value, false if could not find the uniform location in the shader program
     */
	bool  setUniformMatrix4fv(const GLuint shaderProgram, const GLchar* uniformName, int count, GLboolean transpose, GLfloat* value);
    /** Set a value for a uniform1fv value
     @param[in] shaderProgram The shader program
     @param[in] count The number of values
     @param[in] value The values
     @return true if could set the value, false if could not find the uniform location in the shader program
     */
	bool setUniform1fv(const GLuint shaderProgram, const GLchar* uniformName,int count, GLfloat* value);
    
    
    /** Render Widgets on screen */
	virtual void renderGUI(vector<shared_ptr<UIWidget>> uiWidgetVector)override;
    
};

#endif // GLFWGRAPHICSYSTEM_H
