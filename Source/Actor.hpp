#pragma once

#include "Module.hpp"
#include <vector>
#include "Transform.hpp"

//class Transform;
class Component;

/** Actor 

	Actor is the base Game Object. Since GUInity is a component-based engine, the idea is NOT to inherit from
	Actor to create new behaviours. On the contrary, every game object in the world should be an Actor and their behaviour
	should come from different components.

*/
class Actor : public std::enable_shared_from_this<Actor>
#ifdef GUINITY_DEBUG
	// Allow for instance counting when using the GUINITY_DEBUG macro
, public StaticCounter<Actor>
#endif

{

private:
	/** An actor can admit two states, active or not active. Non-active actors disable all their components, increasing overall performance */
	bool isActive;
	/** editorFlag indicates if this actor belongs to the Editor realm */
	bool editorFlag;

public:
	/** Default Constructor */
    Actor() {}
	/** Constructor with actor name */
	Actor(string name);
	/** Default Destructor */
	virtual ~Actor();

    shared_ptr<Actor> clone();
    
	/** Name of the Actor */
	string name;
	
	/** Transform of the Actor. By default every Actor has a transform. For further improvements, it could be
	considered to treat Transform as any other component*/
	shared_ptr<Transform> transform;
	
	/** The components of the Actor, may vary from Collider to Script */
	vector<shared_ptr<Component>> components;

	/** Awake. This function is called to Awake all the components attached to the actor */
	void awake();
	/** Tick. Function called every frame. This function is responsible for calling the Tick for each Component attached to the actor */
	void tick(float deltaSeconds) ;

	/** Function that receives Collision from PhysX
	@actor - Other actor that collided with this
	*/
	void triggerPhysxCollision(Actor* actor);
	
	/** Function that receives Trigger Collision from PhysX
	@actor - Other actor that collided with this
	*/
	void triggerPhysxTrigger(Actor* actor);

	/** Parent. Actors can have parent to create hierarchy. Hierarchy is important to group several Actors into one */
	/** Weak_ptr because we don't want this object to prevent an Actor to be destroyed */
	weak_ptr<Actor> parent;
	/** Parent getter */
	shared_ptr<Actor> getParent();
	/** Parent setter */
	void setParent(shared_ptr<Actor> parent);

	
	/** Children. All the Actors that are children of this. */
	/** Weak_ptr because we don't want this object to prevent an Actor to be destroyed */
	vector<weak_ptr<Actor>> children;
	/** Add children to list */
	void addChildren(shared_ptr<Actor> children);


	/** isActive setter */
	void setActive(bool isActive);
	/** isActive getter */
	bool getIsActive();

	/** editorFlat setter */
	void setEditorFlag(bool isEditor);
	/** editorFlat getter */
	bool getEditorFlag();


	/** initComponents. This function is called to Initialize all the components attached to the actor */
    void initComponents();

	/** addComponent. Attaches an existing component to the actor. This function is used for deserialization of Actors */
	void addComponent(shared_ptr<Component> component);

    
    void destroyComponents();
    
	/** Generic AddComponent. This function creates a smart pointer to the desired component and returns it*/
	template <typename T>
	shared_ptr<T> AddComponent()
	{
		shared_ptr<T> component = make_shared<T>();
		component->setActor(transform->actor);
		components.push_back(component);
		component->init();
        

		return component;
	}

	/** Generic GetComponent. This function looks for a component of the desired type from the components list and returns the first it finds */
	template <typename T>
	shared_ptr<T> GetComponent()
	{
		for (auto& x : components)
		{
			shared_ptr<T> wantedComponent = dynamic_pointer_cast<T> (x);

			if (wantedComponent)
				return wantedComponent;
		}

		return nullptr;
	}


};
