#include <gl/glew.h>
#include <GLFW/glfw3.h>
#include <glm/common.hpp>
#include <glm/gtc/quaternion.hpp>
#include <stdio.h>
#include <memory>
#include <iostream>
#include <fstream>

#include "Material.hpp"
#include <vector>
#include "Actor.hpp"
#include "Camera.hpp"
#include <tuple>
#include "Input.hpp"
#include "GraphicsSystem.hpp"
#include "Time.hpp"
#include "World.hpp"
#include "Mesh.hpp"
#include "MeshRenderer.hpp"
#include "Shader.hpp"
//#include <Box2D\Box2D.h>
#include <PxPhysicsAPI.h>
#include <PxQueryReport.h>


#include "print.hpp"
#include "Factory.hpp"
#include "PhysXEventCallback.hpp"
#include "Physics.hpp"
#include "Light.hpp"
#include "PhysicsMaterial.hpp"
#include "Script.hpp"
#include "PlayerScript.hpp"


//-------Loading PhysX libraries----------]
#ifdef _DEBUG
#pragma comment(lib, "PhysX3DEBUG_x86.lib")
#pragma comment(lib, "PhysX3CommonDEBUG_x86.lib")
#pragma comment(lib, "PhysX3ExtensionsDEBUG.lib")
#else
#pragma comment(lib, "PhysX3_x86.lib")
#pragma comment(lib, "PhysX3Common_x86.lib")
#pragma comment(lib, "PhysX3Extensions.lib")
#endif
using namespace physx;
using namespace std;



//static int average(lua_State *L)
//{
//	/* get number of arguments */
//	int n = lua_gettop(L);
//	double sum = 0;
//	int i;
//
//	/* loop through each argument */
//	for (i = 1; i <= n; i++)
//	{
//		/* total the arguments */
//		sum += lua_tonumber(L, i);
//	}
//
//	/* push the average */
//	lua_pushnumber(L, sum / n);
//
//	/* push the sum */
//	lua_pushnumber(L, sum);
//
//	/* return the number of results */
//	return 2;
//}
//
//static int vec3 = 10;
//
//static int test(lua_State *L)
//{
//	lua_pushnumber(L, 1);
//
//	return 1;
//}

