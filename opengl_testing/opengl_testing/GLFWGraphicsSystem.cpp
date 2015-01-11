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
#include "Camera.hpp"
#include "Light.hpp"
#include "Material.hpp"
#include "Shader.hpp"

int GLFWGraphicsSystem::init()
{
    if (!glfwInit()) {
		fprintf(stderr, "ERROR: could not start GLFW3\n");
		return 1;
	}
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 0);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
	//window = make_shared<GLFWwindow>(glfwCreateWindow(640, 480, "Hello Triangle", NULL, NULL), glfwDestroyWindow);
	//window = make_shared<GLFWwindow>(glfwCreateWindow(640, 480, "Hello Triangle", NULL, NULL),NULL);
	window.reset(glfwCreateWindow(640, 480, "Hello Triangle", NULL, NULL), glfwDestroyWindow);
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
	createDebugShader();
	return 0;

}
 void GLFWGraphicsSystem::shutdown()
{
    debugMaterial.reset();
	debugShader.reset();
	glfwTerminate();

}
 void GLFWGraphicsSystem::swap()
{
    glfwPollEvents();
    // put the stuff we've been drawing onto the display
    glfwSwapBuffers(window.get());

}

void GLFWGraphicsSystem::createDebugShader()
{
    //debugShader = make_shared<Shader>("../../../../../../data/vs.vs", "../../../../../../data/fs.fragmentshader");

    string vsDataPath = DATA_PATH;
    string fsDataPath = DATA_PATH;
    debugShader = make_shared<Shader>(vsDataPath.append("vs.vs").c_str(),fsDataPath.append("fs.fragmentshader").c_str());

    //debugShader = make_shared<Shader>("/Users/guilherme_cunha/Dev/GITHUB/GUInity/data/vsLight.vs", "/Users/guilherme_cunha/Dev/GITHUB/GUInity/data/fsLight.fragmentshader");

    debugMaterial = make_shared<Material>(debugShader);
}

void GLFWGraphicsSystem::clear()
{

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

 GLFWGraphicsSystem::~GLFWGraphicsSystem() {}

GLFWGraphicsSystem::GLFWGraphicsSystem() {}


GLint GLFWGraphicsSystem::uniform(const GLuint shaderProgram, const GLchar* uniformName) {
    if (!uniformName)
        throw std::runtime_error("uniformName was NULL");

    GLint uniform = glGetUniformLocation(shaderProgram, uniformName);
    if (uniform == -1)
        throw std::runtime_error(std::string("Program uniform not found: ") + uniformName);

    return uniform;
}

void GLFWGraphicsSystem::render(shared_ptr<Camera> camera, vector < shared_ptr<MeshRenderer>>& renderers, vector<shared_ptr<Light>>& lights)
//void GraphicsSystem::render(World& world)
{
    //shared_ptr<Camera> camera = world.cameras[0];

    camera->computeModelViewMatrix();

    for (int i = 0; i < renderers.size(); i++)
    {
        shared_ptr<MeshRenderer> meshRenderer = renderers[i];

        shared_ptr<Actor> actor = meshRenderer->getActor();

        shared_ptr<MeshFilter> meshFilter = meshRenderer->meshFilter.lock();
        if (!meshFilter)
            continue;

        GLuint shaderProgram = meshRenderer->material->getShaderProgram();


        glLinkProgram(shaderProgram);
        glUseProgram(shaderProgram);

        float ambientLight = 0.5f;
        glm::vec3 ambientLightColor(1.0, 0.0, 0.0);

        glUniform3fv(uniform(shaderProgram, "ambientLightColor"), 1, &ambientLightColor[0]);
        glUniform1f(uniform(shaderProgram, "ambientLightIntensity"), ambientLight);

        glUniformMatrix4fv(uniform(shaderProgram, "camera"), 1, GL_FALSE, &camera->MVPMatrix[0][0]);
        glUniformMatrix4fv(uniform(shaderProgram, "model"), 1, GL_FALSE, &actor->transform->getModelMatrix()[0][0]);
        for (int j = 0; j < lights.size(); j++)
        {
            shared_ptr<Light> light = lights[j];

            glUniform3fv(meshRenderer->material->shader->paramID["lightPos"], 1, &light->getActor()->transform->position[0]);
            glUniform3fv(meshRenderer->material->shader->paramID["lightIntensity"], 1, &light->color[0]);
        }

        glBindVertexArray(meshFilter->mesh->vao);

        glEnableVertexAttribArray(0);
        glBindBuffer(GL_ARRAY_BUFFER, meshFilter->mesh->mvbo);

        //Vertex
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(MeshVertex), (void*)(0));

        int beginNormal = sizeof(glm::vec3) + sizeof(glm::vec2);

        //Normal
        glEnableVertexAttribArray(2);
        glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, sizeof(MeshVertex), (void*)(beginNormal));

        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, meshFilter->mesh->ibo);

        // draw points 0-3 from the currently bound VAO with current in-use shader
        glDrawElements(GL_TRIANGLES, meshFilter->mesh->triangles.size(), GL_UNSIGNED_SHORT, NULL);

        glDisableVertexAttribArray(0);
        glDisableVertexAttribArray(2);

    }

}

