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

/** Function called every frame. Calls tick for each Component attached to the actor
 @param deltaSeconds Duration of last frame
 */
void Actor::tick(float deltaSeconds)
{
	// Only tick active actors
    if(!isActive)
        return;
    
	for (int i = 0; i < components.size(); i++)
	{
		shared_ptr<Component> component = components[i];

        if(component->getIsActive())
            component->tick(deltaSeconds);
        
	}
    
}

/** Function that receives Collision from PhysX. Delegates the collision to all ScriptComponents.
 @param[in] actor Other actor that collided with this
 */
void Actor::triggerPhysxCollision(shared_ptr<Actor> actor)
{
	for (auto& x : components)
	{
		shared_ptr<ScriptComponent> scriptComponent = dynamic_pointer_cast<ScriptComponent> (x);
        
		if (scriptComponent)
			scriptComponent->onCollision(actor);
	}
}

/** Function that receives Trigger Collision from PhysX.  Delegates the collision to all ScriptComponents.
 @param[in] actor Other actor that collided with this
 */
void Actor::triggerPhysxTrigger(shared_ptr<Actor> actor)
{
	for (auto& x : components)
	{
		shared_ptr<ScriptComponent> scriptComponent = dynamic_pointer_cast<ScriptComponent> (x);
        
		if (scriptComponent)
			scriptComponent->onTrigger(actor);
	}
}

/** Parent setter
 @param[in] parent The parent actor
 */
void Actor::setParent(shared_ptr<Actor> parent)
{
	this->parent = parent;
}
/** Parent getter
 @return pointer to actor or nullptr
 */
const shared_ptr<Actor> Actor::getParent() const
{
	shared_ptr<Actor> parentLock = parent.lock();
	return parentLock;
}

/** Add children to list
 @param[in] child Actor to be added as child
 */
void Actor::addChild(shared_ptr<Actor> children)
{
    
	this->children.push_back(children);
    
    
	children->setParent(shared_from_this());
    children->setActive(isActive);
    
}

/** isActive Setter. Triggers setActive with the same state for every component and children.
 @param isActive true if Actor should be active, false otherwise
 */
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

/** isActive Getter
 @return true if Actor is active, false otherwise
 */
bool Actor::getIsActive() const
{
	return isActive;
}

/** editorFlat Setter
 @param isEditor true if this Actor belongs to the Editor World
 */
void Actor::setEditorFlag(bool isEditor)
{
	editorFlag = isEditor;
}

/** editorFlat Getter
 @return true if this Actor belongs to the Editor World
 */
bool Actor::getEditorFlag() const
{
	return editorFlag;
}

/** Initialize all the components attached to the actor */
void Actor::initComponents()
{
    
  	for (auto& x : components)
	{
		x->init();
	}
}

/** Sets the components for this actor. Only used on deserialization of Actors
 @param components The components that will be added to the actor
 */
void Actor::setComponents(vector<shared_ptr<Component>> components)
{
    this->components = std::move(components);
    
    for(auto&x : this->components)
    {
        x->actor = shared_from_this();
    }
}


/** Attaches an existing component to the Actor. This function is used for deserialization of Actors
 @param[in] component The component that will be added to this actor */
void Actor::addComponent(shared_ptr<Component> component)
{
    component->setActor(shared_from_this());
    components.push_back(component);
    component->init();
}


/** Destroy this Actor and all of the children Actor components, called when Actor is destroyed */
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

/** Clones the actor, all its components and children recursively
 @return Reference to the cloned Actor
 */
shared_ptr<Actor> Actor::clone()
{
    shared_ptr<Actor> newActor = Factory::CreateActor(name+"(Clone)");
    
    newActor->transform->setPosition(transform->getPosition());
    newActor->transform->setScale(transform->getScale());
    newActor->transform->setRotation(transform->getRotation());
    
  	for (auto& x : components)
	{
        newActor->addComponent(x->clone());
    }
    
	for (auto& x : children)
	{
		auto ptrLock = x.lock();
		if (ptrLock)
            newActor->addChild(ptrLock->clone());
	}
    
    return newActor;
}
