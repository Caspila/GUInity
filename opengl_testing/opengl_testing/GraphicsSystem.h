#pragma once

#include "Module.h"
#include "Actor.h"
#include "Camera.h"
#include <PxPhysicsAPI.h>
#include "print.h"
#include "Light.h"

using namespace physx;

class GraphicsSystem
{
public:
	GraphicsSystem();
	~GraphicsSystem();

	int init();
	void shutdown();

	shared_ptr<GLFWwindow> window;

	void render(shared_ptr<Camera> camera, vector < shared_ptr<Actor>> actors, vector < shared_ptr<Light>> lights);
	void render(shared_ptr<Camera> camera, const  physx::PxRenderBuffer& rb, const glm::vec3& color);
	void render(shared_ptr<Camera> camera, const Ray& r, const glm::vec3& color);

	void clear();
	void swap();


	void createDebugShader();
	shared_ptr<Shader> debugShader;
	shared_ptr<Material> debugMaterial;
};

