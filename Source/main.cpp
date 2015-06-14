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
#include "RotateOverTime.hpp"
#include "AddForceScript.hpp"
#include "IncreaseColliderScript.hpp"
#include "EditorCameraControl.hpp"
#include "PlayerScript.hpp"

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
//using namespace physx;
//using namespace std;
//using namespace fbxsdk_2015_1;

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

//BOOST_CLASS_EXPORT_GUID(MeshComponent, "MeshComponent")
//BOOST_CLASS_EXPORT_GUID(MeshRenderer, "MeshRenderer")
//BOOST_CLASS_EXPORT_GUID(MeshFilter, "MeshFilter")
//BOOST_CLASS_EXPORT_GUID(Component, "Component")
//BOOST_CLASS_EXPORT_GUID(Collider, "Collider")
//BOOST_CLASS_EXPORT_GUID(SphereCollider, "SphereCollider")
//BOOST_CLASS_EXPORT_GUID(BoxCollider, "BoxCollider")
//BOOST_CLASS_EXPORT_GUID(CapsuleCollider, "CapsuleCollider")
//BOOST_CLASS_EXPORT_GUID(Camera, "Camera")
//BOOST_CLASS_EXPORT_GUID(FontMesh, "FontMesh")
//BOOST_CLASS_EXPORT_GUID(Light, "Light")
//BOOST_CLASS_EXPORT_GUID(ScriptComponent, "ScriptComponent")
//BOOST_CLASS_EXPORT_GUID(RigidBody, "RigidBody")
//BOOST_CLASS_EXPORT_GUID(RigidStatic, "RigidStatic")

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

//#define _GLFW_USE_MENUBAR
//#include "mainwindow.h"
//#include <QApplication>
//#include <qsurfaceformat.h>
#include "AnimationCurve.hpp"




void checkFilesOnCommonData(){
    
    //while(true)
    {
        //        cout << "OI" <<endl;
        
        
        vector<path> files = getFilesInDirectory(CommonData(""));
        
        for(auto& file : files)
        {
            
            
            string filename = file.filename().string();
            //shared_ptr<Asset> asset = AssetDatabase::getAsset(filename);
            
			shared_ptr<Asset> asset = AssetDatabase::tryLoadAsset(file.filename().string(), file.extension().string());
            
            //if(asset)
            //{
            //    int crc = getCRC(file.string());
            //
            //    if(crc == asset->crc)
            //        cout << "CRC Matches!" << endl;
            //    else
            //        cout << "CRC does not match!" << endl;
            //}
            
        }
        
        
        //        path p(CommonData(""));
        //
        //        if(is_directory(p))
        //        {
        //                      // so we can sort them later
        //            vector<path> vec;             // store paths,
        //
        //            copy(directory_iterator(p), directory_iterator(), back_inserter(vec));
        //
        //            for(auto& file : vec)
        //            {
        //                int crc = AssetDatabase::getCRC(CommonData(file));
        //            }
        //
        //        }
    }
    
}

