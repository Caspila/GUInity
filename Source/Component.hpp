#pragma once

#include "Module.hpp"
#include "SerializationStructs.hpp"

class Actor;

/** Component is the very basis of the engine. All the actor behaviour should come from a component 
	Component-based game engines allow for small, modular classes that are reused very often.
	Component behaviour can vary from custom ScriptComponent (Custom behaviour) to RigidBody physics and MeshRenderer.
	A component can only exist in conjunction with an actor.
	Component class is supposed to be the parent for all Components.
*/
class Component : public enable_shared_from_this<Component>
//#ifdef GUINITY_DEBUG
//	:public StaticCounter<Component>
//#endif
{

protected:
    /** Used when been deserialized or cloned*/
	bool initWithData;
    /** Used when been deserialized or cloned*/
    void setCopyMode(bool initWithData);
    
private:
	/** All components should be tied to a actor */
	weak_ptr<Actor> actor;


    
public:

	/** Default Constructor*/
	Component();
	/** Default Destructor. Virtual because is parent class*/
	virtual ~Component();

    
    
	/** Functions that should be inheritted if needed */
	/** sets the component as active or not active */
	virtual void setActive(bool isActive) {};
	/** Called when actor is first awaken */
	virtual void awake() {};
	/** Called when actor is initialized */
	virtual void init() {};
	/** Called by actor every frame */
	virtual void tick(float deltaSecods) {};
	
	/** getter for Actor */
	shared_ptr<Actor> getActor();
	/** setter for Actor */
	void setActor(weak_ptr<Actor> actor);
    

	/** TODO. SERIALIZATION IS NOT WORKING PROPERLY AT THE MOMENT */
	/** Every component should inherit the following functions to allow for serialization/deserialization of actors */
	/** Creates a description for the Component*/
	virtual shared_ptr<ComponentDescription> getComponentDescription() { return make_shared<ComponentDescription>();};
	/** Clone current component. Prototype Design Pattern*/
	virtual shared_ptr<Component> clone() { shared_ptr<Component> compClone = make_shared<Component>();return compClone;};
	/** Deserializes a description to a Component */
    virtual void deserialize(shared_ptr<ComponentDescription> desc) {};
    
#ifdef GUINITY_DEBUG
	static int count;
#endif
};