void GLFWGraphicsSystem::render(shared_ptr<Camera> camera,const physx::PxRenderBuffer& rb,const glm::vec3& color)
{
    float *points = new float[rb.getNbLines() * 6];

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

    glUniform3fv(debugMaterial->shader->paramID["difuse"], 1, &color[0]);

    glm::mat4 transformMatrix = camera->MVPMatrix;// *actor->transform->getModelMatrix();

    glUniformMatrix4fv(debugMaterial->shader->paramID["MVP"], 1, GL_FALSE, &transformMatrix[0][0]);

    glDrawArrays(GL_LINES, 0, 2 * rb.getNbLines());

    glBindVertexArray(0); // Unbind our Vertex Array Object

    glDeleteBuffers(1, &vbo);
    glDeleteVertexArrays(1, &vao);

    delete []points;
}


GLuint GLFWGraphicsSystem::generateVertexArrays(const GLuint id, GLuint& vao)
{
    glGenVertexArrays(id, &vao);
    glBindVertexArray(vao);
}

GLuint GLFWGraphicsSystem::generateBuffer(const GLuint size, GLuint& bo, GLenum type, int dataSize, void *dataPointer, GLenum drawType)
{
    glGenBuffers(size, &bo);
    glBindBuffer(type, bo);
    glBufferData(type, dataSize, dataPointer, drawType);

}

GLuint GLFWGraphicsSystem::createShader(GLenum shaderType)
{

    return glCreateShader(shaderType);
}


void GLFWGraphicsSystem::compileShader(GLuint shaderID, GLuint size,const char* dataPointer)
{
    glShaderSource(shaderID, size, &dataPointer, NULL);
    glCompileShader(shaderID);
}


GLuint GLFWGraphicsSystem::createShaderProgram()
{
    return glCreateProgram();
}

void GLFWGraphicsSystem::attachAndLinkShader(GLuint ProgramID,GLuint VertexShaderID,GLuint FragmentShaderID)
{
    glAttachShader(ProgramID, VertexShaderID);
    glAttachShader(ProgramID, FragmentShaderID);
    glLinkProgram(ProgramID);
}

void GLFWGraphicsSystem::deleteShader(GLuint shaderID)
{
glDeleteShader(shaderID);
}

void GLFWGraphicsSystem::deleteBuffer(GLuint size,GLuint &bo)
{
    glDeleteBuffers(size,&bo);
}

GLint GLFWGraphicsSystem::getUniformLocation(GLuint programID,const char* name)
{
   return glGetUniformLocation(programID,name);
}

//void GLFWGraphicsSystem::render(shared_ptr<Camera> camera, const Ray& r, const glm::vec3& color)
//{
//    float points[6];

//    // render the line

//    points[0] = r.origin.x;
//    points[1] = r.origin.y;
//    points[2] = r.origin.z;
//    points[3] = r.origin.x+r.direction.x*10;
//    points[4] = r.origin.y+r.direction.y*10;
//    points[5] = r.origin.z+r.direction.z*10;

//    GLuint vbo = 0;
//    glGenBuffers(1, &vbo);
//    glBindBuffer(GL_ARRAY_BUFFER, vbo);
//    glBufferData(GL_ARRAY_BUFFER, 6  * sizeof(float), points, GL_STATIC_DRAW);

//    GLuint vao = 0;
//    glGenVertexArrays(1, &vao);
//    glBindVertexArray(vao);
//    glEnableVertexAttribArray(0);
//    glBindBuffer(GL_ARRAY_BUFFER, vbo);
//    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, NULL);


//    glLinkProgram(debugMaterial->getShaderProgram());
//    glUseProgram(debugMaterial->getShaderProgram());

//    glBindVertexArray(vao);

//    //glm::mat4 transformMatrix = camera->MVPMatrix;
//    glUniform3fv(debugMaterial->shader->paramID["difuse"], 1, &color[0]);
//    glm::mat4 transformMatrix(1.0f);
//    glUniformMatrix4fv(debugMaterial->shader->paramID["MVP"], 1, GL_FALSE, &transformMatrix[0][0]);

//    glDrawArrays(GL_LINES, 0, 2);



//}

