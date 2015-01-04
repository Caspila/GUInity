#include "Actor.hpp"
//#include "Script.hpp"
//#include "ScriptComponent.h"
#include "Transform.hpp"
#include "print.hpp"

Actor::Actor(string name)// , shared_ptr<MeshRenderer> meshRenderer	)
{
	
	transform = make_shared<Transform>();

	//this->meshRenderer = meshRenderer;

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
	for (int i = 0; i < components.size(); i++)
	{
		shared_ptr<Component> component = components[i];
		component->awake();
	}
}

void Actor::tick(float deltaSeconds)
{
	for (int i = 0; i < components.size(); i++)
	{
		shared_ptr<Component> component = components[i];
		//ScriptComponent& scriptComponent = scriptComponents[i];

		//shared_ptr<Actor> actor = scriptComponent.actor.lock();
		//if (actor)
		//{
		//scriptComponent.script->tick(scriptComponent.actor, deltaSeconds);
		component->tick(deltaSeconds);

		//}



		//scriptComponent->tick(scr a,deltaSeconds);
	}

	//if (transform->rigidBody.expired())
	//	cout << transform->rigidBody.expired();

	//shared_ptr<PxRigidBody> rigidBodyLock = transform->rigidBody.lock();
	//if (transform->rigidBody != nullptr)
	//{
	//	transform->rigidBody->setGlobalPose(transformToPhysXTransform(transform));
	//}
}

void Actor::triggerPhysxCollision(Actor* actor)//string name)
{
	for (auto& x : components)
	{
		shared_ptr<ScriptComponent> scriptComponent = dynamic_pointer_cast<ScriptComponent> (x);

		if (scriptComponent)
			scriptComponent->onCollision(actor);
	}
}
void Actor::triggerPhysxTrigger(Actor* actor)
{
	for (auto& x : components)
	{
		shared_ptr<ScriptComponent> scriptComponent = dynamic_pointer_cast<ScriptComponent> (x);

		if (scriptComponent)
			scriptComponent->onTrigger(actor);
	}
}

void Actor::setParent(shared_ptr<Actor> parent)
{
	this->parent = parent;
}
void Actor::addChildren(shared_ptr<Actor> children)
{
	this->children.push_back(children);
	children->setParent(shared_from_this());
}

void Actor::setActive(bool isActive)
{
	for (auto& x : components)
	{
		x->setActive(isActive);
	}
	for (auto& x : children)
	{
		auto ptrLock = x.lock();
		if (ptrLock)
			ptrLock->setActive(isActive);
	}


}

void Actor::initComponents()
{
  	for (auto& x : components)
	{
		x->init();
	}
}


shared_ptr<Actor> Actor::getParent()
{
	shared_ptr<Actor> parentLock = parent.lock();
	return parentLock;
}

void Actor::setEditorFlag(bool isEditor)
{
	editorFlag = isEditor;
}