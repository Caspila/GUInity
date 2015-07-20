#include <stdio.h>
#include <memory>
#include <iostream>
#include <fstream>
#include <vector>
#include <iostream>
#include <thread>

#include "Module.hpp"

// SYSTEMS
#include "Input.hpp"
#include "GraphicsSystem.hpp"
#include "Time.hpp"
#include "SoundSystem.hpp"
#include "Editor.hpp"
#include "Game.hpp"
#include "Physics.hpp"
#include "Math.hpp"
#include "Factory.hpp"


// HELPERS
#include "print.hpp"
#include "FSAuxiliar.hpp"

// ASSETS
#include "AssetDatabase.hpp"
#include "Material.hpp"
#include "Font.hpp"
#include "Mesh.hpp"
#include "Shader.hpp"
#include "Sound.hpp"
#include "Texture.hpp"
#include "PhysicsMaterial.hpp"

// ACTOR / COMPONENTS
#include "Actor.hpp"
#include "Camera.hpp"
#include "MeshRenderer.hpp"
#include "FontMesh.hpp"
#include "Light.hpp"
#include "RigidBody.hpp"
#include "BoxCollider.hpp"
#include "MeshFilter.hpp"
#include "SphereCollider.hpp"
#include "MeshCollider.hpp"
#include "MeshImporter.hpp"

// SCRIPTS
#include "EditorCameraControl.hpp"
#include "PlayerScript.hpp"
#include "KillOnCollision.hpp"
#include "AsteroidSpawner.hpp"
#include "PointsTracker.hpp"

// MYGAME
#include "MyGame.hpp"
#include "SpaceShipGame.hpp"

// LIBRARIES
#include <boost/filesystem.hpp>

using namespace std;
using namespace boost::filesystem;

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

BOOST_CLASS_EXPORT_GUID(Asset, "Asset")
BOOST_CLASS_EXPORT_GUID(Mesh, "Mesh")
BOOST_CLASS_EXPORT_GUID(Material, "Material")
BOOST_CLASS_EXPORT_GUID(Shader, "Shader")
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
BOOST_CLASS_EXPORT_GUID(FontMeshDescription, "FontMeshDescription")

BOOST_SHARED_POINTER_EXPORT_GUID(RigidStatic,"RigidStatic")
BOOST_SHARED_POINTER_EXPORT_GUID(MeshComponent, "MeshComponent")
BOOST_SHARED_POINTER_EXPORT_GUID(MeshRenderer, "MeshRenderer")
BOOST_SHARED_POINTER_EXPORT_GUID(MeshFilter, "MeshFilter")
BOOST_SHARED_POINTER_EXPORT_GUID(Component, "Component")
BOOST_SHARED_POINTER_EXPORT_GUID(Collider, "Collider")
BOOST_SHARED_POINTER_EXPORT_GUID(SphereCollider, "SphereCollider")
BOOST_SHARED_POINTER_EXPORT_GUID(BoxCollider, "BoxCollider")
BOOST_SHARED_POINTER_EXPORT_GUID(CapsuleCollider, "CapsuleCollider")
BOOST_SHARED_POINTER_EXPORT_GUID(Camera, "Camera")
BOOST_SHARED_POINTER_EXPORT_GUID(FontMesh, "FontMesh")
BOOST_SHARED_POINTER_EXPORT_GUID(Light, "Light")
BOOST_SHARED_POINTER_EXPORT_GUID(ScriptComponent, "ScriptComponent")
BOOST_SHARED_POINTER_EXPORT_GUID(RigidBody, "RigidBody")
BOOST_SHARED_POINTER_EXPORT_GUID(Actor, "Actor")
BOOST_SHARED_POINTER_EXPORT_GUID(Transform, "Transform")


#define EXPORT __attribute__((visibility("default")))


EXPORT
int startGUInity(GLFWwindow* window)
{
    
    int notOK = GraphicsSystem::getInstance()->initGLFW(window,1024,768);
	if (notOK)
		return 1;
    
    AssetDatabase::init();
    
    Input input(window);
    //    Input input(GraphicsSystem::getInstance()->getWindow());
	
	SoundSystem::getInstance()->init();
    
    Physics physics;
    physics.init();
    
    
    EngineMode engineMode = EngineMode::editor;
    
    shared_ptr<Editor> editor = make_shared<Editor>();
    editor->init();
    
    shared_ptr<Game> game = make_shared<Game>();
    game->init();
    
    shared_ptr<MyGame> myGame = make_shared<SpaceShipGame>();
    
    myGame->setupInitialScene();
    
    editor->world->awake();
    game->world->awake();
    
    
    while(!GraphicsSystem::getInstance()->shouldClose())
    {
        
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
        
        float fps = Time::frameEnd();
        cout << "FPS:" << 1.0f/fps << endl;
    }
    
    physics.shutdown();
	
    editor->shutdown();
    
    game->shutdown();
    
    // close GL context and any other GLFW resources
	SoundSystem::getInstance()->shutdown();
    GraphicsSystem::getInstance()->shutdown();
    
    return 0;
}