int main(int argc, char *argv[]) {
    
    
	//thread t (checkFilesOnCommonData);
	//t.detach();
    
    
    int notOK = GraphicsSystem::getInstance()->init(640,480);
	if (notOK)
		return 1;
    
    AssetDatabase::init();
    
   	checkFilesOnCommonData();
    
    
    
    Input input(GraphicsSystem::getInstance()->getWindow());
	
	
	SoundSystem::getInstance()->init();
    
	
    
    Physics physics;
    physics.init();
    
    EngineMode engineMode = EngineMode::editor;
    
	
    
	
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
    triangles.push_back(0);
    triangles.push_back(1);
    triangles.push_back(2);
    triangles.push_back(2);
    triangles.push_back(1);
    triangles.push_back(3);
    
    shared_ptr<PhysicsMaterial> bouncyPhysMaterial = AssetDatabase::createPhysicsMaterial("bouncy", 0.0f, 0.0f, 1.0f);
    
    shared_ptr<Mesh> quadMesh = AssetDatabase::createMesh(quadVertex, triangles);
    
	//	shared_ptr<Texture> whiteTexture = AssetDatabase::createTexture(CommonData("white2.png"));
    
    shared_ptr<Font> font = AssetDatabase::createFont("arial.ttf",48);
    
    shared_ptr<Texture> texture = AssetDatabase::getAsset<Texture>("button.png");
    
    
    /*shared_ptr<Sound> sound = AssetDatabase::createSound(CommonData("mp3test.mp3"));
     
     SoundSystem::getInstance()->playSound(sound);
     */
    
    shared_ptr<Mesh> cylinderMesh = AssetDatabase::createMeshFromFBX("cylinder3.fbx");
    
    shared_ptr<Mesh> cubeMesh = AssetDatabase::createMeshFromFBX("box.fbx");
    
    //		shared_ptr<Mesh> objMesh = AssetDatabase::createMeshFromOBJ("sphere.obj");
    
    shared_ptr<Mesh> sphereMesh =  AssetDatabase::getAsset<Mesh>("sphere.obj");
    
    shared_ptr<Mesh> spaceShipMesh =  AssetDatabase::getAsset<Mesh>("arrow.fbx");
    
    shared_ptr<Texture> spaceShipTexture = AssetDatabase::getAsset<Texture>("sh3.png");
    shared_ptr<Texture> spaceBKGTexture = AssetDatabase::getAsset<Texture>("star-space-tile.png");

    
        shared_ptr<Mesh> cubeAnim =  AssetDatabase::getAsset<Mesh>("cubeSkel_Anim.fbx");
    
    //    vector<glm::vec3> fbxNonDup = fbxMesh->getNonDuplicateMeshVertex();
    //
    //    for(int i = 0; i < fbxNonDup.size(); i++)
    //    {
    //        cout << i << " " << fbxNonDup[i]<< endl;
    //    }
    //
    //    vector<glm::vec3> hullTest = {
    //        glm::vec3(0,0,0), //p0
    //        glm::vec3(0,1,0), //p1
    //        glm::vec3(1,1,0), //p2
    //        glm::vec3(1,0,0), //p3
    //        glm::vec3(0,0,1), //p4
    //        glm::vec3(1,0,1), //p5
    //        glm::vec3(1,1,1), //p6
    //        glm::vec3(0,1,1), //p7
    //        //glm::vec3(0.5f,2,0.5f), //p8
    //        //glm::vec3(0.5f,-1,0.5f), //p9
    //        glm::vec3(2.0f,0.5f,0.5f), //p8
    //    //    glm::vec3(2,0 ,1)
    //    }; //p9
    //
    //    vector<int> usedIndex;
    //    vector<int> usedTris;
    //
    //    convexHull(fbxNonDup, usedIndex, usedTris);
    //
    //    shared_ptr<Mesh> tryMesh = AssetDatabase::createMesh(fbxNonDup,usedIndex,usedTris);
    //
    
    
    shared_ptr<Shader> diffuseShader = AssetDatabase::createShader("LightShader", CommonData("vsLight.vs"), CommonData("fsLight.fragmentshader"));
    shared_ptr<Shader> unlitShader = AssetDatabase::createShader("UnlitShader", CommonData("vsUnlit.vs"), CommonData("fsUnlit.fragmentshader"));
    //shared_ptr<Shader> s = AssetDatabase::createShader(CommonData("vsLight.vs"),CommonData("fsNoLight.fragmentshader"));
    
    shared_ptr<Material> defaultMaterial = AssetDatabase::createMaterial("DefaultMaterial", diffuseShader);
    defaultMaterial->setParamVec4("_diffuseColor", glm::vec4(1,1,1,1));
    
    shared_ptr<Material> spaceShipMaterial = AssetDatabase::createMaterial("SpaceShipMaterial", diffuseShader);
    spaceShipMaterial->setParamTexture("_textureSampler", spaceShipTexture);
    spaceShipMaterial->setParamVec4("_diffuseColor", glm::vec4(1,1,1,1));
    spaceShipMaterial->setParamVec2("_offset", glm::vec2(0,0));
    
    shared_ptr<Material> spaceBKGMaterial = AssetDatabase::createMaterial("SpaceBKGMaterial", diffuseShader);
    spaceBKGMaterial->setParamTexture("_textureSampler", spaceBKGTexture);
    spaceBKGMaterial->setParamVec4("_diffuseColor", glm::vec4(1,1,1,1));
    spaceBKGMaterial->setParamVec2("_offset", glm::vec2(0,0));
    
    shared_ptr<Material> fontMaterial = AssetDatabase::createMaterial("FontMaterial", unlitShader);
    fontMaterial->setParamTexture("_textureSampler", font->getFontTexture());
    fontMaterial->setParamVec4("_difuseColor", glm::vec4(1, 1, 1,1));
    
    
    shared_ptr<Editor> editor = make_shared<Editor>();
    editor->init();
    
    shared_ptr<Game> game = make_shared<Game>();
    game->init();
    {
		
        
        /** SHIP WITH ROOT CHILDREN **/
        //		shared_ptr<Actor> spaceShipRoot = Factory::CreateActor("SpaceShipRoot");// , meshRenderer1);
        //
        //        shared_ptr<Actor> spaceShipChildren = Factory::CreateActor("SpaceShipChildren");
        //
        //        shared_ptr<MeshFilter> meshFilter = spaceShipChildren->AddComponent<MeshFilter>();
        //        meshFilter->setMesh(spaceShipMesh);
        //        shared_ptr<MeshRenderer> meshRenderer =spaceShipChildren->AddComponent<MeshRenderer>();
        //        meshRenderer->setMaterial(spaceShipMaterial);
        //
        //        spaceShipChildren->transform->setRotation(glm::quat(glm::vec3(90*Deg2Radian,0,-90*Deg2Radian)));
        //
        //        spaceShipChildren->transform->setScale(glm::vec3(2,2,2));
        //
        //        spaceShipRoot->addChildren(spaceShipChildren);
        /** END SHIP WITH ROOT CHILDREN **/
        
        shared_ptr<Actor> spaceShipRoot = Factory::CreateActor("SpaceShipRoot");// , meshRenderer1);
        shared_ptr<MeshFilter> meshFilter = spaceShipRoot->AddComponent<MeshFilter>();
        meshFilter->setMesh(spaceShipMesh);
        shared_ptr<MeshRenderer> meshRenderer = spaceShipRoot->AddComponent<MeshRenderer>();
        meshRenderer->setMaterial(spaceShipMaterial);
        spaceShipRoot->AddComponent<RigidBody>();
        shared_ptr<Collider> collider = spaceShipRoot->AddComponent<SphereCollider>();
        collider->setPhysicsMaterial(bouncyPhysMaterial);
        
		//fbxTest->transform->setScale(glm::vec3(10,10,10));
		//    fbxTest->transform->setRotationQuat(glm::quat(glm::vec3(45 * Deg2Radian, 45 * Deg2Radian, 45 * Deg2Radian)));
        //		shared_ptr<MeshFilter> meshFilter = spaceShipRoot->AddComponent<MeshFilter>();
        
		//meshFilter->mesh = dynamic_pointer_cast<Mesh>(objMesh);
        //		meshFilter->setMesh(spaceShipMesh);
        //		shared_ptr<MeshRenderer> meshRenderer = spaceShipRoot->AddComponent<MeshRenderer>();
        //		meshRenderer->setMaterial(spaceShipMaterial);
        
        
        
        //		shared_ptr<RigidBody> rigidBody = spaceShipRoot->AddComponent<RigidBody>();
        
        //        rigidBody->setConstraintsFlags((int)TransformConstraintAxis::MoveLockY);
        
        //        spaceShipRoot->AddComponent<PlayerScript>();
//        spaceShipRoot->transform->setPosition(glm::vec3(1,0,0));
        /*	rigidBody->setRotateEnabled(TransformAxis::x, false);
         rigidBody->setRotateEnabled(TransformAxis::y, false);
         rigidBody->setRotateEnabled(TransformAxis::z, false);
         rigidBody->setGravity(true);
         */
        //		shared_ptr<Collider> collider = spaceShipRoot->AddComponent<SphereCollider>();
        //		collider->setPhysicsMaterial(bouncyPhysMaterial);
		
		//rigidBody->setMoveEnabled(TransformAxis::y, false);
		//    rigidBody->setMoveEnabled(TransformAxis::z, false);
		//        rigidBody->setMoveEnabled(TransformAxis::x, false);
        
		//     rigidBody->setRotateEnabled(TransformAxis::x, false);
		//     rigidBody->setRotateEnabled(TransformAxis::y, false);
		//     rigidBody->setRotateEnabled(TransformAxis::z, false);
        
        
		//fbxTest->AddComponent<RigidBody>();
		//fbxTest->AddComponent<SphereCollider>();
		//fbxTest->AddComponent<AddForceScript>();
		//fbxTest->AddComponent<SphereCollider>();
        
        //		shared_ptr<Actor> floor = Factory::CreateActor("Floor");
        //
        //		meshFilter = floor->AddComponent<MeshFilter>();
        //		floor->transform->setPosition(glm::vec3(0, -4, -2));
        //		//floor->transform->setRotationQuat(glm::quat(glm::vec3(0, 0, 45 * Deg2Radian)));
        //		floor->transform->setScale(glm::vec3(5, 0.1f, 5.0f));
        //		meshFilter->setMesh(cubeMesh);
        //		meshRenderer = floor->AddComponent<MeshRenderer>();
        //		meshRenderer->setMaterial(defaultMaterial);
        //        collider = floor->AddComponent<BoxCollider>();
        //		collider->setPhysicsMaterial(bouncyPhysMaterial);
        
//        shared_ptr<Actor> background = Factory::CreateActor("Background");
//        
//		shared_ptr<MeshFilter> meshFilter = background->AddComponent<MeshFilter>();
//		background->transform->setPosition(glm::vec3(0, 0, -2));
//		background->transform->setScale(glm::vec3(2.0f, 2.0f, 0.1f));
//        meshFilter->setMesh(cubeMesh);
//		shared_ptr<MeshRenderer> meshRenderer = background->AddComponent<MeshRenderer>();
//		meshRenderer->setMaterial(spaceBKGMaterial);
        
        
        		shared_ptr<Actor> fontTest = Factory::CreateActor("FontTest");// , meshRenderer1);
    		shared_ptr<FontMesh> fontMesh = fontTest->AddComponent<FontMesh>();
        		fontMesh->setFont(font);
        		fontMesh->setText("hey there mate!");
        		shared_ptr<MeshRenderer> fontMeshRenderer = fontTest->AddComponent<MeshRenderer>();
        		fontMeshRenderer->setMaterial(fontMaterial);
        
        // START ACTOR SE/DESERIALIZATION AND CLONE
        
        //
        //        ActorDescription desc = Factory::getActorDescription(spaceShipRoot);
        //
        //        //save data to archive
        //        {
        //            // create and open a character archive for output
        //            std::ofstream ofs(CommonData("spaceShipRootDesc"));
        //
        //            boost::archive::text_oarchive oa(ofs);
        //            // write class instance to archive
        //            ActorDescription desc = Factory::getActorDescription(spaceShipRoot);
        //
        //            oa & desc;
        //
        //
        //            //oa & game->world;
        //            // archive and stream closed when destructors are called
        //        }
        //
        //        ActorDescription desc2;// =
        //        //load data from archive
        //        {
        //            // create and open a character archive for output
        //            std::ifstream ifs(CommonData("spaceShipRootDesc"));
        //
        //
        //            boost::archive::text_iarchive ia(ifs);
        //
        //            ia & desc2;
        //
        //            //oa & game->world;
        //            // archive and stream closed when destructors are called
        //        }
        //
        //
        //
        //        shared_ptr<Actor> actorCopy = Factory::DeserializeActor(desc);
        //        actorCopy->name = "SpaceShipRoot (Copy)";
        //
        //        actorCopy->transform->setPosition(glm::vec3(3,0,0));
        //
        
        // END ACTOR SE/DESERIALIZATION AND CLONE
        
        //            fontTest->AddComponent<PlayerScript>();
        
        
		//    int bla = 0;
		//    //while(bla == 0)
		//    for(int i = 0; i < fbxNonDup.size(); i++)
		//    {
		//        stringstream ss;
		//        ss.append("point");
		//        ss.append(i);
		//        fbxTest = Factory::CreateActor(ss);// , meshRenderer1);
		//    //fbxTest->transform->setScale(glm::vec3(10,10,10));
		//        //fbxTest->transform->setScale(glm::vec3(0.5f,0.5f,0.5f));
		//        fbxTest->transform->setPosition(glm::vec3(0,0,1));
		//     //fbxTest->transform->setRotationQuat(glm::quat(glm::vec3(-90 * Math::Deg2Radian, 0, 0)));
		//        shared_ptr<MeshFilter> meshFilter = fbxTest->AddComponent<MeshFilter>();
		//        //meshFilter->mesh = dynamic_pointer_cast<Mesh>(objMesh);
		//        meshFilter->mesh = objMesh;
		//            shared_ptr<MeshRenderer> meshRenderer = fbxTest->AddComponent<MeshRenderer>();
		//        meshRenderer->material = m;
		//
		//        bla++;
		//    }
        
		//    shared_ptr<MeshFilter> meshFilter = fbxTest->AddComponent<MeshFilter>();
		//    //meshFilter->mesh = dynamic_pointer_cast<Mesh>(objMesh);
		//    meshFilter->mesh = tryMesh;
		//    shared_ptr<MeshRenderer> meshRenderer = fbxTest->AddComponent<MeshRenderer>();
		//    meshRenderer->material = m;
		//    fbxTest->AddComponent<RigidBody>();
		//    fbxTest->AddComponent<BoxCollider>();
        
        
        
        
        
		//    floor->AddComponent<RotateOverTime>();
		//    floor->AddComponent<RigidSta>();
        
        
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
		myCamera->transform->setRotation(glm::quat(glm::vec3(0, 180 * Deg2Radian, 0)));
		myCamera->AddComponent<Camera>();
        //		myCamera->AddComponent<EditorCameraControl>();
        
////        /******* SCENE SERIALIZATION ****/
////        vector<ActorDescription> sceneDesc = Factory::getSceneDescription(game->world);
//        
//        //save data to archive
//        {
//            // create and open a character archive for output
//            std::ofstream ofs(CommonData("sceneDesc"));
//            
//            boost::archive::text_oarchive oa(ofs);
//            
//            
//            oa & spaceShipRoot;
//            
//            //            oa & sceneDesc;
//            
//            
//            //oa & game->world;
//            // archive and stream closed when destructors are called
//        }
////        /******* END SCENE SERIALIZATION ****/
////        
////        
////        
////        Factory::DestroyActor(spaceShipRoot);
//        
//        shared_ptr<Actor> actorDeserialized;
//        //save data to archive
//        {
//            // create and open a character archive for output
//            std::ifstream ifs(CommonData("sceneDesc"));
//            
//            boost::archive::text_iarchive ia(ifs);
//            
//            
//            ia & actorDeserialized;
//            
//            actorDeserialized->initComponents();
//            
//            cout << "bla" << endl;
//            
//            //            oa & sceneDesc;
//            
//            
//            //oa & game->world;
//            // archive and stream closed when destructors are called
//        }
//        Factory::ActorDeserialized(actorDeserialized);
//
//        actorDeserialized->name = "Copy";
//        actorDeserialized->transform->setPosition(glm::vec3(2,0,0));
	}
    
    
    
    /******* SCENE DESERIALIZATION ****/
    //    vector<ActorDescription> sceneDesc;
    //
    //    //load data from archive
    //    {
    //        // create and open a character archive for output
    //        std::ifstream ifs(CommonData("sceneDesc"));
    //
    //
    //        boost::archive::text_iarchive ia(ifs);
    //
    //        ia & sceneDesc;
    //
    //    }
    //
    //    Factory::loadSceneDescription(sceneDesc);
    /******* END SCENE DESERIALIZATION ****/
    
    editor->world->awake();
    game->world->awake();
    
    while (!glfwWindowShouldClose(GraphicsSystem::getInstance()->getWindow().get())) {
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
    GraphicsSystem::getInstance()->shutdown();
	SoundSystem::getInstance()->shutdown();
    
    
	return 0;
}	
