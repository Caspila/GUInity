//#include <qdebug.h>
//#include "QTGraphicsSystem.hpp"
//#include "GraphicsSystem.hpp"
//#include "Mesh.hpp"
//#include "MeshRenderer.hpp"
//#include "MeshFilter.hpp"
//#include "Actor.hpp"
//#include "Camera.hpp"
//#include "Light.hpp"
//#include "Material.hpp"
//#include "Shader.hpp"
//#include <qopenglvertexarrayobject.h>
//#include <qopenglbuffer.h>
//#include <QOpenGLShader>
//#include <QThread>
//#include <qwidget.h>
//
//QTGraphicsSystem::QTGraphicsSystem()
//{
//
//}
//
//QTGraphicsSystem::~QTGraphicsSystem()
//{
//
//}
//
//void QTGraphicsSystem::setGraphicsParent(QWindow *parent)
//{
//   setParent(parent);
//}
//
//int QTGraphicsSystem::init()
//{
//
//    setSurfaceType(OpenGLSurface);
//
//    QSurfaceFormat fmt;
//    fmt.setMajorVersion(4);
//    fmt.setMinorVersion(2);
//    fmt.setProfile(QSurfaceFormat::CoreProfile); //whatever this is
//
//    this->setBaseSize(QSize(640,480));
//    this->setFormat(fmt);
//    create();
//
//
//    m_context = new QOpenGLContext(0);
//    m_context->setFormat(fmt);
//    m_context->create();
//
//    m_context->makeCurrent(this);
//    initializeOpenGLFunctions();
//
//    //initializeOpenGLFunctions();
//    //m_context->makeCurrent(this);
//
//     //m_funcs = m_context->functions();
//     //initializ
//
//  //  m_device = new QOpenGLPaintDevice;
//    // m_device->setSize(size());
//    //initializeOpenGLFunctions();
//    //initialize();
//
//     if(!m_context->isValid())
//       qCritical()<<"The OpenGL context is invalid!"; //I allways get this message
//
//      //now another test:
//      //the next line prints: "Window format version is: 4.2" which is correct
//      qDebug()<<"Window format version is: "<<this->format().majorVersion()<<"."<<this->format().minorVersion();
//      //the next line prints: "Context format version is: 2.0" Which is ofcourse not correct! WTF?
//      qDebug()<<"Context format version is: "<<m_context->format().majorVersion()<<"."<<m_context->format().minorVersion();
//
//
//
//    show();
//
//
//
//    return 0;
//
//}
// void QTGraphicsSystem::shutdown()
//{
//    debugMaterial.reset();
//    debugShader.reset();
//}
// void QTGraphicsSystem::swap()
//{
//     m_context->swapBuffers(this);
//     //m_context->functions()->glswa
//}
//
//void QTGraphicsSystem::createDebugShader()
//{
//    //debugShader = make_shared<Shader>("../../../../../../data/vs.vs", "../../../../../../data/fs.fragmentshader");
//
//    string vsDataPath = DATA_PATH;
//    string fsDataPath = DATA_PATH;
//    debugShader = make_shared<Shader>(vsDataPath.append("vs.vs").c_str(),fsDataPath.append("fs.fragmentshader").c_str());
//
//    //debugShader = make_shared<Shader>("/Users/guilherme_cunha/Dev/GITHUB/GUInity/data/vsLight.vs", "/Users/guilherme_cunha/Dev/GITHUB/GUInity/data/fsLight.fragmentshader");
//
//    debugMaterial = make_shared<Material>(debugShader);
//}
//
//void QTGraphicsSystem::clear()
//{
//
//    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
//}
//
//
//
//GLint QTGraphicsSystem::uniform(const GLuint shaderProgram, const GLchar* uniformName) {
//    if (!uniformName)
//        throw std::runtime_error("uniformName was NULL");
//
//    GLint uniform = m_context->functions()->glGetUniformLocation(shaderProgram, uniformName);
//    if (uniform == -1)
//        throw std::runtime_error(std::string("Program uniform not found: ") + uniformName);
//
//    return uniform;
//}
//
//void QTGraphicsSystem::render(shared_ptr<Camera> camera, vector < shared_ptr<MeshRenderer>>& renderers, vector<shared_ptr<Light>>& lights)
////void GraphicsSystem::render(World& world)
//{
//    //shared_ptr<Camera> camera = world.cameras[0];
//
//    camera->computeModelViewMatrix();
//
//    for (int i = 0; i < renderers.size(); i++)
//    {
//        shared_ptr<MeshRenderer> meshRenderer = renderers[i];
//
//        shared_ptr<Actor> actor = meshRenderer->getActor();
//
//        shared_ptr<MeshFilter> meshFilter = meshRenderer->meshFilter.lock();
//        if (!meshFilter)
//            continue;
//
//        GLuint shaderProgram = meshRenderer->material->getShaderProgram();
//
//
//        m_context->functions()->glLinkProgram(shaderProgram);
//        m_context->functions()->glUseProgram(shaderProgram);
//
//        float ambientLight = 0.5f;
//        glm::vec3 ambientLightColor(1.0, 0.0, 0.0);
//
//        glUniform3fv(uniform(shaderProgram, "ambientLightColor"), 1, &ambientLightColor[0]);
//        glUniform1f(uniform(shaderProgram, "ambientLightIntensity"), ambientLight);
//
//        glUniformMatrix4fv(uniform(shaderProgram, "camera"), 1, GL_FALSE, &camera->MVPMatrix[0][0]);
//        glUniformMatrix4fv(uniform(shaderProgram, "model"), 1, GL_FALSE, &actor->transform->getModelMatrix()[0][0]);
//        for (int j = 0; j < lights.size(); j++)
//        {
//            shared_ptr<Light> light = lights[j];
//
//            glUniform3fv(meshRenderer->material->shader->paramID["lightPos"], 1, &light->getActor()->transform->position[0]);
//            glUniform3fv(meshRenderer->material->shader->paramID["lightIntensity"], 1, &light->color[0]);
//        }
//
//        //glBindVertexArray(meshFilter->mesh->vao);
//        meshFilter->mesh->QTvao->bind();
//
//
//        glEnableVertexAttribArray(0);
//        glBindBuffer(GL_ARRAY_BUFFER, meshFilter->mesh->mvbo);
//
//        //Vertex
//        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(MeshVertex), (void*)(0));
//
//        int beginNormal = sizeof(glm::vec3) + sizeof(glm::vec2);
//
//        //Normal
//        glEnableVertexAttribArray(2);
//        glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, sizeof(MeshVertex), (void*)(beginNormal));
//
//        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, meshFilter->mesh->ibo);
//
//        // draw points 0-3 from the currently bound VAO with current in-use shader
//        glDrawElements(GL_TRIANGLES, meshFilter->mesh->triangles.size(), GL_UNSIGNED_SHORT, NULL);
//
//        glDisableVertexAttribArray(0);
//        glDisableVertexAttribArray(2);
//
//    }
//
//}
//
//
//void QTGraphicsSystem::render(shared_ptr<Camera> camera,const physx::PxRenderBuffer& rb,const glm::vec3& color)
//{
////    float *points = new float[rb.getNbLines() * 6];
//
////    for (PxU32 i = 0; i < rb.getNbLines(); i++)
////    {
//
////        const PxDebugLine& line = rb.getLines()[i];
////        // render the line
//
////        points[i * 6] = line.pos0.x;
////        points[i * 6+1] = line.pos0.y;
////        points[i * 6+2] = line.pos0.z;
////        points[i * 6+3] = line.pos1.x;
////        points[i * 6+4] = line.pos1.y;
////        points[i * 6+5] = line.pos1.z;
//
//
////    }
//
////    GLuint vbo = 0;
////    glGenBuffers(1, &vbo);
////    glBindBuffer(GL_ARRAY_BUFFER, vbo);
////    glBufferData(GL_ARRAY_BUFFER, 6 * rb.getNbLines() * sizeof(float), points, GL_STATIC_DRAW);
//
////    GLuint vao = 0;
////    glGenVertexArrays(1, &vao);
////    glBindVertexArray(vao);
////    glEnableVertexAttribArray(0);
////    glBindBuffer(GL_ARRAY_BUFFER, vbo);
////    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, NULL);
//
//
////    glLinkProgram(debugMaterial->getShaderProgram());
////    glUseProgram(debugMaterial->getShaderProgram());
//
////    glBindVertexArray(vao);
//
////    glUniform3fv(debugMaterial->shader->paramID["difuse"], 1, &color[0]);
//
////    glm::mat4 transformMatrix = camera->MVPMatrix;// *actor->transform->getModelMatrix();
//
////    glUniformMatrix4fv(debugMaterial->shader->paramID["MVP"], 1, GL_FALSE, &transformMatrix[0][0]);
//
////    glDrawArrays(GL_LINES, 0, 2 * rb.getNbLines());
//
////    glBindVertexArray(0); // Unbind our Vertex Array Object
//
////    glDeleteBuffers(1, &vbo);
////    glDeleteVertexArrays(1, &vao);
//
////    delete []points;
//}
//
//
//GLint QTGraphicsSystem::getUniformLocation(GLuint programID,const char* name)
//{
//   return m_context->functions()->glGetUniformLocation(programID,name);
//}
//
////void QTGraphicsSystemQTGraphicsSystem::render(shared_ptr<Camera> camera, const Ray& r, const glm::vec3& color)
////{
////    float points[6];
//
////    // render the line
//
////    points[0] = r.origin.x;
////    points[1] = r.origin.y;
////    points[2] = r.origin.z;
////    points[3] = r.origin.x+r.direction.x*10;
////    points[4] = r.origin.y+r.direction.y*10;
////    points[5] = r.origin.z+r.direction.z*10;
//
////    GLuint vbo = 0;
////    glGenBuffers(1, &vbo);
////    glBindBuffer(GL_ARRAY_BUFFER, vbo);
////    glBufferData(GL_ARRAY_BUFFER, 6  * sizeof(float), points, GL_STATIC_DRAW);
//
////    GLuint vao = 0;
////    glGenVertexArrays(1, &vao);
////    glBindVertexArray(vao);
////    glEnableVertexAttribArray(0);
////    glBindBuffer(GL_ARRAY_BUFFER, vbo);
////    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, NULL);
//
//
////    glLinkProgram(debugMaterial->getShaderProgram());
////    glUseProgram(debugMaterial->getShaderProgram());
//
////    glBindVertexArray(vao);
//
////    //glm::mat4 transformMatrix = camera->MVPMatrix;
////    glUniform3fv(debugMaterial->shader->paramID["difuse"], 1, &color[0]);
////    glm::mat4 transformMatrix(1.0f);
////    glUniformMatrix4fv(debugMaterial->shader->paramID["MVP"], 1, GL_FALSE, &transformMatrix[0][0]);
//
////    glDrawArrays(GL_LINES, 0, 2);
//
//
//
////}
//
//QOpenGLVertexArrayObject* QTGraphicsSystem::generateVertexArrays(const GLuint id, GLuint& vao)
//{
//    //QOpenGLVertexArrayObject
//      // glGenVertexArrays(id, &vao);
//      // glBindVertexArray(vao);
//
//
//    QOpenGLVertexArrayObject* m_vao1 = new QOpenGLVertexArrayObject( this );
//    m_vao1->create();
//    m_vao1->bind();
//    vao = m_vao1->objectId();
//
//    return m_vao1;
////    m_context->functions()->glGenVertexArrays(id, &vao);
////    m_context->functions()->glBindVertexArray(vao);
//
//}
//
//
//GLuint QTGraphicsSystem::generateBuffer(const GLuint size, GLuint& bo, GLenum type, int dataSize, void *dataPointer, GLenum drawType)
//{
//    //  glBindBuffer(GL_ARRAY_BUFFER, mvbo);
//    //	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo);
//
////    QOpenGLBuffer::Type qtType;
////    switch(type)
////    {
////    case GL_ARRAY_BUFFER:
////        qtType = QOpenGLBuffer::Type::VertexBuffer;
////        break;
////    case GL_ELEMENT_ARRAY_BUFFER:
////        qtType = QOpenGLBuffer::Type::IndexBuffer;
////        break;
////    }
//
////    QOpenGLBuffer* buffer = new QOpenGLBuffer(qtType);
////    buffer->bind();
////    buffer->allocate(dataPointer,dataSize);
//
//
//    m_context->functions()->glGenBuffers(size, &bo);
//    m_context->functions()->glBindBuffer(type, bo);
//    m_context->functions()->glBufferData(type, dataSize, dataPointer, drawType);
//}
//
//GLuint QTGraphicsSystem::createShader(GLenum shaderType)
//{
////    QOpenGLShader::ShaderType shaderTypeQt;
////    switch(shaderType)
////    {
////    case GL_VERTEX_SHADER:
////        shaderTypeQt = QOpenGLShader::Vertex;
////        break;
////    case GL_FRAGMENT_SHADER:
////        shaderTypeQt = QOpenGLShader::Fragment;
////        break;
////    }
//
////    QOpenGLShader* shader = new QOpenGLShader(shaderTypeQt);
//
////    return shader->shaderId();
//
//
//    return m_context->functions()->glCreateShader(shaderType);
//
//}
//
//void QTGraphicsSystem::compileShader(GLuint shaderID, GLuint size,const char* dataPointer)
//{
//
//    m_context->functions()->glShaderSource(shaderID, size, &dataPointer, NULL);
//    m_context->functions()->glCompileShader(shaderID);
//
//    GLint Result = GL_FALSE;
//    int InfoLogLength;
//
//    m_context->functions()->glGetShaderiv(shaderID, GL_COMPILE_STATUS, &Result);
//    m_context->functions()->glGetShaderiv(shaderID, GL_INFO_LOG_LENGTH, &InfoLogLength);
//    std::vector<char> VertexShaderErrorMessage(InfoLogLength);
//    m_context->functions()->glGetShaderInfoLog(shaderID, InfoLogLength, NULL, &VertexShaderErrorMessage[0]);
//    fprintf(stdout, "%s\n", &VertexShaderErrorMessage[0]);
//}
//
//
//GLuint QTGraphicsSystem::createShaderProgram()
//{
//    return m_context->functions()->glCreateProgram();
//}
//
//void QTGraphicsSystem::attachAndLinkShader(GLuint ProgramID,GLuint VertexShaderID,GLuint FragmentShaderID)
//{
//    m_context->functions()->glAttachShader(ProgramID, VertexShaderID);
//    m_context->functions()->glAttachShader(ProgramID, FragmentShaderID);
//    m_context->functions()->glLinkProgram(ProgramID);
//}
//
//void QTGraphicsSystem::deleteShader(GLuint shaderID)
//{
//m_context->functions()->glDeleteShader(shaderID);
//}
//
//void QTGraphicsSystem::deleteBuffer(GLuint size,GLuint &bo)
//{
//    m_context->functions()->glDeleteBuffers(size,&bo);
//}
