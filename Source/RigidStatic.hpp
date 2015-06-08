#pragma once
#include "Component.hpp"
#include <PxPhysics.h>
#include "Subject.hpp"
using namespace physx;

/** RigidStatic is the component that adds real physics simulation to an Actor. It's static and can be moved by the Game but will never be moved due to physics simulation */
class RigidStatic : public Subject<RigidStatic>,
public Component
{
private:
    /** The PhysX RigidBody */
   	PxRigidDynamic* physxRigidStatic;
    
    
    
public:
    /** Default Constructor */
	RigidStatic();
    /** Default Destructor */
	virtual ~RigidStatic();
    
    /** Component init override. Creates a RigidDynamic body in the PhysX scene and sets it as Kinematic by default */
	virtual void init() override;
    /** Component destroy override. Releases the RigidDynamic body */
    virtual void destroy() override;
    /** Component tick override. Updates the PhysX scene with the Actor transform
     @param [in] deltaSeconds last frame duration */
	virtual void tick(float deltaSecods) override;
    /** Component setActive override. Disables visualization and physics simulation in the PhysX scene */
	virtual void setActive(bool isActive) override;
    
    /** physxRigidBody getter
     @return pointer to PhysX RigidBody*/
    PxRigidDynamic* getRigidDynamic();
    
    
    /** Clones current component (Prototype Design Pattern)
     @return shared_ptr to cloned RigidStatic Component
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

