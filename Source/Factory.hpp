#pragma once

#include "Module.hpp"
#include "Subject.hpp"
#include "Serialization2.hpp"
#include <map>

class Actor;
class Script;
class MeshRenderer;

/** Actor Factory 

	This class is responsible for creating new actors. Actors should not be created by hand, but using the Factory instead.
	This class also holds the model of each Component for the Prototype Design Pattern. 
*/

class Factory : public Subject<Factory>
{
private:
	/**  The model of each Component for the Prototype Design Pattern. */
	static vector<shared_ptr<Component>> prototypes;

public:
	/** Default Constructor*/
	Factory() {}
	/** Default Destructory*/
	~Factory() {}
    
	/** Create a new Actor */
	static shared_ptr<Actor> CreateActor(string name);
	/** Create reference actor. Every Actor in the Game World has a Reference Actor in the Editor World to allow them to be manipulated */
	static void CreateReferenceActor(shared_ptr<Actor> realActor);
	/** Create a new Editor Actor, one that lives only in the Editor World */
	static shared_ptr<Actor> CreateEditorActor(string name);
    
	/** Deserialize a list of Components and attaches them to an Actor */
    static void DeserializeComponents(shared_ptr<Actor> actor, vector<shared_ptr<ComponentDescription>> compDescs);
	/** Deserialize an Actor*/
    static shared_ptr<Actor> DeserializeActor(ActorDescription& desc);

    
};


