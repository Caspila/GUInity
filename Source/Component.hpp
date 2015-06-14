#pragma once

#include "Module.hpp"
#include "SerializationStructs.hpp"

class Actor;

/** Component is the very basis of the engine. All the actor behaviour should come from a component
 Component-based game engines allow for small, modular classes that are reused very often.
 Component behaviour can vary from custom ScriptComponent (custom behaviour) to RigidBody physics and MeshRenderer.
 A Component can only exist in conjunction with an actor.
 Component is an abstract class and is the parent of all Components.
 */
class Component : public enable_shared_from_this<Component>
{
    
public:
	/** Reference to the actor that owns this component */
	weak_ptr<Actor> actor;
    
protected:
    /** Used when been deserialized or cloned*/
	bool initWithData;

    
    /** Is component active */
    bool isActive;
    
    
    
public:
    
	/** Default Constructor*/
	Component();
	/** Default Destructor. Virtual because is parent class*/
	virtual ~Component();
    
	/** Initializes the component. Initialization should not be done in constructor due to enable_shared_from_this<T> inheritance. */
	virtual void init() { this->isActive = true;};
	/** Destroys Component and release any component-specific members */
	virtual void destroy() {};
    
    /*  Sets the Component as active or not active
     @param isActive - true to activate, false to deactivate
     */
	virtual void setActive(bool isActive) { this->isActive = isActive; };
	/** Called by Actor owner when it's first awaken */
	virtual void awake() {};
    
	
    /** Called by actor every frame
     @param [in] deltaSeconds - last frame duration
     */
	virtual void tick(float deltaSecods) {};
	
    /** Used when been deserialized or cloned
     @param [in] initWithData true if this component data will come from clone of deserialization, false if it's a new component being creates
     */
    void setCopyMode(bool initWithData);
    
	/** Getter for owner Actor
     @return shared_ptr for the owner */
	shared_ptr<Actor> getActor();
	/** Setter for owner Actor
     @param owner Actor*/
	void setActor(weak_ptr<Actor> actor);

    /** isActive Getter
     @return true if Component is Active, false otherwise */
    bool getIsActive();
	/** isActive Setter
     @param[in] true if Component should be Active, false otherwise */
	void setIsActive(bool isActive);
    
    /** Pure virtual function. Clones current component (Prototype Design Pattern)
     @return shared_ptr to cloned Component
     */
	virtual shared_ptr<Component> clone() = 0;
    
    
    /** @defgroup serialization_functions Serialization Functions
     *  !TODO! SERIALIZATION IS NOT WORKING PROPERLY AT THE MOMENT
     *  Every component should inherit the following functions to allow for serialization/
     *  deserialization of actors
     *  @{
     */
#pragma region Serialization Functions
    
    
	/** Creates a description for the Component */
	virtual shared_ptr<ComponentDescription> getComponentDescription() = 0;
    /** Deserializes a description to a Component */
    virtual void deserialize(shared_ptr<ComponentDescription> desc) = 0;
    
#pragma endregion
    /** @} */ // end of serialization_functions
    
#ifdef GUINITY_DEBUG
	static int count;
#endif
};

