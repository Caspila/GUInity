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

	This class is responsible for creating new actors. Actors should not be created by hand, but using the Factory instead.
	This class also holds the model of each Component for the Prototype Design Pattern. 
*/

class Factory : public Subject<Factory>
{
private:
	/**  The model of each Component for the Prototype Design Pattern. */
	static vector<shared_ptr<Component>> prototypes;

    static TransformDescription getTransformDescription(shared_ptr<Transform> t);
    static vector<shared_ptr<ComponentDescription>> getActorComponentsDescription(shared_ptr<Actor> actor);
    
	/** Deserialize a list of Components and attaches them to an Actor */
    static void DeserializeComponents(shared_ptr<Actor> actor, vector<shared_ptr<ComponentDescription>> compDescs);
    
public:
	/** Default Constructor*/
	Factory() {}
	/** Default Destructory*/
	~Factory() {}
    
	/** Create a new Actor */
	static shared_ptr<Actor> CreateActor(string name);
    
    /** Destroys an Actor */
    static void DestroyActor(weak_ptr<Actor> actor);
    
	/** Create reference actor. Every Actor in the Game World has a Reference Actor in the Editor World to allow them to be manipulated */
	static void CreateReferenceActor(shared_ptr<Actor> realActor);
	/** Create a new Editor Actor, one that lives only in the Editor World */
	static shared_ptr<Actor> CreateEditorActor(string name);

	/** Deserialize an Actor*/
    static shared_ptr<Actor> DeserializeActor(ActorDescription& desc);
    
    static ActorDescription getActorDescription(shared_ptr<Actor> actor);

    static vector<ActorDescription> getSceneDescription(shared_ptr<World> world);

    static void loadSceneDescription(vector<ActorDescription> sceneDesc);
    
};


