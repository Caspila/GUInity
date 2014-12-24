#include "Actor.hpp"
#include "Script.hpp"
//#include "ScriptComponent.h"
#include "Transform.hpp"
#include "print.hpp"

Actor::Actor(string name, shared_ptr<MeshRenderer> meshRenderer	)
{
	
	transform = make_shared<Transform>();

	this->meshRenderer = meshRenderer;

	this->name = name;

#ifdef GUINITY_DEBUG
	nCount++;
#endif
}

Actor::~Actor()
{
#ifdef GUINITY_DEBUG
	nCount--;
	cout << "Actor "<< name << " destroyed (" << nCount << " remaining)" << endl;
#endif
	
}

void Actor::awake()
{
	for (int i = 0; i < scriptComponents.size(); i++)
	{
		shared_ptr<ScriptComponent> scriptComponent = scriptComponents[i];
		scriptComponent->awake();
	}
}

void Actor::tick(float deltaSeconds)
{
	for (int i = 0; i < scriptComponents.size(); i++)
	{
		shared_ptr<ScriptComponent> scriptComponent = scriptComponents[i];
		//ScriptComponent& scriptComponent = scriptComponents[i];

		//shared_ptr<Actor> actor = scriptComponent.actor.lock();
		//if (actor)
		//{
		//scriptComponent.script->tick(scriptComponent.actor, deltaSeconds);
		scriptComponent->tick(deltaSeconds);

		//}



		//scriptComponent->tick(scr a,deltaSeconds);
	}

	//if (transform->rigidBody.expired())
	//	cout << transform->rigidBody.expired();

	//shared_ptr<PxRigidBody> rigidBodyLock = transform->rigidBody.lock();
	if (transform->rigidBody != nullptr)
	{
		transform->rigidBody->setGlobalPose(transformToPhysXTransform(transform));
	}
}