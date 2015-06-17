#pragma once

#include "Module.hpp"
#include <vector>
#include "Transform.hpp"

//class Transform;
class Component;

/** Actor
 
 Actor is the base Game Object. Since GUInity is a component-based engine, the idea is NOT to inherit from
 Actor to create new behaviours. On the contrary, every game object in the world should be an Actor and their behaviour
 should come from different Components.
 
 */
class Actor : public std::enable_shared_from_this<Actor>
#ifdef GUINITY_DEBUG
// Allow for instance counting when using the GUINITY_DEBUG macro
, public StaticCounter<Actor>
#endif

{
    
public:
	/** An actor can admit two states, active or not active. Non-active actors disable all their components, increasing overall performance */
	bool isActive;
	/** editorFlag indicates if this actor belongs to the Editor realm */
	bool editorFlag;
    
public:
	/** Default Constructor */
    Actor() {}
	/** Constructor with actor name */
	Actor(string name);
    
    /** Disable move constructor */
    Actor ( Actor && ) = delete;
    
	/** Default Destructor */
	virtual ~Actor();
    

    
	/** Name of the Actor */
	string name;
    
    /** Sets the components for this actor. Only used on deserialization of Actors 
     @param components The components that will be added to the actor 
     */
    void setComponents(vector<shared_ptr<Component>> components);
	
	/** Transform of the Actor. By default every Actor has a transform. For further improvements, it could be
     considered to treat Transform as any other component*/
	shared_ptr<Transform> transform;
	
	/** The components of the Actor */
	vector<shared_ptr<Component>> components;
    
	/** Awake. This function is called to Awake all the components attached to the actor */
	void awake();
	/** Function called every frame. Calls tick for each Component attached to the actor 
     @param deltaSeconds Duration of last frame
     */
	void tick(float deltaSeconds) ;
    
	/** Function that receives Collision from PhysX. Delegates the collision to all ScriptComponents.
     @param[in] actor Other actor that collided with this
     */
	void triggerPhysxCollision(shared_ptr<Actor> actor);
	
	/** Function that receives Trigger Collision from PhysX.  Delegates the collision to all ScriptComponents.
     @param[in] actor Other actor that collided with this
     */
	void triggerPhysxTrigger(shared_ptr<Actor> actor);
    
	/** Parent actor. Allows for hierarchy. */
	weak_ptr<Actor> parent;
	/** Parent setter
     @param[in] parent The parent actor
     */
	void setParent(shared_ptr<Actor> parent);
	/** Parent getter
     @return pointer to actor or nullptr
     */
	const shared_ptr<Actor> getParent() const;
    
	
	/** All the Actors that are children of this. */
	vector<weak_ptr<Actor>> children;
	/** Add children to list 
     @param[in] child Actor to be added as child
     */
	void addChild(shared_ptr<Actor> child);
    
    
	/** isActive Setter. Triggers setActive with the same state for every component and children.
     @param isActive true if Actor should be active, false otherwise
     */
	void setActive(bool isActive);
	/** isActive Getter
     @return true if Actor is active, false otherwise
     */
    bool getIsActive() const;
    
	/** editorFlat Setter 
     @param isEditor true if this Actor belongs to the Editor World
     */
	void setEditorFlag(bool isEditor);
	/** editorFlat Getter
     @return true if this Actor belongs to the Editor World
     */
    bool getEditorFlag() const;
    
    
	/** Initialize all the components attached to the actor */
    void initComponents();
    
	/** Attaches an existing component to the Actor. This function is used for deserialization of Actors */
	void addComponent(shared_ptr<Component> component);
    
    /** Destroy this Actor and all of the children Actor components, called when Actor is destroyed */
    void destroyComponents();
    
    /** Clones the actor, all its components and children recursively 
     @return Reference to the cloned Actor
     */
     shared_ptr<Actor> clone();
    
	/** Adds a Component and initialize it
     @return Reference to the added Component
     */
	template <typename T>
	shared_ptr<T> AddComponent()
	{
		shared_ptr<T> component = make_shared<T>();
		component->setActor(shared_from_this());
		components.push_back(component);
		component->init();
        
        
		return component;
	}
    
    /** Get the first Component of the Actor that matches the type
     @return Reference to the Component
     */
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
