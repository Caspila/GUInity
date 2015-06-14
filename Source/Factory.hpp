#pragma once

#include "Module.hpp"
#include "Subject.hpp"
#include "Serialization2.hpp"
#include <map>


class Actor;
class Script;
class MeshRenderer;
class World;

/** Actor Factory 

	This class is responsible for creating and destroying actors. Actors should not be created by hand, but using the Factory instead.
	This class also holds the model of each Component for the Prototype Design Pattern. 
*/

class Factory : public Subject<Factory>
{
private:
	/**  The model of each Component for the Prototype Design Pattern. */
	static vector<shared_ptr<Component>> prototypes;

    /** Gets a ActorDescription from an Actor
     @param[in] actor The Actor
     @return ActorDescription
     */
    static ActorDescription getActorDescription(shared_ptr<Actor> actor);
    
    /** Gets a TransformDescription from a Transform
     @param[in] transform The Transform
     @return TransformDescription
     */
    static TransformDescription getTransformDescription(shared_ptr<Transform> transform);
    
    /** Gets a list of ComponentDescriptions for each Component in an Actor
     @param[in] actor The Actor
     @return list of ComponentDescriptions
     */
    static vector<shared_ptr<ComponentDescription>> getActorComponentsDescription(shared_ptr<Actor> actor);
    
	/** Deserialize a list of Components and attaches them to an Actor
     @param[in] actor Actor that will receive the Components
     @param[in] compDescs List of ComponentDescription
     */
    static void DeserializeComponents(shared_ptr<Actor> actor, vector<shared_ptr<ComponentDescription>> compDescs);
    
    
    
public:
	/** Default Constructor*/
	Factory() {}
	/** Default Destructory*/
	~Factory() {}
    
	/** Create a new Actor 
     @param[in] name Name of the Actor
     @return Reference to the Actor that was created
     */
	static shared_ptr<Actor> CreateActor(string name);
    
    /** Destroys an Actor 
     @param[in] actor Reference to the actor to be destroyed
     */
    static void DestroyActor(weak_ptr<Actor> actor);
    
	/** Create reference actor. Every Actor in the Game World has a Reference Actor in the Editor World to allow them to be manipulated in the Editor
     @param[in] realActor Reference to the actor
     */
	static void CreateReferenceActor(shared_ptr<Actor> realActor);
	/** Create a new Editor Actor, one that lives only in the Editor World 
     @param[in] name Name of the Actor
     @return Reference to the Editor Actor
     */
	static shared_ptr<Actor> CreateEditorActor(string name);

	/** Deserialize an Actor
     @param[in] desc The ActorDescription
     @return The deserialized Actor
     */
    static shared_ptr<Actor> DeserializeActor(ActorDescription& desc);
    


    /** Gets a list of ActorDescription from a World. Technically it could be used for describing a scene.
     @param[in] world The World
     @return list of ActorDescription
     */
    static vector<ActorDescription> getSceneDescription(shared_ptr<World> world);

    /** Loads a scene description, deserializing every ActorDescription into new Actors.
     @param[in] sceneDesc The list of ActorDescription
     */
    static void loadSceneDescription(vector<ActorDescription> sceneDesc);

    /** Notifies when an Actor has been deserialized.
     @param[in] actor The Actor that was deserialized
     */
    static void ActorDeserialized(shared_ptr<Actor> actor);
    
};


