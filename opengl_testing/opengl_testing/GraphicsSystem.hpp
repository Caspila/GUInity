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

class Camera;
class Actor;
class Light;
class Shader;
class Material;
class MeshRenderer;

using namespace physx;

class GraphicsSystem
//#ifdef GUINITY_DEBUG
//	:public StaticCounter<GraphicsSystem>
//#endif
{

public:
	static GraphicsSystem& getInstance()
	{
		static GraphicsSystem instance; // Guaranteed to be destroyed.
		// Instantiated on first use.
		return instance;
	}

private:
	GraphicsSystem() {};                   // Constructor? (the {} brackets) are needed here.
	// Dont forget to declare these two. You want to make sure they
	// are unaccessable otherwise you may accidently get copies of
	// your singleton appearing.
	GraphicsSystem(GraphicsSystem const&);              // Don't Implement
	void operator=(GraphicsSystem const&); // Don't implement
public:
	//GraphicsSystem();
	~GraphicsSystem();

	int init();
	void shutdown();

	shared_ptr<GLFWwindow> window;

	void render(shared_ptr<Camera> camera, vector < shared_ptr<Actor>> actors, vector < shared_ptr<Light>> lights);
	void render(shared_ptr<Camera> camera, const  physx::PxRenderBuffer& rb, const glm::vec3& color);
	void render(shared_ptr<Camera> camera, const Ray& r, const glm::vec3& color);
	//void render(shared_ptr<Camera> camera, vector < shared_ptr<Light>> lights);
	void render(shared_ptr<Camera> camera, vector < shared_ptr<MeshRenderer>>& renderers, vector<shared_ptr<Light>>& lights);

	void clear();	
	void swap();


	void createDebugShader();
	shared_ptr<Shader> debugShader;
	shared_ptr<Material> debugMaterial;
    
	//vector<weak_ptr<MeshRenderer>> allMeshRenderer;
    
};

