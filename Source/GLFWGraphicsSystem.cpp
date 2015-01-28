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
#include "UIWidget.hpp"
#include "AssetDatabase.hpp"
#include "Texture.hpp"

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
	
    glEnable(GL_CULL_FACE);
    glFrontFace(GL_CCW);
    
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
    debugShader = make_shared<Shader>(CommonData("vs.vs").c_str(),CommonData("fs.fragmentshader").c_str());
    debugMaterial = make_shared<Material>(debugShader);

    guiShader = make_shared<Shader>(CommonData("vsOrtho.vs").c_str(),CommonData("fsOrtho.fragmentshader").c_str());
    guiMaterial = make_shared<Material>(guiShader);


    GUIMatrix = glm::ortho(0.0f, 640.0f, 480.0f, 0.0f, -5.0f, 5.0f);
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

//void GLFWGraphicsSystem::renderGUI(MeshVertex* meshVertex, int nVertex)
//void GLFWGraphicsSystem::renderGUI(shared_ptr<UIWidget> uiWidget, int nWidgets)
void GLFWGraphicsSystem::renderGUI(vector<shared_ptr<UIWidget>> uiWidgetVector)
{
//    
//    GLuint shaderProgram = guiMaterial->getShaderProgram();
//    
//    glLinkProgram(shaderProgram);
//    glUseProgram(shaderProgram);
//    
//    // Get a handle for our "myTextureSampler" uniform
//    GLuint TextureID  = glGetUniformLocation(shaderProgram, "myTextureSampler");
//    shared_ptr<Texture> texture = dynamic_pointer_cast<Texture>(AssetDatabase::idToAsset[1]);
//    
////    glEnable(GL_BLEND);
////    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
//    
//    for (int i = 0; i < uiWidgetVector.size(); i++)
//    {
//        shared_ptr<UIWidget> uiWidget = uiWidgetVector[i];
//        
//        glUniformMatrix4fv(uniform(shaderProgram, "model"), 1, GL_FALSE, &uiWidget->getModelMatrix()[0][0]);
//    glUniformMatrix4fv(uniform(shaderProgram, "ortho"), 1, GL_FALSE, &GUIMatrix[0][0]);
//    glUniform4fv(uniform(shaderProgram, "diffuseColor"), 1, &uiWidget->color[0]);
//    
//    glBindVertexArray(uiWidget->mesh->vao);
//    
//    glEnableVertexAttribArray(0);
//    glBindBuffer(GL_ARRAY_BUFFER, uiWidget->mesh->mvbo);
//    
//        // Bind our texture in Texture Unit 0
//        glActiveTexture(GL_TEXTURE0);
//        glBindTexture(GL_TEXTURE_2D, texture->textureID);
//        // Set our "myTextureSampler" sampler to user Texture Unit 0
//        glUniform1i(TextureID, 0);
//        
//    //Vertex
//    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(MeshVertex), (void*)(0));
//        
//        int beginUV = sizeof(glm::vec3);
//        
//        //UV
//        glEnableVertexAttribArray(3);
//        glVertexAttribPointer(3, 2, GL_FLOAT, GL_FALSE, sizeof(MeshVertex), (void*)(beginUV));
//        
//    
//    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, uiWidget->mesh->ibo);
//    
//    // draw points 0-3 from the currently bound VAO with current in-use shader
//    glDrawElements(GL_TRIANGLES, uiWidget->mesh->triangles.size(), GL_UNSIGNED_SHORT, NULL);
//    
//    glDisableVertexAttribArray(0);
//    glDisableVertexAttribArray(3);
//    }
}

