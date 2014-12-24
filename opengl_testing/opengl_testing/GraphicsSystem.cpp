#include "GraphicsSystem.hpp"
#include "Mesh.hpp"
#include "MeshRenderer.hpp"
#include "Actor.hpp"
#include "Camera.hpp"
#include "Light.hpp"
#include "Material.hpp"
#include "Shader.hpp"


GraphicsSystem::GraphicsSystem()
{
#ifdef GUINITY_DEBUG
	nCount++;
#endif
}


GraphicsSystem::~GraphicsSystem()
{
#ifdef GUINITY_DEBUG
	nCount--;
	cout << "Destroying GraphicsSystem" << endl;
#endif
}

void GraphicsSystem::shutdown()
{
	glfwTerminate();
}

int GraphicsSystem::init()
{
	if (!glfwInit()) {
		fprintf(stderr, "ERROR: could not start GLFW3\n");
		return 1;
	}

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

void GraphicsSystem::createDebugShader()
{
	debugShader = make_shared<Shader>("vs.vs", "fs.fragmentshader");

	debugMaterial = make_shared<Material>(debugShader);
}

GLint uniform(const GLuint shaderProgram, const GLchar* uniformName) {
	if (!uniformName)
		throw std::runtime_error("uniformName was NULL");

	GLint uniform = glGetUniformLocation(shaderProgram, uniformName);
	if (uniform == -1)
		throw std::runtime_error(std::string("Program uniform not found: ") + uniformName);

	return uniform;
}

void GraphicsSystem::render(shared_ptr<Camera> camera, vector < shared_ptr<Actor>> actors, vector < shared_ptr<Light>> lights)
{
	camera->computeModelViewMatrix();


	for (int i = 0; i < actors.size(); i++)
	{
		shared_ptr<Actor> actor = actors[i];

		GLuint shaderProgram = actor->meshRenderer->material->getShaderProgram();

		glLinkProgram(shaderProgram);
		glUseProgram (shaderProgram);



		//for each (pair<string, Holder> var in actor->meshRenderer->material->params)
		//{
		//	if (var.second.isVec3())
		//		glUniform3fv(actor->meshRenderer->material->shader->paramID[var.first], 1, &var.second.operator glm::vec3()[0]);
		//
		//}
		
		//glm::mat4 transformMatrix = camera->MVPMatrix * actor->transform->getModelMatrix();

		//map<string, GLuint> watch = actor->meshRenderer->material->shader->paramID;

		float ambientLight = 0.5f;
		glm::vec3 ambientLightColor(1.0, 0.0, 0.0);

		//glUniform3fv(actor->meshRenderer->material->shader->paramID["ambientLightColor"], 1, &ambientLightColor[0]);
		glUniform3fv(uniform(shaderProgram,"ambientLightColor"), 1, &ambientLightColor[0]);
		glUniform1f(uniform(shaderProgram, "ambientLightIntensity"), ambientLight);
		//glUniform3fv(actor->meshRenderer->material->shader->paramID["ambientLightColor"], 1, &ambientLightColor[0]);
		//glUniform1f(actor->meshRenderer->material->shader->paramID["ambientLightIntensity"], ambientLight);
		
		glUniformMatrix4fv(uniform(shaderProgram, "camera") , 1, GL_FALSE, &camera->MVPMatrix[0][0]);
		glUniformMatrix4fv(uniform(shaderProgram, "model"), 1, GL_FALSE, &actor->transform->getModelMatrix()[0][0]);
		//glUniformMatrix4fv(actor->meshRenderer->material->shader->paramID["model2"], 1, GL_FALSE, &actor->transform->getModelMatrix()[0][0]);

		
		//glUniformMatrix4fv(actor->meshRenderer->material->shader->paramID["camera"], 1, GL_FALSE, &camera->MVPMatrix[0][0]);
		//glUniformMatrix4fv(actor->meshRenderer->material->shader->paramID["model"], 1, GL_FALSE, &actor->transform->getModelMatrix()[0][0]);
		//glUniformMatrix4fv(actor->meshRenderer->material->shader->paramID["model2"], 1, GL_FALSE, &actor->transform->getModelMatrix()[0][0]);

		//glUniformMatrix4fv(actor->meshRenderer->material->shader->paramID["MVP"], 1, GL_FALSE, &transformMatrix[0][0]);
		//glUniformMatrix4fv(actor->meshRenderer->material->shader->paramID["M"], 1, GL_FALSE, &actor->transform->getModelMatrix()[0][0]);
		//glUniformMatrix4fv(actor->meshRenderer->material->shader->paramID["V"], 1, GL_FALSE, &camera->view[0][0]);

		for (int j = 0; j < lights.size(); j++)
		{
			shared_ptr<Light> light = lights[j];

			glUniform3fv(actor->meshRenderer->material->shader->paramID["lightPos"], 1, &light->transform.position[0]);
			glUniform3fv(actor->meshRenderer->material->shader->paramID["lightIntensity"], 1, &light->color[0]);
		}

		glBindVertexArray(actor->meshRenderer->mesh->vao);
		
		// draw points 0-3 from the currently bound VAO with current in-use shader
		glDrawArrays(GL_TRIANGLES, 0, actor->meshRenderer->mesh->nPoints);
	}

}

void GraphicsSystem::render(shared_ptr<Camera> camera,const physx::PxRenderBuffer& rb,const glm::vec3& color)
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

	delete points;
}

void GraphicsSystem::render(shared_ptr<Camera> camera, const Ray& r, const glm::vec3& color)
{
	float points[6];

	// render the line

	points[0] = r.origin.x;
	points[1] = r.origin.y;
	points[2] = r.origin.z;
	points[3] = r.origin.x+r.direction.x*10;
	points[4] = r.origin.y+r.direction.y*10;
	points[5] = r.origin.z+r.direction.z*10;

	GLuint vbo = 0;
	glGenBuffers(1, &vbo);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glBufferData(GL_ARRAY_BUFFER, 6  * sizeof(float), points, GL_STATIC_DRAW);

	GLuint vao = 0;
	glGenVertexArrays(1, &vao);
	glBindVertexArray(vao);
	glEnableVertexAttribArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, vbo);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, NULL);


	glLinkProgram(debugMaterial->getShaderProgram());
	glUseProgram(debugMaterial->getShaderProgram());

	glBindVertexArray(vao);

	//glm::mat4 transformMatrix = camera->MVPMatrix;
	glUniform3fv(debugMaterial->shader->paramID["difuse"], 1, &color[0]);
	glm::mat4 transformMatrix(1.0f);
	glUniformMatrix4fv(debugMaterial->shader->paramID["MVP"], 1, GL_FALSE, &transformMatrix[0][0]);

	glDrawArrays(GL_LINES, 0, 2);

}

void GraphicsSystem::clear()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}
void GraphicsSystem::swap()
{

	glfwPollEvents();

	// put the stuff we've been drawing onto the display
	glfwSwapBuffers(window.get());
}