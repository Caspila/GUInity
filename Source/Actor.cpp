#include "Actor.hpp"
#include "Transform.hpp"
#include "print.hpp"
#include "ScriptComponent.hpp"
#include "Factory.hpp"

/** Constructor with actor name */
Actor::Actor(string name) : name(name), isActive(true)
{
	transform = make_shared<Transform>();
    
	// Memory Management check - Increment Counter by 1
#ifdef GUINITY_DEBUG
	nCount++;
#endif
}

/** Default Destructor */
Actor::~Actor()
{
	// Memory Management check - Decrease Counter by 1
#ifdef GUINITY_DEBUG
	nCount--;
	cout << "Actor "<< name << " destroyed (" << nCount << " remaining)" << endl;
#endif
	
}

/** Awake. This function is called to Awake all the components attached to the actor */
void Actor::awake()
{
	for (int i = 0; i < components.size(); i++)
	{
		shared_ptr<Component> component = components[i];
		component->awake();
	}
}

/** Tick. Function called every frame. This function is responsible for calling the Tick for each Component attached to the actor */
void Actor::tick(float deltaSeconds)
{
	// Only tick active actors
    if(!isActive)
        return;

	for (int i = 0; i < components.size(); i++)
	{
		shared_ptr<Component> component = components[i];

		component->tick(deltaSeconds);

	}

}

/** Function that receives Collision from PhysX
@actor - Other actor that collided with this

Delegates the collision to all ScriptComponents. Trying to emulate Unity, where every script can contain code to handle Collision
*/
void Actor::triggerPhysxCollision(Actor* actor)
{
	for (auto& x : components)
	{
		shared_ptr<ScriptComponent> scriptComponent = dynamic_pointer_cast<ScriptComponent> (x);

		if (scriptComponent)
			scriptComponent->onCollision(actor);
	}
}

/** Function that receives Trigger Collision from PhysX
@actor - Other actor that collided with this

Delegates the collision to all ScriptComponents. Trying to emulate Unity, where every script can contain code to handle Collision
*/
void Actor::triggerPhysxTrigger(Actor* actor)
{
	for (auto& x : components)
	{
		shared_ptr<ScriptComponent> scriptComponent = dynamic_pointer_cast<ScriptComponent> (x);

		if (scriptComponent)
			scriptComponent->onTrigger(actor);
	}
}

/** Parent setter */
void Actor::setParent(shared_ptr<Actor> parent)
{
	this->parent = parent;
}
/** Parent getter */
shared_ptr<Actor> Actor::getParent()
{
	shared_ptr<Actor> parentLock = parent.lock();
	return parentLock;
}

/** Add children to list */
void Actor::addChildren(shared_ptr<Actor> children)
{
	this->children.push_back(children);
	children->setParent(shared_from_this());
  
    children->setActive(isActive);
}

/** isActive setter */
void Actor::setActive(bool isActive)
{
    this->isActive = isActive;
    
	// Deactivate all components
	for (auto& x : components)
	{
		x->setActive(isActive);
	}
	// Deactivate all children
	for (auto& x : children)
	{
		auto ptrLock = x.lock();
		if (ptrLock)
			ptrLock->setActive(isActive);
	}


}

/** isActive getter */
bool Actor::getIsActive()
{
	return isActive;
}

/** editorFlag setter */
void Actor::setEditorFlag(bool isEditor)
{
	editorFlag = isEditor;
}

/** editorFlag setter */
bool Actor::getEditorFlag()
{
	return editorFlag;
}

/** initComponents. This function is called to Initialize all the components attached to the actor */
void Actor::initComponents()
{
  	for (auto& x : components)
	{
		x->init();
	}
}




/** addComponent. Attaches an existing component to the actor. This function is used for deserialization of Actors */
void Actor::addComponent(shared_ptr<Component> component)
{
    component->setActor(shared_from_this());
    components.push_back(component);
    component->init();
}

void Actor::destroyComponents()
{
  	for (auto& x : components)
	{
        x->destroy();
    }
    
    for (auto& x : children)
	{
		auto ptrLock = x.lock();
		if (ptrLock)
            ptrLock->destroyComponents();
	}
}

shared_ptr<Actor> Actor::clone()
{
    shared_ptr<Actor> newActor = Factory::CreateActor(name+"(Clone)");
    
    newActor->transform->setPosition(transform->getPosition());
    newActor->transform->setScale(transform->getScale());
    newActor->transform->setRotationQuat(transform->getRotationQuat());
    
  	for (auto& x : components)
	{
        newActor->addComponent(x->clone());
    }
    
	for (auto& x : children)
	{
		auto ptrLock = x.lock();
		if (ptrLock)
            newActor->addChildren(ptrLock->clone());
	}
    
    return newActor;
}
