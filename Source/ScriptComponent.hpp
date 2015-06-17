#pragma once
#include "Module.hpp"
//#include "Script.hpp"
#include "Component.hpp"

class Actor;
//class Script;


/** ScriptComponent is a Component that allows for Custom Behaviour. For example the controller of a space ship, a manager or anything that needs its own specific rules. */
class ScriptComponent: public Component
#ifdef GUINITY_DEBUG
	, public StaticCounter<ScriptComponent>
#endif
{
public:

    /** Default Constructor */
	ScriptComponent();

    /** Default Destructor */
	virtual ~ScriptComponent();

    /** Component init override */
	virtual void init() {};
    /** Component destroy override */
	virtual void destroy() {};
    
    /** Component awake override */
	virtual void awake() override {} ;
    /** Component tick override 
     @param [in] deltaSeconds last frame durations */
	virtual void tick(float deltaSecods) override {};

    /** Callback function called when a collision occurs */
	virtual void onCollision(shared_ptr<Actor> actor) {};
    /** Callback function called when a trigger collision occurs */
	virtual void onTrigger(shared_ptr<Actor> actor) {};

    /** Clones current component (Prototype Design Pattern)
     @return shared_ptr to cloned ScriptComponent Component
     */
    virtual shared_ptr<Component> clone() override;
    
    
    /** @defgroup serialization_functions Serialization Functions
     *  Serialization Region
     *  @{
     */
#pragma region Serialization Functions
    
	/** Creates a description for the Component*/
	virtual shared_ptr<ComponentDescription> getComponentDescription() override {return nullptr;}
    /** Deserializes a description to a Component */
    virtual void deserialize(shared_ptr<ComponentDescription> desc) override {};
    
#pragma endregion
    /** @} */ // end of serialization_functions
private:
	//ScriptComponent();
};

