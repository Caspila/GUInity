#ifndef GLFWGRAPHICSYSTEM_H
#define GLFWGRAPHICSYSTEM_H

#include "GraphicsSystem.hpp"

class GLFWGraphicsSystem : public GraphicsSystem
{
public:
    virtual int init() override;
    virtual void shutdown() override;
    virtual void swap() override;
    virtual void createDebugShader() override;
    virtual void clear() override;
    
    virtual GLint uniform(const GLuint shaderProgram, const GLchar* uniformName) override;

   // virtual void render(shared_ptr<Camera> camera, vector < shared_ptr<Actor>> actors, vector < shared_ptr<Light>> lights) override;
    virtual void render(shared_ptr<Camera> camera, const  physx::PxRenderBuffer& rb, const glm::vec3& color) override;
    virtual void render(shared_ptr<Camera> camera, vector < shared_ptr<MeshRenderer>>& renderers, vector<shared_ptr<Light>>& lights) override;


    virtual GLuint generateVertexArrays(const GLuint id, GLuint& vao) override;
    virtual GLuint generateBuffer(const GLuint id,GLuint& bo,GLenum type,int size,void *dataPointer, GLenum drawType) override;

    virtual GLuint createShader(GLenum shaderType) override;
    virtual void compileShader(GLuint shaderID, GLuint size,const char* dataPointer) override;


    virtual GLuint createShaderProgram() override;

    virtual void attachAndLinkShader(GLuint ProgramID,GLuint VertexShaderID,GLuint FragmentShaderID) override;
virtual void deleteShader(GLuint shaderID) override;
    virtual void deleteBuffer(GLuint size,GLuint &bo) override;

     virtual GLint getUniformLocation(GLuint programID,const char* name) override;

    virtual ~GLFWGraphicsSystem();
    
    public:
    GLFWGraphicsSystem();
};

#endif // GLFWGRAPHICSYSTEM_H
