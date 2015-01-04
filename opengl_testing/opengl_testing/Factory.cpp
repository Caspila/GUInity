#include "Factory.hpp"
#include "Actor.hpp"
#include "Transform.hpp"
//#include "Script.hpp"
#include "ScriptComponent.hpp"
#include "RigidStatic.hpp"
#include "SphereCollider.hpp"
#include "EditorCollider.hpp"

Factory::Factory()
{
}


Factory::~Factory()
{
}


shared_ptr<Actor> Factory::CreateActor(string name)//, shared_ptr<MeshRenderer> meshRenderer)
{
	shared_ptr<Actor> actor = make_shared<Actor>(name);
	actor->transform->setActor(actor);

	actor->setEditorFlag(false);

	//notify(ActorEventType::NewActor, actor, false);

    CreateReferenceActor(actor);

	return actor;
}

void Factory::CreateReferenceActor(shared_ptr<Actor> realActor)
{
    notify(ActorEventType::NewActor, realActor, false);
    
    shared_ptr<Actor> editorRef = CreateEditorActor(string(realActor->name).append("___editorRef"));
	shared_ptr<EditorCollider> editorCollider = editorRef->AddComponent<EditorCollider>();
	editorCollider->setGameActor(realActor);
	editorRef->AddComponent<SphereCollider>();
}

shared_ptr<Actor> Factory::CreateEditorActor(string name)
{
	shared_ptr<Actor> actor = make_shared<Actor>(name);
	actor->transform->setActor(actor);

	actor->setEditorFlag(true);

	notify(ActorEventType::NewActor, actor, true);

	return actor;
}


void Factory::notifyNewActorCreated(Actor& actor)
{
    //CreateReferenceActor(actor);
}