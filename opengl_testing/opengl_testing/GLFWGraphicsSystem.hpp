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
    
 //   virtual void setGraphicsParent(QWindow *parent) override {};

    virtual GLint uniform(const GLuint shaderProgram, const GLchar* uniformName) override;

   // virtual void render(shared_ptr<Camera> camera, vector < shared_ptr<Actor>> actors, vector < shared_ptr<Light>> lights) override;
    virtual void render(shared_ptr<Camera> camera, const  physx::PxRenderBuffer& rb, const glm::vec4& color) override;
    virtual void render(shared_ptr<Camera> camera, vector < shared_ptr<MeshRenderer>>& renderers, vector<shared_ptr<Light>>& lights) override;


    virtual void generateVertexArrays(const GLuint id, GLuint& vao) override;
    virtual void generateBuffer(const GLuint id,GLuint& bo,GLenum type,int size,void *dataPointer, GLenum drawType) override;

    virtual GLuint createShader(GLenum shaderType) override;
    virtual void compileShader(GLuint shaderID, GLuint size,const char* dataPointer) override;
    
    //virtual void renderGUI(MeshVertex* meshVertex, int nVertex);
    //virtual void renderGUI(shared_ptr<UIWidget> uiWidget, int nWidgets) override;
    virtual void renderGUI(vector<shared_ptr<UIWidget>> uiWidgetVector)override;

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
