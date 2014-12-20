#include "ScriptComponent.h"

ScriptComponent::ScriptComponent(shared_ptr<Script> script, shared_ptr<Actor> actor)
{
	this->script = script;
	this->actor = actor;
}


ScriptComponent::~ScriptComponent()
{
}
