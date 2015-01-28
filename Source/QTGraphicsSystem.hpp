//#ifndef QTGRAPHICSSYSTEM_H
//#define QTGRAPHICSSYSTEM_H
//
//#include "GraphicsSystem.hpp"
//#include <qobject.h>
//#include <qopengl.h>
//#include <qopenglcontext.h>
//#include <qopenglfunctions.h>
//#include <qwindow.h>
//#include <qopenglpaintdevice.h>
//
//
//class QOpenGLVertexArrayObject;
//
//class QTGraphicsSystem : public GraphicsSystem, public QWindow, protected QOpenGLFunctions
//{
//
//    virtual int init() override;
//    virtual void shutdown() override;
//    virtual void swap() override;
//    virtual void createDebugShader() override;
//    virtual void clear() override;
//
//    virtual void setGraphicsParent(QWindow *parent) override;
//
//    virtual GLint uniform(const GLuint shaderProgram, const GLchar* uniformName) override;
//
//    //virtual void render(shared_ptr<Camera> camera, vector < shared_ptr<Actor>> actors, vector < shared_ptr<Light>> lights) override;
//    virtual void render(shared_ptr<Camera> camera, const  physx::PxRenderBuffer& rb, const glm::vec3& color) override;
//    virtual void render(shared_ptr<Camera> camera, vector < shared_ptr<MeshRenderer>>& renderers, vector<shared_ptr<Light>>& lights) override;
//
//    virtual QOpenGLVertexArrayObject* generateVertexArrays(const GLuint id, GLuint& vao) override;
//    virtual GLuint generateBuffer(const GLuint size, GLuint& bo, GLenum type, int dataSize, void *dataPointer, GLenum drawType) override;
//
//
//    virtual GLuint createShader(GLenum shaderType) override;
//    virtual void compileShader(GLuint shaderID, GLuint size,const char* dataPointer) override;
//
//
//    virtual GLuint createShaderProgram() override;
//    virtual void attachAndLinkShader(GLuint ProgramID,GLuint VertexShaderID,GLuint FragmentShaderID) override;
//    virtual void deleteShader(GLuint shaderID) override;
//    virtual void deleteBuffer(GLuint size,GLuint &bo) override;
//
//
//    virtual GLint getUniformLocation(GLuint programID,const char* name) override;
//
//public:
//    QTGraphicsSystem();
//    virtual ~QTGraphicsSystem();
//
//    QOpenGLContext *m_context;
//    QOpenGLFunctions *m_funcs;
//    //QOpenGLPaintDevice *m_device;
//};
//
//#endif // QTGRAPHICSSYSTEM_H