void GLFWGraphicsSystem::render(shared_ptr<Camera> camera, vector < shared_ptr<MeshRenderer>>& renderers, vector<shared_ptr<Light>>& lights)
//void GraphicsSystem::render(World& world)
{
    //shared_ptr<Camera> camera = world.cameras[0];

    camera->computeModelViewMatrix();

        //glEnable(GL_BLEND);
        //glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    
    for (int i = 0; i < renderers.size(); i++)
    {
        shared_ptr<MeshRenderer> meshRenderer = renderers[i];

        shared_ptr<Actor> actor = meshRenderer->getActor();

        /*shared_ptr<MeshFilter> meshFilter = meshRenderer->meshFilter.lock();
        if (!meshFilter)
            continue;
*/

		shared_ptr<MeshComponent> meshComponent = meshRenderer->meshComponent.lock();
		if (!meshComponent)
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

            /*glUniform3fv(meshRenderer->material->shader->paramID["lightPos"], 1, &light->getActor()->transform->position[0]);
            glUniform3fv(meshRenderer->material->shader->paramID["lightIntensity"], 1, &light->color[0]);*/

			glUniform3fv(uniform(shaderProgram, "lightPos"), 1, &light->getActor()->transform->position[0]);
			glUniform3fv(uniform(shaderProgram, "lightIntensity"), 1, &light->color[0]);
        }

		shared_ptr<Texture> texture = meshRenderer->material->getTextureParam();
		if (texture)
		{
			//glEnable(GL_TEXTURE);
			glActiveTexture(GL_TEXTURE0);
			glBindTexture(GL_TEXTURE_2D, texture->textureID);
			glUniform1i(uniform(shaderProgram, "myTextureSampler"), 0);
			//glBindTexture(GL_TEXTURE_2D, Texture);
			//glUniform1i(texture->textureID, 0);

			//glactivete

			/*glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, texture->width, texture->height, 0, GL_RGBA, GL_UNSIGNED_BYTE, (GLvoid*)texture->data);

			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);*/
		}
		else
		{
			//glDisable(GL_TEXTURE);
			//glActiveTexture(GL_TEXTURE0);
			//glUniform1i(texture->textureID, 0);
			//glDisable(GL_TEXTURE0);

		}

        
		glBindVertexArray(meshComponent->mesh->vao);

        glEnableVertexAttribArray(0);
		glBindBuffer(GL_ARRAY_BUFFER, meshComponent->mesh->mvbo);

        //Vertex
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(MeshVertex), (void*)(0));

        int beginNormal = sizeof(glm::vec3) + sizeof(glm::vec2);

        //Normal
        glEnableVertexAttribArray(2);
        glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, sizeof(MeshVertex), (void*)(beginNormal));

        int beginUV = sizeof(glm::vec3);
        
        //UV
        glEnableVertexAttribArray(3);
        glVertexAttribPointer(3, 2, GL_FLOAT, GL_FALSE, sizeof(MeshVertex), (void*)(beginUV));
        
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, meshComponent->mesh->ibo);

        // draw points 0-3 from the currently bound VAO with current in-use shader
		glDrawElements(GL_TRIANGLES, meshComponent->mesh->triangles.size(), GL_UNSIGNED_SHORT, NULL);

        glDisableVertexAttribArray(0);
        glDisableVertexAttribArray(2);
        glDisableVertexAttribArray(3);


    }

}

void GLFWGraphicsSystem::render(shared_ptr<Camera> camera,const physx::PxRenderBuffer& rb,const glm::vec4& color)
{
    float *points = new float[rb.getNbLines() * 6];

    //glDisable(GL_BLEND);
    
    
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

	
    /*glUniform3fv(debugMaterial->shader->paramID["difuse"], 1, &color[0]);*/
	glUniform3fv(getUniformLocation(debugMaterial->getShaderProgram(), "difuse") , 1, &color[0]);

    glm::mat4 transformMatrix = camera->MVPMatrix;// *actor->transform->getModelMatrix();

	glUniformMatrix4fv(getUniformLocation(debugMaterial->getShaderProgram(), "MVP"), 1, GL_FALSE, &transformMatrix[0][0]);
    //glUniformMatrix4fv(debugMaterial->shader->paramID["MVP"], 1, GL_FALSE, &transformMatrix[0][0]);

    glDrawArrays(GL_LINES, 0, 2 * rb.getNbLines());

    glBindVertexArray(0); // Unbind our Vertex Array Object

    glDisableVertexAttribArray(0);
    
    glDeleteBuffers(1, &vbo);
    glDeleteVertexArrays(1, &vao);

    delete []points;
}


void GLFWGraphicsSystem::generateVertexArrays(const GLuint id, GLuint& vao)
{
    glGenVertexArrays(id, &vao);
    glBindVertexArray(vao);

}

void GLFWGraphicsSystem::generateBuffer(const GLuint size, GLuint& bo, GLenum type, int dataSize, void *dataPointer, GLenum drawType)
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

