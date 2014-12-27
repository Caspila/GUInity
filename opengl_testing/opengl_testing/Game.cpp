#include "Game.hpp"
#include "Time.hpp"
#include "Physics.hpp"
#include "GraphicsSystem.hpp"
#include "Camera.hpp"
#include "MeshRenderer.hpp"

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
	//shared_ptr<Game> game = shared_from_this();
	Camera::addObserver(shared_from_this());
	Light::addObserver(shared_from_this());
	MeshRenderer::addObserver(shared_from_this());
	//Camera::addObserver(shared_from_this());
}

void Game::shutdown()
{
	Camera::removeObserver(shared_from_this());
}

void Game::update(shared_ptr<World> world, float deltaSeconds)
{
	//camera->computeModelViewMatrix();

	world->tick(deltaSeconds);

	Physics::tick();
	Physics::updateActorsTransform();

	GraphicsSystem::getInstance().clear();

	GraphicsSystem::getInstance().render(world->cameras[0],world->meshRenderers,world->lights);
//	GraphicsSystem::getInstance().render(camera, world.lights);
	
	GraphicsSystem::getInstance().swap();
}

void Game::onNotify(EventType type, shared_ptr<Component> component)
{

}