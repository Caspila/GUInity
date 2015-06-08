#pragma once

#include "Collider.hpp"

/** BoxCollider is an AABB collider Component. Can either be real physics simulated or trigger only. */
class BoxCollider : public Collider
#ifdef GUINITY_DEBUG
, public StaticCounter<BoxCollider>
#endif
{
private:
	/** The extents of the AABB (half) */
	PxVec3 halfExtent;
public:
	/** Default Constructor */
	BoxCollider();
	/** Deserialization Constructor */
    BoxCollider(PxVec3 halfExtent, PxVec3 center = PxVec3(0,0,0));
	/** Default Destructor*/
	virtual ~BoxCollider();
    
    /** Init component override. Create a new Box Shape in the PhysX scene. */
	virtual void init();
    
    
    /** Clones current component (Prototype Design Pattern)
     @return shared_ptr to cloned BoxCollider Component
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
    virtual void deserialize(shared_ptr<ComponentDescription> desc)  override;
    
#pragma endregion
    /** @} */ // end of serialization_functions
    
};

