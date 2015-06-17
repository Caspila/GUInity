#include "Game.hpp"
#include "Time.hpp"
#include "Physics.hpp"
#include "GraphicsSystem.hpp"
#include "Camera.hpp"
#include "MeshRenderer.hpp"
#include "Input.hpp"

    /** The Editor World */
shared_ptr<World> Game::world;


    /** Initalize the editor. Creates the Scene camera and the Transform handles to manipulate the Actors */
void Game::init()
{
	world = make_shared<World>();
	world->init();
	world->registerObserverAsGame();

}

        /** Releases any allocated memory */
void Game::shutdown()
{
	world->shutdown();

}

/** "Ticks" the Game. Simulates the Physics, Ticks Actors and Renders on screen
 @param[in] deltaSeconds Duration of last frame
 */
void Game::update(float deltaSeconds)
{
    // Tick the Actors
	world->tick(deltaSeconds);

    // Tick the Physics
	Physics::tickScene(deltaSeconds,world->physicsScene);

    // Enables/Disables Physics render debug
    if(Input::getKeyPressed(GLFW_KEY_B))
    {
        Physics::toggleDebugVisualization(world->physicsScene);
    }
    
    // Render the Game World
	GraphicsSystem::getInstance()->clear();
    
    if(world->cameras.size()>0)
    {
        GraphicsSystem::getInstance()->render(world->cameras[0],world->meshRenderers,world->lights);
        GraphicsSystem::getInstance()->renderPhysicsDebug(world->cameras[0], world->physicsScene->getRenderBuffer(), glm::vec4(1, 1, 1,1));
    }
	
	GraphicsSystem::getInstance()->swap();
}

