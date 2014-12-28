#include "Factory.hpp"
#include "Actor.hpp"
#include "Transform.hpp"
//#include "Script.hpp"
#include "ScriptComponent.hpp"

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

	notify(EventType::NewActor, actor);

	return actor;
}

shared_ptr<Actor> Factory::CreateEditorActor(string name)
{
	shared_ptr<Actor> actor = make_shared<Actor>(name);
	actor->transform->setActor(actor);

	actor->setEditorFlag(true);

	notify(EventType::NewEditorActor, actor);

	return actor;
}