int main() {

	GraphicsSystem graphicsSystem;
	int notOK = graphicsSystem.init();
	if (notOK)
		return 1;

	Input input(graphicsSystem.window);

	World world;

	Physics physics;
	physics.init();

	float pointsTriangle[] = {
		0.0f, 0.5f, 0.0f,
		0.5f, -0.5f, 0.0f,
		-0.5f, -0.5f, 0.0f
	};
	float colorTriangle[] =
	{
		1.0f, 0.0f, 0.0f,
		0.0f, 1.0f, 0.0f,
		0.0f, 0.0f, 1.0f,
	};
	float normalTriangle[] =
	{
		0.0f, 0.0f, 1.0f,
		0.0f, 0.0f, 1.0f,
		0.0f, 0.0f, 1.0f,
	};

	float pointsQuad[] = {
		-0.5f, -0.5f, 0.0f,
		0.5f, 0.5f, 0.0f,
		-0.5f, 0.5f, 0.0f,
		-0.5f, -0.5f, 0.0f,
		0.5f, -0.5f, 0.0f,
		0.5f, 0.5f, 0.0f
	};
	float colorQuad[] =
	{
		0.0f, 0.0f, 1.0f,
		0.0f, 1.0f, 0.0f,
		1.0f, 0.0f, 0.0f,
		0.0f, 0.0f, 1.0f,
		1.0f, 0.0f, 0.0f,
		0.0f, 1.0f, 0.0f,
	};
	float normalQuad[] =
	{
		0.0f, 0.0f, 1.0f,
		0.0f, 0.0f, 1.0f,
		0.0f, 0.0f, 1.0f,
		0.0f, 0.0f, 1.0f,
		0.0f, 0.0f, 1.0f,
		0.0f, 0.0f, 1.0f,
	};
	float pointsCube[] = {
		// botom	
		-0.5f, -0.5f, -0.5f,
		0.5f, -0.5f, -0.5f,
		-0.5f, -0.5f, 0.5f,
		0.5f, -0.5f, -0.5f,
		0.5f, -0.5f, 0.5f,
		-0.5f, -0.5f, 0.5f,

		// top	
		-0.5f, 0.5f, -0.5f,
		-0.5f, 0.5f, 0.5f,
		0.5f, 0.5f, -0.5f,
		0.5f, 0.5f, -0.5f,
		-0.5f, 0.5f, 0.5f,
		0.5f, 0.5f, 0.5f,

		// front	
		-0.5f, -0.5f, 0.5f,
		0.5f, -0.5f, 0.5f,
		-0.5f, 0.5f, 0.5f,
		0.5f, -0.5f, 0.5f,
		0.5f, 0.5f, 0.5f,
		-0.5f, 0.5f, 0.5f,

		// back	
		-0.5f, -0.5f, -0.5f,
		-0.5f, 0.5f, -0.5f,
		0.5f, -0.5f, -0.5f,
		0.5f, -0.5f, -0.5f,
		-0.5f, 0.5f, -0.5f,
		0.5f, 0.5f, -0.5f,

		// left	
		-0.5f, -0.5f, 0.5f,
		-0.5f, 0.5f, -0.5f,
		-0.5f, -0.5f, -0.5f,
		-0.5f, -0.5f, 0.5f,
		-0.5f, 0.5f, 0.5f,
		-0.5f, 0.5f, -0.5f,

		//right	
		0.5f, -0.5f, 0.5f,
		0.5f, -0.5f, -0.5f,
		0.5f, 0.5f, -0.5f,
		0.5f, -0.5f, 0.5f,
		0.5f, 0.5f, -0.5f,
		0.5f, 0.5f, 0.5f

	};
	float normalCube[] = {
		0.0f, -1.0f, 0.0f,
		0.0f, -1.0f, 0.0f,
		0.0f, -1.0f, 0.0f,
		0.0f, -1.0f, 0.0f,
		0.0f, -1.0f, 0.0f,
		0.0f, -1.0f, 0.0f,

		0.0f, 1.0f, 0.0f,
		0.0f, 1.0f, 0.0f,
		0.0f, 1.0f, 0.0f,
		0.0f, 1.0f, 0.0f,
		0.0f, 1.0f, 0.0f,
		0.0f, 1.0f, 0.0f,

		0.0f, 0.0f, 1.0f,
		0.0f, 0.0f, 1.0f,
		0.0f, 0.0f, 1.0f,
		0.0f, 0.0f, 1.0f,
		0.0f, 0.0f, 1.0f,
		0.0f, 0.0f, 1.0f,

		0.0f, 0.0f, -1.0f,
		0.0f, 0.0f, -1.0f,
		0.0f, 0.0f, -1.0f,
		0.0f, 0.0f, -1.0f,
		0.0f, 0.0f, -1.0f,
		0.0f, 0.0f, -1.0f,

		-1.0f, 0.0f, 0.0f,
		-1.0f, 0.0f, 0.0f,
		-1.0f, 0.0f, 0.0f,
		-1.0f, 0.0f, 0.0f,
		-1.0f, 0.0f, 0.0f,
		-1.0f, 0.0f, 0.0f,

		1.0f, 0.0f, 0.0f,
		1.0f, 0.0f, 0.0f,
		1.0f, 0.0f, 0.0f,
		1.0f, 0.0f, 0.0f,
		1.0f, 0.0f, 0.0f,
		1.0f, 0.0f, 0.0f,

	};
    
    string vsDataPath = DATA_PATH;
    string fsDataPath = DATA_PATH;
    
	shared_ptr<Shader> s = make_shared<Shader>(vsDataPath.append("vsLight.vs").c_str(),fsDataPath.append("fsLight.fragmentshader").c_str());//"/Users/guilherme_cunha/Dev/GITHUB/GUInity/data/vsLight.vs", "/Users/guilherme_cunha/Dev/GITHUB/GUInity/data/fsLight.fragmentshader");
	
	shared_ptr<Material> m = make_shared<Material>(s);
	//m->setParamVec3("difuse", glm::vec3(1, 0, 0));

	shared_ptr<Material> m2 = make_shared<Material>(s);
	//m2->setParamVec3("difuse", glm::vec3(0, 1, 0));

	shared_ptr<Material> m3 = make_shared<Material>(s);
	//m3->setParamVec3("difuse", glm::vec3(0, 0, 1));

	string meshDataPath = DATA_PATH;

	shared_ptr<Mesh> sphereMesh = make_shared<Mesh>(meshDataPath.append("sphere.obj").c_str());
	shared_ptr<Mesh> triangleMesh = make_shared<Mesh>(pointsTriangle,3,colorTriangle,normalTriangle);
	shared_ptr<Mesh> quadMesh = make_shared<Mesh>(pointsQuad, 6, colorQuad, normalQuad);
	shared_ptr<Mesh> cubeMesh = make_shared<Mesh>(pointsCube, 36, nullptr,normalCube);

	shared_ptr<MeshRenderer> meshRenderer1 = make_shared<MeshRenderer>(quadMesh, m);
	shared_ptr<MeshRenderer> meshRenderer2 = make_shared<MeshRenderer>(triangleMesh, m2);
	shared_ptr<MeshRenderer> meshRenderer3 = make_shared<MeshRenderer>(cubeMesh, m3);
	//shared_ptr<MeshRenderer> meshRenderer4 = make_shared<MeshRenderer>(sphereMesh, m3);

	//shared_ptr<Player> player = Factory::CreateActor<Player>("Player", meshRenderer2);
	shared_ptr<Actor> player = Factory::CreateActor<Actor>("Player", meshRenderer2);
	player->transform->setPosition(glm::vec3(0, 0, 0));

	shared_ptr<Actor> myplane = Factory::CreateActor("Plane", meshRenderer1);
	myplane->transform->setPosition(glm::vec3(0, -4, 0));
	myplane->transform->setRotationQuat(glm::quat(glm::vec3(-90*Math::Deg2Radian,0,0)));
	myplane->transform->setScale(glm::vec3(5, 5, 5));
	
	shared_ptr<Light> light = make_shared<Light>(glm::vec3(0, 10, 10), glm::vec3(1,1,1));
	shared_ptr<Actor> mycube = Factory::CreateActor("Cube", meshRenderer3);
	mycube->transform->setRotationQuat(glm::quat(glm::vec3(-90 * Math::Deg2Radian, 0, 0)));
	mycube->transform->setPosition(glm::vec3(0, -2, 0));

	//shared_ptr<Actor> mysphere = Factory::CreateActor("Sphere", meshRenderer4);
	//mysphere->transform->setPosition(glm::vec3(0, -1, 0));
	//mysphere->transform->setScale(glm::vec3(1, 1, 1)*0.5f);

	//shared_ptr<Script> script = make_shared<PlayerScript>();
//	unique_ptr<Script> script = make_unique<PlayerScript>();

	world.addActor(myplane);
	world.addLight(light);
	world.addActor(mycube);
	//world.addActor(mysphere);


	//shared_ptr<PlayerScript> script = mycube->AddScript<PlayerScript>();
	//script->setSphereRef(world.findActor("Sphere"));
	//script->setReference()
	//mycube->AddScript<PlayerScript>();
	//AddScript<PlayerScript>(mysphere);

	//CreateScriptComponent<PlayerScript>(mysphere);
	//Factory::CreateScriptComponent<int>(mysphere);
	//Factory::CreateScriptComponent<PlayerScript>(mysphere);
	//Factory::CreateScriptComponent<PlayerScript>(mysphere);
	//Factory::CreateScriptComponent(mysphere, script);
	//Factory::CreateScriptComponent(mycube, script);



	//world.addActor(player);



	shared_ptr<PhysicsMaterial> physMaterial = physics.createMaterial(0.5f, 0.5f, 0.75f);

	physics.createBoxRigidBody(mycube,    physMaterial, false);
//	physics.createSphereRigidBody(player, physMaterial, false);
	//physics.createSphereRigidBody(mysphere, physMaterial, false);
	physics.createBoxRigidBody(myplane,   physMaterial, true);
	//physics.createBoxRigidBody(mycube, glm::vec3(0.5f, 0.5f, 0.5f), 0.5f, 0.5f, 0.75f, false);
	//physics.createBoxRigidBody(myplane, glm::vec3(2.5f, 2.5f, 0.1f), 0.5f, 0.5f, 0.75f,true);
	//physics.createSphereRigidBody(player, 0.5f, 0.5f, 0.5f, 0.75f,false);

	/////////////////////END BOX2D//////////////////////////////

	shared_ptr<Camera> camera = make_shared<Camera>(0.3f, 100.0f, 45, 4.0f / 3);
	camera->transform->setPosition(glm::vec3(0, 0, 10));
	camera->computeModelViewMatrix();

//	LuaBinder luaBinder;
//	luaBinder.RunScript(nullptr);

	world.awake();

	//int cont = 0;
	while (!glfwWindowShouldClose(graphicsSystem.window.get())) {
		Time::frameStart();

		Input::updateInputState();
		
		Ray r = camera->screenPointToRay(Input::mousePos);
		
		PxRaycastBuffer hitCallback;
		if (Input::getMouseButton(GLFW_MOUSE_BUTTON_1) && Physics::rayCast(r, 300, hitCallback))
		{
			Actor *a = (Actor*)hitCallback.block.actor->userData;
		
			cout << "Mouse click: " << a->name << endl;
		}

		Physics::tick();
		Physics::updateActorsTransform();

		world.tick(Time::deltaTime);

		graphicsSystem.clear();

		graphicsSystem.render(camera, world.actors, world.lights);
		graphicsSystem.render(camera, Physics::scene->getRenderBuffer(), glm::vec3(1, 1, 1));
		graphicsSystem.swap();

		Time::frameEnd();
	}

	physics.shutdown();
	
	// close GL context and any other GLFW resources
	graphicsSystem.shutdown();

	return 0;
}
 