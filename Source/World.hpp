#pragma once

#include <vector>
#include "Actor.hpp"
#include "Light.hpp"
#include "Observer.hpp"
#include "Camera.hpp"

class MeshRenderer;


/** World is a container of Actors. It also keeps track of objects that are important for game simulation and rendering such as lights and cameras.
 
 The World also has a PhysX scene to allow for physics simulation */
class World : public Observer, public enable_shared_from_this<World>

{
private:

    /** Awakes a range of Actors in the world */
    void awake(unsigned long start, unsigned long end);
	
    
public:
    
    /** Default Constructor */
	World();
    /** Default Destructor */
	~World() {}
    
    /** Is the world awake? */
	bool isAwake;
    /** Does this World belong to the Editor */
	bool isEditor;
    /** The PhysX scene */
   	PxScene *physicsScene;

    
    /** Initializes the physics scene */
	void init();
    /** Releases any alocated memory */
	void shutdown();
    
    /** The MeshRenderers of the world */
	std::vector<shared_ptr<MeshRenderer>> meshRenderers;
    /** Adds a MeshRenderer to the meshRenderers vector
     @param[in] meshRenderer The MeshRenderer to be added*/
	void addMeshRenderer(shared_ptr<MeshRenderer> meshRenderer);
    /** Removes a MeshRenderer from the meshRenderers vector
     @param[in] meshRenderer The MeshRenderer to be removed */
  	void removeMeshRenderer(shared_ptr<MeshRenderer> meshRenderer);
	
    /** The Cameras of the world */
	std::vector<shared_ptr<Camera>> cameras;
    /** Adds a Camera to the cameras vector
     @param[in] camera The Camera to be added*/
    void addCamera(shared_ptr<Camera> camera);
    /** Removes a Camera from the cameras vector
     @param[in] camera The Camera to be removed*/
    void removeCamera(shared_ptr<Camera> camera);
	
    /** The Lights of the world */
	std::vector<shared_ptr<Light>> lights;
    /** Adds a Light to the lights vector
     @param[in] light The Light to be added*/
	void addLight(shared_ptr<Light> light);
    /** Removes a Light from the lights vector
     @param[in] light The Light to be removed*/
   	void removeLight(shared_ptr<Light> light);
    
    /** The Actors of the world */
	std::vector<shared_ptr<Actor>> actors;
    /** The Actors to be added in the next tick */
    std::vector<shared_ptr<Actor>> newActors;
    /** The Actors to be removed in the next tick */
	std::vector<weak_ptr<Actor>> toRemoveActors;
    
    /** Adds an Actor to the world
     @param[in] actor The Actor to be added*/
	void addActor(shared_ptr<Actor> actor);
    /** Adds an Actor to the world in the next "tick" loop
     @param[in] actor The Actor to be added*/
    void addActorDelayed(shared_ptr<Actor> actor);
    /** Awakes the actors that were added with delay and move them to the actors vector  */
	void transferNewActors();
    
    /** Removes an Actor from the world
     @param[in] actor The Actor to be removed*/
	void removeActor(shared_ptr<Actor> actor);
    /** Removes an Actor from the world in the next "tick" loop"
     @param[in] actor The Actor to be removed*/
    void removeActorDelayed(shared_ptr<Actor> actor);
    /** Removes the actors that were marked to be removed with delay */
    void removeDestroyedActors();
    
    /** Finds an Actor in the World given a name
     @param[in] name The name of the Actor to be found. Returns the first one that matches the name or nullptr in case none was found */
	shared_ptr<Actor> findActor(string name);
	
    /** Awakes the World and every Actor in it */
	void awake();
    /** Ticks the World and every Actor in it */
    void tick(float deltaTime);

    /** Register the World to as Observers to Subjects that are important for the Game */
	void registerObserverAsGame()  ;
    /** Register the World to as Observers to Subjects that are important for the Editor */
	void registerObserverAsEditor();

    /** Receive Component notifications from Subjects that this World is observing */
	virtual void onNotify(ComponentEventType type, shared_ptr<Component> component, bool isEditor) override;
    /** Receive Actor notifications from Subjects that this World is observing */
	virtual void onNotify(ActorEventType type, shared_ptr<Actor> actor, bool isEditor) override;
 

};

