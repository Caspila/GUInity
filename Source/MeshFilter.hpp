#pragma once
#include "ScriptComponent.hpp"
#include "Component.hpp"
#include <PxPhysicsAPI.h>
#include "MeshComponent.hpp"



using namespace physx;


class Component;

/** MeshFilter makes reference to a Mesh. It's used in combination with MeshRenderer to render a Mesh on screen */
class MeshFilter :
	public MeshComponent
{
public:
    /** Default Constructor */
	MeshFilter();
    /** Default Destructor. Virtual because it's child class. */
	virtual ~MeshFilter();

    /** Clones current component (Prototype Design Pattern)
     @return shared_ptr to cloned MeshFilter Component
     */
    virtual shared_ptr<Component> clone() override;
    
    /** @defgroup serialization_functions Serialization Functions
     *  Serialization Region
     *  @{
     */
#pragma region Serialization Functions
    
	/** Creates a description for the Component*/
	virtual shared_ptr<ComponentDescription> getComponentDescription() override;
    /** Deserializes a description to a Component */
    virtual void deserialize(shared_ptr<ComponentDescription> desc) override;
    
#pragma endregion
    /** @} */ // end of serialization_functions

        
};

