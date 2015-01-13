#include <gl/glew.h>
#include <GLFW/glfw3.h>
#include <glm/common.hpp>
#include <glm/gtc/quaternion.hpp>
#include <stdio.h>
#include <memory>
#include <iostream>
#include <fstream>

#include "Serialization2.hpp"

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
#include "AssetDatabase.hpp"

#include <fmod.hpp>
#include <fmod_common.h>
#include <fmod_errors.h>
#include <fbxsdk.h>
#include "EditorCameraControl.hpp"
#include "mainwindow.h"
#include "Texture.h"
#include <png.h>

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




BOOST_CLASS_EXPORT_GUID(Asset, "Asset")
BOOST_CLASS_EXPORT_GUID(Mesh, "Mesh")
BOOST_CLASS_EXPORT_GUID(Material, "Material")
BOOST_CLASS_EXPORT_GUID(Shader, "Shader")
//BOOST_CLASS_EXPORT_GUID(Component, "Component")
//BOOST_CLASS_EXPORT_GUID(RigidBody, "RigidBody")
//BOOST_CLASS_EXPORT_GUID(MeshFilter, "MeshFilter")
//BOOST_CLASS_EXPORT_GUID(MeshRenderer, "MeshRenderer")
BOOST_CLASS_EXPORT_GUID(ComponentDescription, "ComponentDescription")
BOOST_CLASS_EXPORT_GUID(MeshFilterDescription, "MeshFilterDescription")
BOOST_CLASS_EXPORT_GUID(MeshRendererDescription, "MeshRendererDescription")
BOOST_CLASS_EXPORT_GUID(CameraDescription, "CameraDescription")
BOOST_CLASS_EXPORT_GUID(RigidBodyDescription, "RigidBodyDescription")
BOOST_CLASS_EXPORT_GUID(RigidStaticDescription, "RigidStaticDescription")
BOOST_CLASS_EXPORT_GUID(LightDescription, "LightDescription")
BOOST_CLASS_EXPORT_GUID(ColliderDescription, "ColliderDescription")
BOOST_CLASS_EXPORT_GUID(BoxColliderDescription, "BoxColliderDescription")
BOOST_CLASS_EXPORT_GUID(SphereColliderDescription, "SphereColliderDescription")
BOOST_CLASS_EXPORT_GUID(CapsuleColliderDescription, "CapsuleColliderDescription")

#include <fstream>



//#include "mainwindow.h"
//#include <QApplication>
//#include <qsurfaceformat.h>