EXPORT
int startGUInity(wxGLCanvas* window,wxGLContext* context)
{
    
    int notOK = GraphicsSystem::getInstance()->initWX(window,context,1024,768);
	if (notOK)
		return 1;
    
    AssetDatabase::init();
    
    Input input();
    //    Input input(GraphicsSystem::getInstance()->getWindow());
	
	SoundSystem::getInstance()->init();
    
    Physics physics;
    physics.init();
    
    
    EngineMode engineMode = EngineMode::editor;
    
    shared_ptr<Editor> editor = make_shared<Editor>();
    editor->init();
    
    shared_ptr<Game> game = make_shared<Game>();
    game->init();
    
    shared_ptr<MyGame> myGame = make_shared<SpaceShipGame>();
    
    myGame->setupInitialScene();
    
    editor->world->awake();
    game->world->awake();
    
    
    while(!GraphicsSystem::getInstance()->shouldClose())
    {
        
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
        
        float fps = Time::frameEnd();
        cout << "FPS:" << 1.0f/fps << endl;
    }
    
    physics.shutdown();
	
    editor->shutdown();
    
    game->shutdown();
    
    // close GL context and any other GLFW resources
	SoundSystem::getInstance()->shutdown();
    GraphicsSystem::getInstance()->shutdown();
    
    return 0;
}

class QWindow;
class QOpenGLContext;

EXPORT
int startGUInity(QWindow* window,QOpenGLContext* context)
{
    
    int notOK = GraphicsSystem::getInstance()->initQT(window,context,1024,768);
	if (notOK)
		return 1;
    
    AssetDatabase::init();
    
    Input input();
    //    Input input(GraphicsSystem::getInstance()->getWindow());
	
	SoundSystem::getInstance()->init();
    
    Physics physics;
    physics.init();
    
    
    EngineMode engineMode = EngineMode::editor;
    
    shared_ptr<Editor> editor = make_shared<Editor>();
    editor->init();
    
    shared_ptr<Game> game = make_shared<Game>();
    game->init();
    
    shared_ptr<MyGame> myGame = make_shared<SpaceShipGame>();
    
    myGame->setupInitialScene();
    
    editor->world->awake();
    game->world->awake();
    
    
    while(!GraphicsSystem::getInstance()->shouldClose())
    {
        
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
        
        float fps = Time::frameEnd();
        cout << "FPS:" << 1.0f/fps << endl;
    }
    
    physics.shutdown();
	
    editor->shutdown();
    
    game->shutdown();
    
    // close GL context and any other GLFW resources
	SoundSystem::getInstance()->shutdown();
    GraphicsSystem::getInstance()->shutdown();
    
    return 0;
}


EXPORT
int startGUInity()
{
    
    int notOK = GraphicsSystem::getInstance()->init(1024,768);
	if (notOK)
		return 1;
    
    AssetDatabase::init();
    
    Input input;
//    Input input(GraphicsSystem::getInstance()->getWindow());
	
	SoundSystem::getInstance()->init();
    
    Physics physics;
    physics.init();
    
    
    EngineMode engineMode = EngineMode::editor;
    
    shared_ptr<Editor> editor = make_shared<Editor>();
    editor->init();
    
    shared_ptr<Game> game = make_shared<Game>();
    game->init();
    
    shared_ptr<MyGame> myGame = make_shared<SpaceShipGame>();
    
    myGame->setupInitialScene();
    
    editor->world->awake();
    game->world->awake();
    
    
    while(!GraphicsSystem::getInstance()->shouldClose())
    {

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
        
        float fps = Time::frameEnd();
        cout << "FPS:" << 1.0f/fps << endl;
    }
    
    physics.shutdown();
	
    editor->shutdown();
    
    game->shutdown();
    
    // close GL context and any other GLFW resources
	SoundSystem::getInstance()->shutdown();
    GraphicsSystem::getInstance()->shutdown();
    
    return 0;
}

class wxGLCanvas;

//EXPORT
//int startGUInityWX(wxGLCanvas *glCanvas)
//{
//    
//    int notOK = GraphicsSystem::getInstance()->initWX(glCanvas,1024,768);
//	if (notOK)
//		return 1;
//    
//    AssetDatabase::init();
//    
//    Input input;
////    Input input(GraphicsSystem::getInstance()->getWindow());
//	
//	SoundSystem::getInstance()->init();
//    
//    Physics physics;
//    physics.init();
//    
//    
//    EngineMode engineMode = EngineMode::editor;
//    
//    shared_ptr<Editor> editor = make_shared<Editor>();
//    editor->init();
//    
//    shared_ptr<Game> game = make_shared<Game>();
//    game->init();
//    
//    shared_ptr<MyGame> myGame = make_shared<SpaceShipGame>();
//    
//    myGame->setupInitialScene();
//    
//    editor->world->awake();
//    game->world->awake();
//    
//    
//    while(!GraphicsSystem::getInstance()->shouldClose())
//    {
//        
//        Time::frameStart();
//        
//        Input::updateInputState();
//        
//        
//        switch (engineMode)
//        {
//            case EngineMode::editor:
//                editor->update(Time::deltaTime,game->world);
//                break;
//            case EngineMode::game:
//                game->update(Time::deltaTime);
//                break;
//            default:
//                break;
//        }
//		
//        if (Input::getKeyPressed(GLFW_KEY_1))
//            engineMode = EngineMode::editor;
//        if (Input::getKeyPressed(GLFW_KEY_2))
//            engineMode = EngineMode::game;
//        
//        float fps = Time::frameEnd();
//        cout << "FPS:" << 1.0f/fps << endl;
//    }
//    
//    physics.shutdown();
//	
//    editor->shutdown();
//    
//    game->shutdown();
//    
//    // close GL context and any other GLFW resources
//	SoundSystem::getInstance()->shutdown();
//    GraphicsSystem::getInstance()->shutdown();
//    
//    return 0;
//}


int main(int argc, char *argv[]) {
    
    return startGUInity();

}
