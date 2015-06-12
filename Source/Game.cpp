#include "Game.hpp"
#include "Time.hpp"
#include "Physics.hpp"
#include "GraphicsSystem.hpp"
#include "Camera.hpp"
#include "MeshRenderer.hpp"

shared_ptr<World> Game::world;

Game::Game()
{
	//camera = make_shared<Camera>(0.3f, 100.0f, 45, 4.0f / 3);
	//camera->transform->setPosition(glm::vec3(0, 0, 10));

	//Camera::addObserver(shared_from_this());

}


Game::~Game()
{
	//Camera::removeObserver(shared_from_this());
}


void Game::init()
{
	world = make_shared<World>();
	world->init();
	world->registerObserverAsGame();

	//shared_ptr<Game> game = shared_from_this();
	//Camera::addObserver(shared_from_this());
	//Light::addObserver(shared_from_this());
	//MeshRenderer::addObserver(shared_from_this());
	//Camera::addObserver(shared_from_this());
}

void Game::shutdown()
{
	world->shutdown();
	//Camera::removeObserver(shared_from_this());
}

void Game::update(float deltaSeconds)
{
	//camera->computeModelViewMatrix();

	world->tick(deltaSeconds);

	Physics::tickScene(world->physicsScene);
    Physics::updateActorsTransform(world->physicsScene);

//	Physics::updateActorsTransform(world->physicsScene);

	GraphicsSystem::getInstance()->clear();

    
//    Time::stopwatchStart();
    
    if(world->cameras.size()>0)
    {
        GraphicsSystem::getInstance()->render(world->cameras[0],world->meshRenderers,world->lights);
//    cout << "Render time:" << Time::stopwatchEnd() << endl;
    
	//GraphicsSystem::getInstance().render(world->cameras[0], );
        GraphicsSystem::getInstance()->render(world->cameras[0], world->physicsScene->getRenderBuffer(), glm::vec4(1, 1, 1,1));
    }
//	GraphicsSystem::getInstance().render(camera, world.lights);
	
	GraphicsSystem::getInstance()->swap();
}

//void Game::onNotify(EventType type, shared_ptr<Component> component, bool isEditor)
//{
//
//}