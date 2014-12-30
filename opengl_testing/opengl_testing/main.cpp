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
#include "PlayerScript.hpp"
#include "RigidBody.hpp"
#include "BoxCollider.hpp"
#include "MeshFilter.hpp"
#include "SphereCollider.hpp"
#include "IncreaseColliderScript.hpp"
#include "Editor.hpp"
#include "Game.hpp"
#include "MeshCollider.hpp"
#include "MeshImporter.hpp"

#include <fmod.hpp>
#include <fmod_common.h>
#include <fmod_errors.h>
#include <fbxsdk.h>
#include "EditorCameraControl.hpp"

//-------Loading PhysX libraries----------]
#ifdef _DEBUG
#pragma comment(lib, "PhysX3DEBUG_x86.lib")
#pragma comment(lib, "PhysX3CommonDEBUG_x86.lib")
#pragma comment(lib, "PhysX3ExtensionsDEBUG.lib")
#pragma comment(lib, "PhysX3CookingDEBUG_x86.lib")
#else
#pragma comment(lib, "PhysX3_x86.lib")
#pragma comment(lib, "PhysX3Common_x86.lib")
#pragma comment(lib, "PhysX3Extensions.lib")
#pragma comment(lib, "PhysX3Cooking_x86.lib")
#endif
using namespace physx;
using namespace std;
using namespace fbxsdk_2015_1;


enum EngineMode {editor, game};



