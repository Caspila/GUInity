#pragma once

#include "Module.hpp"
#include "Actor.hpp"
#include "Subject.hpp"
#include "Serialization2.hpp"
#include <map>
//#include "Player.h"

class Script;
class MeshRenderer;

class Factory : public Subject<Factory>
{
public:
	Factory();
	~Factory();
    
    
    
	static shared_ptr<Actor> CreateActor(string name);
	static shared_ptr<Actor> CreateEditorActor(string name);
    
    static void notifyNewActorCreated(Actor& actor);
    
    static void CreateReferenceActor(shared_ptr<Actor> realActor);
    
    static void DeserializeComponents(shared_ptr<Actor> actor, vector<shared_ptr<ComponentDescription>> compDescs);
    
    static shared_ptr<Actor> DeserializeActor(ActorDescription& desc);

    static vector<shared_ptr<Component>> prototypes;
    
};


