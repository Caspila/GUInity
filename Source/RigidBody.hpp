#pragma once

#include "Module.hpp"
#include "Component.hpp"
#include <PxPhysicsAPI.h>
#include "Subject.hpp"

using namespace physx;

/** RigidBody is the component that adds real physics simulation to an Actor. It's dynamic and directly influences in the Transform of the Actor due to physics simulation */
class RigidBody : public Subject<RigidBody>,
public Component

#ifdef GUINITY_DEBUG
, public StaticCounter<RigidBody>
#endif
{
private:
    
    /** The PhysX RigidBody */
	PxRigidBody* physxRigidBody;
    
    /** Is movement locked in the X axis? */
    bool lockMoveX;
    /** Is movement locked in the Y axis? */
    bool lockMoveY;
    /** Is movement locked in the Z axis? */
    bool lockMoveZ;
    
    /** Is rotation locked in the X axis? */
    bool lockRotateX;
    /** Is rotation locked in the X axis? */
    bool lockRotateY;
    /** Is rotation locked in the X axis? */
    bool lockRotateZ;
    /** Is the object being simulated using physics */
    bool isKinematic;
    /** Is the object affected by gravity? */
    bool gravityEnabled;
    
public:
    /** Default Constructor */
	RigidBody();
    /** Default Destructor */
	virtual ~RigidBody();
    
    
    /** Component init override. Creates a RigidDynamic body in the PhysX scene */
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
	PxRigidBody* getRigidbody();
	
    /** isKinematic setter
     @param true if physics should be not be simulated, false if it should */
	void setKinematic(bool isKinematic);
    /** isKinematic getter
     @return true if physics is being simulated, false if it's not */
    bool getKinematic();
    
    /** gravity setter
     @param [in] enabled true if gravity is enabled, false otherwise */
	void setGravity(bool enabled);
    /** gravity getter
     @return true if gravity is enabled, false otherwise */
	bool getGravity();
    
    /** Allow or constrain translation in one of the 3 axis
     @param [in] axis one of the 3 axis (X,Y,Z)
     @param [in] true to allow, false to constrain */
    void setMoveEnabled(TransformAxis axis, bool enabled);
    /** Allow or constrain rotation in one of the 3 axis
     @param [in] axis one of the 3 axis (X,Y,Z)
     @param [in] true to allow, false to constrain */
    void setRotateEnabled(TransformAxis axis, bool enabled);
    
    
    /** Update the transform based on the PhysX physics simulation and current constraints
     @param [in] the PhysX transform*/
    void updateTransform(const PxTransform& transform);
    
    
    /** Add force to the RigidBody
     @param [in] the force that will be added (direction and magnitude)
     */
    void addForce(glm::vec3 force);
    

    
    /** Clones current component (Prototype Design Pattern)
     @return shared_ptr to cloned RigidBody Component
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