int main() {

	int notOK = GraphicsSystem::getInstance().init();
	if (notOK)
		return 1;

	Input input(GraphicsSystem::getInstance().window);


	FMOD_RESULT result;
	FMOD::System *system = NULL;

	result = FMOD::System_Create(&system);      // Create the main system object.
	if (result != FMOD_OK)
	{
		printf("FMOD error! (%d) %s\n", result, FMOD_ErrorString(result));
		exit(-1);
	}

	result = system->init(512, FMOD_INIT_NORMAL, 0);    // Initialize FMOD.
	if (result != FMOD_OK)
	{
		printf("FMOD error! (%d) %s\n", result, FMOD_ErrorString(result));
		exit(-1);
	}
	FMOD::Channel    *channel = 0;
	FMOD::Sound *sound1;
	result = system->createSound(CommonData("mp3test.mp3").c_str(), FMOD_DEFAULT, 0, &sound1);
	//ERRCHECK(result);

	result = system->playSound(sound1, 0, false, &channel);
	//ERRCHECK(result);
	
	MeshImporter meshImporter;
	meshImporter.init();
	shared_ptr<Mesh> fbxMesh = meshImporter.importFbxMesh("box.fbx");
	fbxMesh->scale(0.1f);

	shared_ptr<Mesh> objMesh = meshImporter.importObjMesh("sphere.obj");
	


	Physics physics;
	physics.init();

	EngineMode engineMode = EngineMode::editor;

	shared_ptr<Editor> editor = make_shared<Editor>();
	editor->init();

	shared_ptr<Game> game = make_shared<Game>();
	game->init();


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

	float quadNormal[] =
	{
		0.0f, 0.0f, 1.0f, //0
		0.0f, 0.0f, 1.0f, //1
		0.0f, 0.0f, 1.0f, //2
		0.0f, 0.0f, 1.0f, //3
	};

	float quadIndex[] =
	{
		-0.5f, -0.5f, 0,  //0
		-0.5f, 0.5f, 0,   //1
		0.5f, 0.5f, 0,    //2
		0.5f, -0.5f, 0    //3
	};
    
	unsigned int quadTriangles[] =
	{
		0,1,3,
		1,2,3
	};

    string vsDataPath = DATA_PATH;
    string fsDataPath = DATA_PATH;
    
	//shared_ptr<Shader> s = make_shared<Shader>(vsDataPath.append("vs.vs").c_str(), fsDataPath.append("fs.fragmentshader").c_str());//"/Users/guilherme_cunha/Dev/GITHUB/GUInity/data/vsLight.vs", "/Users/guilherme_cunha/Dev/GITHUB/GUInity/data/fsLight.fragmentshader");

	shared_ptr<Shader> s = make_shared<Shader>(vsDataPath.append("vsLight.vs").c_str(),fsDataPath.append("fsLight.fragmentshader").c_str());//"/Users/guilherme_cunha/Dev/GITHUB/GUInity/data/vsLight.vs", "/Users/guilherme_cunha/Dev/GITHUB/GUInity/data/fsLight.fragmentshader");
	
	shared_ptr<Material> m = make_shared<Material>(s);
	//m->setParamVec3("difuse", glm::vec3(1, 0, 0));

	shared_ptr<Material> m2 = make_shared<Material>(s);
	//m2->setParamVec3("difuse", glm::vec3(0, 1, 0));

	shared_ptr<Material> m3 = make_shared<Material>(s);
	//m3->setParamVec3("difuse", glm::vec3(0, 0, 1));

	string meshDataPath = DATA_PATH;

	//shared_ptr<Mesh> sphereMesh = make_shared<Mesh>(meshDataPath.append("sphere.obj").c_str());
	//shared_ptr<Mesh> triangleMesh = make_shared<Mesh>(pointsTriangle,3,colorTriangle,normalTriangle);
	//shared_ptr<Mesh> quadMesh = make_shared<Mesh>(pointsQuad, 6, colorQuad, normalQuad);
	//shared_ptr<Mesh> quadMesh = make_shared<Mesh>(quadIndex, quadTriangles, quadNormal, 4, 6);
	//shared_ptr<Mesh> cubeMesh = make_shared<Mesh>(pointsCube, 36, nullptr,normalCube);

	shared_ptr<Actor> fbxTest = Factory::CreateActor("FBXTest");// , meshRenderer1);
	fbxTest->transform->setPosition(glm::vec3(0, 0, 0));
	fbxTest->transform->setRotationQuat(glm::quat(glm::vec3(-90 * Math::Deg2Radian, 0, 0)));
	//fbxTest->transform->setScale(glm::vec3(0.1, 0.1, 0.1));

	shared_ptr<MeshFilter> meshFilter = fbxTest->AddComponent<MeshFilter>();
	//meshFilter->mesh = quadMesh;
	//meshFilter->mesh = fbxMesh;
	meshFilter->mesh = fbxMesh;
	shared_ptr<MeshRenderer> meshRenderer = fbxTest->AddComponent<MeshRenderer>();
	meshRenderer->material = m;
	//shared_ptr<RigidBody> rigidBody = fbxTest->AddComponent<RigidBody>();
	//shared_ptr<MeshCollider> meshCol = fbxTest->AddComponent<MeshCollider>();
	shared_ptr<BoxCollider> meshCol = fbxTest->AddComponent<BoxCollider>();

	
	//rigidBody->setKinematic(true);
	//myplane->AddComponent<BoxCollider>();

	//shared_ptr<Actor> myplane = Factory::CreateActor("Plane");// , meshRenderer1);
	//myplane->transform->setPosition(glm::vec3(0, -4, 0));
	//myplane->transform->setRotationQuat(glm::quat(glm::vec3(-90*Math::Deg2Radian,0,0)));
	//myplane->transform->setScale(glm::vec3(5, 5, 5));
	
	//shared_ptr<Light> light = make_shared<Light>(glm::vec3(0, 10, 10), glm::vec3(1,1,1));
	//shared_ptr<Actor> mycube = Factory::CreateActor("Cube");// , meshRenderer3);
	//mycube->transform->setRotationQuat(glm::quat(glm::vec3(-90 * Math::Deg2Radian, 0, 0)));
	//mycube->transform->setPosition(glm::vec3(0, -2, 0));
	//
	//shared_ptr<Actor> mysphere = Factory::CreateActor("Sphere");// , meshRenderer4);
	//mysphere->transform->setPosition(glm::vec3(0, 0, 0));
	//mysphere->transform->setScale(glm::vec3(1, 1, 1)*0.5f);
	
	shared_ptr<Actor> myLight = Factory::CreateActor("Light");// , meshRenderer4);
	myLight->transform->setPosition(glm::vec3(0, 10, 10));
	myLight->AddComponent<Light>();
	
	shared_ptr<Actor> myCamera = Factory::CreateActor("Camera");// , meshRenderer4);
	myCamera->transform->setPosition(glm::vec3(0, 0, 10));
	myCamera->transform->setRotationQuat(glm::quat(glm::vec3(0, 180 * Math::Deg2Radian, 0)));
	myCamera->AddComponent<Camera>();
	myCamera->AddComponent<EditorCameraControl>();
	
	//mysphere->AddComponent<PlayerScript>();
	
	//shared_ptr<MeshFilter> meshFilter = mycube->AddComponent<MeshFilter>();
	//meshFilter->mesh = cubeMesh;
	//shared_ptr<MeshRenderer> meshRenderer = mycube->AddComponent<MeshRenderer>();
	//meshRenderer->material = m;
	//mycube->AddComponent<RigidBody>();
	//shared_ptr<BoxCollider> collider = mycube->AddComponent<BoxCollider>();
	////collider->setTrigger(true);

	//constexpr a = 10*3;

	//shared_ptr<MeshFilter> meshFilter = myplane->AddComponent<MeshFilter>();
	////meshFilter->mesh = quadMesh;
	//meshFilter->mesh = fbxMesh;
	//shared_ptr<MeshRenderer> meshRenderer = myplane->AddComponent<MeshRenderer>();
	//meshRenderer->material = m;
	////shared_ptr<RigidBody> rigidBody = myplane->AddComponent<RigidBody>();
	////rigidBody->setKinematic(true);
	//myplane->AddComponent<BoxCollider>();

	//meshFilter = mysphere->AddComponent<MeshFilter>();
	//meshFilter->mesh = sphereMesh;
	//meshRenderer = mysphere->AddComponent<MeshRenderer>();
	//meshRenderer->material = m;
	//mysphere->AddComponent<RigidBody>();
	//mysphere->AddComponent<SphereCollider>();
//	//mysphere->AddComponent<MeshCollider>();
	

	shared_ptr<PhysicsMaterial> physMaterial = physics.createMaterial(0.5f, 0.5f, 0.75f);

//	physics.createBoxRigidBody(mycube,    physMaterial, false);
//	physics.createSphereRigidBody(player, physMaterial, false);
	//physics.createSphereRigidBody(mysphere, physMaterial, false);
	//physics.createBoxRigidBody(myplane,   physMaterial, true);
	//physics.createBoxRigidBody(mycube, glm::vec3(0.5f, 0.5f, 0.5f), 0.5f, 0.5f, 0.75f, false);
	//physics.createBoxRigidBody(myplane, glm::vec3(2.5f, 2.5f, 0.1f), 0.5f, 0.5f, 0.75f,true);
	//physics.createSphereRigidBody(player, 0.5f, 0.5f, 0.5f, 0.75f,false);

	/////////////////////END BOX2D//////////////////////////////

	//shared_ptr<Camera> camera = make_shared<Camera>(0.3f, 100.0f, 45, 4.0f / 3);
	//camera->transform->setPosition(glm::vec3(0, 0, 10));
	//camera->computeModelViewMatrix();



	editor->world->awake();
	game->world->awake();
	//world->awake();

	//int cont = 0;
	while (!glfwWindowShouldClose(GraphicsSystem::getInstance().window.get())) {
		Time::frameStart();

		Input::updateInputState();

        
		switch (engineMode)
		{
		case EngineMode::editor:
			editor->update(Time::deltaTime,game->world);
			break;
		case EngineMode::game:
			game->update(Time::deltaTime);
			break;
		default:
			break;
		}
		
		if (Input::getKeyPressed(GLFW_KEY_1))
			engineMode = EngineMode::editor;
		if (Input::getKeyPressed(GLFW_KEY_2))
			engineMode = EngineMode::game;
	
		Time::frameEnd();
	}

	physics.shutdown();
	
	editor->shutdown();

	game->shutdown();

	//world->shutdown();


	// close GL context and any other GLFW resources
	GraphicsSystem::getInstance().shutdown();


	return 0;
}	
 