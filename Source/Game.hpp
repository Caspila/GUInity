#pragma once

#include "Module.hpp"
#include <PxPhysics.h>
#include "World.hpp"
#include "Observer.hpp"

using namespace physx;

class Camera;

class Game : public enable_shared_from_this<Game>
{
public:


    
    /** The Editor World */
	static shared_ptr<World> world;
    
    /** Initalize the editor. Creates the Scene camera and the Transform handles to manipulate the Actors */
	void init();
        /** Releases any allocated memory */
	void shutdown();
    /** "Ticks" the Game. Simulates the Physics, Ticks Actors and Renders on screen
     @param[in] deltaSeconds Duration of last frame
     */
    	void update(float deltaSeconds);

};

