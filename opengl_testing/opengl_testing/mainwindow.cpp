#include "mainwindow.h"
#include "ui_mainwindow.h"


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

#include <qtimer.h>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);


}

MainWindow::~MainWindow()
{
    physics.shutdown();

    editor->shutdown();

    game->shutdown();

    // close GL context and any other GLFW resources
    GraphicsSystem::getInstance()->shutdown();

    delete ui;
}

void MainWindow::init()
{
    Input input(GraphicsSystem::getInstance()->window);

    physics.init();

    engineMode = EngineMode::game;

    editor = make_shared<Editor>();
    editor->init();

    game = make_shared<Game>();
    game->init();

    AssetDatabase::init();

    shared_ptr<Mesh> fbxMesh = AssetDatabase::createMeshFromFBX("box.fbx");
    fbxMesh->setScaleFactor(0.1f);

    shared_ptr<Asset> objMesh = AssetDatabase::createMeshFromOBJ("sphere.obj");

    // create and open a character archive for output
    std::ofstream ofs(CommonData("filename"));

    shared_ptr<Shader> s = AssetDatabase::createShader(CommonData("vsLight.vs"),CommonData("fsLight.fragmentshader"));

    shared_ptr<Material> m = AssetDatabase::createMaterial(s);

     shared_ptr<Actor> fbxTest = Factory::CreateActor("FBXTest");// , meshRenderer1);
     fbxTest->transform->setPosition(glm::vec3(0, 0, 0));
     fbxTest->transform->setRotationQuat(glm::quat(glm::vec3(-90 * Math::Deg2Radian, 0, 0)));


    shared_ptr<MeshFilter> meshFilter = fbxTest->AddComponent<MeshFilter>();
    meshFilter->mesh = dynamic_pointer_cast<Mesh>(objMesh);
    shared_ptr<MeshRenderer> meshRenderer = fbxTest->AddComponent<MeshRenderer>();
    meshRenderer->material = m;
    fbxTest->AddComponent<RigidBody>();
    fbxTest->AddComponent<BoxCollider>();


    //fbxTest = nullptr;


 //   shared_ptr<World> testWorld = game->world;

 //   shared_ptr<RigidBody> rigidBody = fbxTest->AddComponent<RigidBody>();
    // save data to archive
    {
        boost::archive::text_oarchive oa(ofs);
        // write class instance to archive
        oa & AssetDatabase::idToAsset;
        oa & AssetDatabase::currentID;

        //oa & rigidBody;
        //oa & fbxTest;
//        oa & fbxTest->components;

        ActorDescription desc = getActorDescription(fbxTest);

        oa & desc;
        vector<shared_ptr<ComponentDescription>> compDescs = getActorComponentsDescription(fbxTest);
        oa & compDescs;

        //oa & game->world;
        // archive and stream closed when destructors are called
    }
  //  exit(0);


    //Actor x;
    shared_ptr<Actor> serializeTest;
    {
        // create and open an archive for input
        std::ifstream ifs(CommonData("filename"),std::fstream::binary | std::fstream::in);
        boost::archive::text_iarchive ia(ifs);
        // read class state from archive
        //ia >> objLoad;
        ia & AssetDatabase::idToAsset;
        ia & AssetDatabase::currentID;
    //    ia & testWorld;
        //ia & fbxTest;
        //ia & x;
        //ia & testWorld;

       // ia & game->world;

        ActorDescription desc;// = getActorDescription(*fbxTest);

        ia & desc;

        serializeTest = Factory::DeserializeActor(desc);

        vector<shared_ptr<ComponentDescription>> compDescs;
        ia & compDescs;

        Factory::DeserializeComponents(serializeTest,compDescs);
    }

    shared_ptr<Asset> loadedObjMesh = dynamic_pointer_cast<Mesh>(AssetDatabase::idToAsset[1]);///AssetDatabase::createMeshFromOBJ("sphere.obj");

     shared_ptr<Shader> loadedShader = dynamic_pointer_cast<Shader>(AssetDatabase::idToAsset[2]);///

    shared_ptr<Material> loadedMaterial = dynamic_pointer_cast<Material>(AssetDatabase::idToAsset[3]);///

    shared_ptr<MeshFilter> meshFilter2 = serializeTest->AddComponent<MeshFilter>();
    meshFilter2->mesh = dynamic_pointer_cast<Mesh>(loadedObjMesh);
    shared_ptr<MeshRenderer> meshRenderer2 = serializeTest->AddComponent<MeshRenderer>();
    meshRenderer2->material = loadedMaterial;

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


    int timerInterval = 0;
    this->timer = new QTimer();
    QObject::connect(timer, SIGNAL(timeout()), this, SLOT(tick()));
    timer->start( timerInterval );
}

void MainWindow::tick()
{
    Time::frameStart();

    Input::updateInputState();

    editor->update(Time::deltaTime,game->world);

    //cout << "Tick" << endl;
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
