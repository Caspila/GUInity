#include "Actor.h"
#include "Script.h"

Actor::Actor(string name, shared_ptr<MeshRenderer> meshRenderer	)
{

	transform = make_shared<Transform>();

	this->meshRenderer = meshRenderer;

	this->name = name;
}

Actor::~Actor()
{
	cout << "Destroying Actor: " << name << endl;
}

void Actor::tick(float deltaSeconds)
{
	for (int i = 0; i < scriptComponents.size(); i++)
	{
		ScriptComponent& scriptComponent = scriptComponents[i];

		scriptComponent.script->tick(scriptComponent.actor, deltaSeconds);
		//scriptComponent->tick(scr a,deltaSeconds);
	}
}