int main(int argc, char *argv[]) {


    
//    QApplication app(argc, argv);
//
//
//    MainWindow myWindow;// = new MainWindow;
//    //QWidget *window = myWindow->window();
//
    int notOK = GraphicsSystem::getInstance()->init();
	if (notOK)
		return 1;
    
    
//
//    //GraphicsSystem::getInstance()->setGraphicsParent(app.activeWindow());
//
//    myWindow.init();
//    myWindow.show();
//
//
//    return app.exec();

//    while(true)
//    {
//        if(app.hasPendingEvents())
//            app.processEvents();

//        myWindow.tick();
//    }
//    return app.exec();

    Input input(GraphicsSystem::getInstance()->window);


//	FMOD_RESULT result;
//	FMOD::System *system = NULL;

//	result = FMOD::System_Create(&system);      // Create the main system object.
//	if (result != FMOD_OK)
//	{
//		printf("FMOD error! (%d) %s\n", result, FMOD_ErrorString(result));
//		exit(-1);
//	}

//	result = system->init(512, FMOD_INIT_NORMAL, 0);    // Initialize FMOD.
//	if (result != FMOD_OK)
//	{
//		printf("FMOD error! (%d) %s\n", result, FMOD_ErrorString(result));
//		exit(-1);
//	}
//	FMOD::Channel    *channel = 0;
//	FMOD::Sound *sound1;
//	result = system->createSound(CommonData("mp3test.mp3").c_str(), FMOD_DEFAULT, 0, &sound1);
//	//ERRCHECK(result);

//	result = system->playSound(sound1, 0, false, &channel);
    //ERRCHECK(result);
	
    Physics physics;
    physics.init();
    
    EngineMode engineMode = EngineMode::editor;
    
    AssetDatabase::init();
    
    vector<MeshVertex> quadVertex;
    MeshVertex meshVertex;
    meshVertex.position.x = -0.5;
    meshVertex.position.y = -0.5;
    meshVertex.position.z = 0;
    meshVertex.normal.x = 0;
    meshVertex.normal.y = 0;
    meshVertex.normal.z = 1;
    meshVertex.uv.x = 0;
    meshVertex.uv.y = 0;
    
    quadVertex.push_back(meshVertex);
    
    meshVertex.position.x = -0.5;
    meshVertex.position.y = 0.5;
    meshVertex.position.z = 0;
    meshVertex.normal.x = 0;
    meshVertex.normal.y = 0;
    meshVertex.normal.z = 1;
    meshVertex.uv.x = 0;
    meshVertex.uv.y = 1;
    
    quadVertex.push_back(meshVertex);
    
    meshVertex.position.x = 0.5;
    meshVertex.position.y = -0.5;
    meshVertex.position.z = 0;
    meshVertex.normal.x = 0;
    meshVertex.normal.y = 0;
    meshVertex.normal.z = 1;
    meshVertex.uv.x = 1;
    meshVertex.uv.y = 0;
    
    quadVertex.push_back(meshVertex);
    
    meshVertex.position.x = 0.5;
    meshVertex.position.y = 0.5;
    meshVertex.position.z = 0;
    meshVertex.normal.x = 0;
    meshVertex.normal.y = 0;
    meshVertex.normal.z = 1;
    meshVertex.uv.x = 1;
    meshVertex.uv.y = 1;
    
    quadVertex.push_back(meshVertex);
    
    vector<unsigned short> triangles;
    triangles.push_back(2);
    triangles.push_back(1);
    triangles.push_back(0);
    triangles.push_back(3);
    triangles.push_back(1);
    triangles.push_back(2);
    
    shared_ptr<Mesh> quadMesh = AssetDatabase::createMesh(quadVertex,triangles);
    
    shared_ptr<Texture> texture = AssetDatabase::createTexture(CommonData("button.png"));
//        read_png_file(CommonData("Crosshair.png").c_str());
    
    shared_ptr<Mesh> fbxMesh = AssetDatabase::createMeshFromFBX("box.fbx");
    fbxMesh->setScaleFactor(0.1f);
    
    shared_ptr<Mesh> objMesh = AssetDatabase::createMeshFromOBJ("sphere.obj");
    
    
    shared_ptr<Editor> editor = make_shared<Editor>();
    editor->init();
    
    shared_ptr<Game> game = make_shared<Game>();
    game->init();

 
    
  
    
    // create and open a character archive for output
    std::ofstream ofs(CommonData("filename"));
    
    shared_ptr<Shader> s = AssetDatabase::createShader(CommonData("vsLight.vs"),CommonData("fsLight.fragmentshader"));
    //shared_ptr<Shader> s = AssetDatabase::createShader(CommonData("vsLight.vs"),CommonData("fsNoLight.fragmentshader"));
    
    shared_ptr<Material> m = AssetDatabase::createMaterial(s);
    
     shared_ptr<Actor> fbxTest = Factory::CreateActor("FBXTest");// , meshRenderer1);
    //fbxTest->transform->setScale(glm::vec3(10,10,10));
     //fbxTest->transform->setPosition(glm::vec3(0, 0, 0));
     //fbxTest->transform->setRotationQuat(glm::quat(glm::vec3(-90 * Math::Deg2Radian, 0, 0)));

    
    shared_ptr<MeshFilter> meshFilter = fbxTest->AddComponent<MeshFilter>();
    //meshFilter->mesh = dynamic_pointer_cast<Mesh>(objMesh);
    meshFilter->mesh = fbxMesh;
    shared_ptr<MeshRenderer> meshRenderer = fbxTest->AddComponent<MeshRenderer>();
    meshRenderer->material = m;
    fbxTest->AddComponent<RigidBody>();
    fbxTest->AddComponent<BoxCollider>();
    
    
//    //fbxTest = nullptr;
//	
//    
// //   shared_ptr<World> testWorld = game->world;
//    
// //   shared_ptr<RigidBody> rigidBody = fbxTest->AddComponent<RigidBody>();
//    // save data to archive
//    {
//        boost::archive::text_oarchive oa(ofs);
//        // write class instance to archive
//        oa & AssetDatabase::idToAsset;
//        oa & AssetDatabase::currentID;
//        
//        //oa & rigidBody;
//        //oa & fbxTest;
////        oa & fbxTest->components;
//        
//        ActorDescription desc = getActorDescription(fbxTest);
//        
//        oa & desc;
//        vector<shared_ptr<ComponentDescription>> compDescs = getActorComponentsDescription(fbxTest);
//        oa & compDescs;
//        
//        //oa & game->world;
//        // archive and stream closed when destructors are called
//    }
//  //  exit(0);
//    
//    
//    //Actor x;
//    shared_ptr<Actor> serializeTest;
//    {
//        // create and open an archive for input
//        std::ifstream ifs(CommonData("filename"),std::fstream::binary | std::fstream::in);
//        boost::archive::text_iarchive ia(ifs);
//        // read class state from archive
//        //ia >> objLoad;
//        ia & AssetDatabase::idToAsset;
//        ia & AssetDatabase::currentID;
//    //    ia & testWorld;
//        //ia & fbxTest;
//        //ia & x;
//        //ia & testWorld;
//        
//       // ia & game->world;
//        
//        ActorDescription desc;// = getActorDescription(*fbxTest);
//        
//        ia & desc;
//        
//        serializeTest = Factory::DeserializeActor(desc);
//        
//        vector<shared_ptr<ComponentDescription>> compDescs;
//        ia & compDescs;
//        
//        Factory::DeserializeComponents(serializeTest,compDescs);
//    }
//
//    shared_ptr<Asset> loadedObjMesh = dynamic_pointer_cast<Mesh>(AssetDatabase::idToAsset[1]);///AssetDatabase::createMeshFromOBJ("sphere.obj");
//
//     shared_ptr<Shader> loadedShader = dynamic_pointer_cast<Shader>(AssetDatabase::idToAsset[2]);///
//    
//    shared_ptr<Material> loadedMaterial = dynamic_pointer_cast<Material>(AssetDatabase::idToAsset[3]);///
//    
//    
//    shared_ptr<MeshFilter> meshFilter2 = serializeTest->AddComponent<MeshFilter>();
//    meshFilter2->mesh = dynamic_pointer_cast<Mesh>(loadedObjMesh);
//    shared_ptr<MeshRenderer> meshRenderer2 = serializeTest->AddComponent<MeshRenderer>();
//    meshRenderer2->material = loadedMaterial;

    shared_ptr<Actor> myLight = Factory::CreateActor("Light");// , meshRenderer4);
    myLight->transform->setPosition(glm::vec3(0, 10, 10));
    myLight->AddComponent<Light>();
	
    shared_ptr<Actor> myCamera = Factory::CreateActor("Camera");// , meshRenderer4);
    myCamera->transform->setPosition(glm::vec3(0, 0, 10));
    myCamera->transform->setRotationQuat(glm::quat(glm::vec3(0, 180 * Math::Deg2Radian, 0)));
    myCamera->AddComponent<Camera>();
    myCamera->AddComponent<EditorCameraControl>();

    shared_ptr<PhysicsMaterial> physMaterial = physics.createMaterial(0.5f, 0.5f, 0.75f);


    editor->world->awake();
    game->world->awake();

    while (!glfwWindowShouldClose(GraphicsSystem::getInstance()->window.get())) {
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

    // close GL context and any other GLFW resources
    GraphicsSystem::getInstance()->shutdown();


	return 0;
}	
