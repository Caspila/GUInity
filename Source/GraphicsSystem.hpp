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

class GraphicsSystem
//#ifdef GUINITY_DEBUG
//	:public StaticCounter<GraphicsSystem>
//#endif
{

public:
//	static GraphicsSystem& getInstance()
//	{
//		static GraphicsSystem instance; // Guaranteed to be destroyed.
//		// Instantiated on first use.
//		return instance;
//	}

    static GraphicsSystem* getInstance();
//    {
//        static GraphicsSystem* instance; // Guaranteed to be destroyed.
//        if(instance == nullptr)
//            instance = new GLFWGraphicsSystem();
//        // Instantiated on first use.
//        return instance;
//    }

public:
	GraphicsSystem() {};                   // Constructor? (the {} brackets) are needed here.
	// Dont forget to declare these two. You want to make sure they
	// are unaccessable otherwise you may accidently get copies of
	// your singleton appearing.
	GraphicsSystem(GraphicsSystem const&);              // Don't Implement
	void operator=(GraphicsSystem const&); // Don't implement
public:
	//GraphicsSystem();
	virtual ~GraphicsSystem();

    virtual int init() = 0;
    virtual void shutdown() = 0;
    virtual void swap() = 0;
    virtual void clear() = 0;
//    virtual void setGraphicsParent(QWindow *parent) = 0;

	shared_ptr<GLFWwindow> window;

    virtual GLint uniform(const GLuint shaderProgram, const GLchar* uniformName) = 0;

    virtual void createDebugShader()= 0;

    //virtual void render(shared_ptr<Camera> camera, vector < shared_ptr<Actor>> actors, vector < shared_ptr<Light>> lights)=0;
    virtual void render(shared_ptr<Camera> camera, const  physx::PxRenderBuffer& rb, const glm::vec4& color)=0;
    virtual void render(shared_ptr<Camera> camera, vector < shared_ptr<MeshRenderer>>& renderers, vector<shared_ptr<Light>>& lights)=0;

    virtual void generateVertexArrays(const GLuint size, GLuint& vao) = 0;

    virtual void generateBuffer(const GLuint size, GLuint& bo, GLenum type, int dataSize, void *dataPointer, GLenum drawType) =0;
    //GraphicsSystem::getInstance()->generateBuffer(1,mvbo,GL_ARRAY_BUFFER,meshVertices.size() * sizeof(MeshVertex),&meshVertices[0],GL_STATIC_DRAW);

    virtual GLuint createShader(GLenum shaderType) = 0;
    virtual void compileShader(GLuint shaderID, GLuint size,const char* dataPointer) = 0;// VertexShaderID,1,&VertexSourcePointer,NULL);

    virtual GLuint createShaderProgram() = 0;
    virtual void attachAndLinkShader(GLuint ProgramID,GLuint VertexShaderID,GLuint FragmentShaderID) = 0;
    virtual void deleteShader(GLuint shaderID) = 0;

    virtual void deleteBuffer(GLuint size,GLuint &bo) = 0;

    virtual GLint getUniformLocation(GLuint programID,const char* name) = 0;

    //virtual void renderGUI(MeshVertex* meshVertex, int nVertex) = 0;
    //virtual void renderGUI(shared_ptr<UIWidget> uiWidget, int nWidgets) = 0;
        virtual void renderGUI(vector<shared_ptr<UIWidget>> uiWidgetVector) = 0;
    
	shared_ptr<Shader> debugShader;
	shared_ptr<Material> debugMaterial;

    shared_ptr<Shader> guiShader;
	shared_ptr<Material> guiMaterial;
    
    glm::mat4 GUIMatrix;

    
	//vector<weak_ptr<MeshRenderer>> allMeshRenderer;
    
};

