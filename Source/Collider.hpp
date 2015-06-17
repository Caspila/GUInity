#pragma once
#include "Component.hpp"
#include <PxPhysics.h>
#include "Physics.hpp"

class PhysicsMaterial;

using namespace physx;

/** Collider is a component that adds either simulates real physics for an Actor or allows it to behave like a volume trigger.
 Collider is an abstract parent class for all the Collider types (SphereCollider, BoxCollider, CapsuleCollider and MeshCollider) */
class Collider :
public Component
{
protected:
	/** The center of the collider */
	PxVec3 center;
	/** The PhysX Shape of the collider */
	PxShape* shape;
    
	/** The physics material that determines the behaviour of the physics shape */
	shared_ptr<PhysicsMaterial> physicsMaterial;
    
    /** Is this collider a trigger or should it simulate real world physics? */
    bool isTrigger;
    /** Is this collider used for queries only? */
    bool isQueryOnly;
    
public:
	/** Default Constructor */
	Collider() { shape = nullptr; isTrigger = false; isQueryOnly = false; };
	/** Default Destructor. Virtual because it's parent class */
	virtual ~Collider() {};
    

    /** Looks for a MeshComponent and gets the extent for the collider */
    virtual void recalculateBounds() = 0;
    
    
    
    /** center setter
     @param [in] center the center of the physics shape */
	void setCenter(PxVec3 center);
	/** center getter
     @return center of the physics shape
     */
	PxVec3 getCenter() const;
    
	/** isTrigger setter
     @param [in] isTrigger - true if it's just a trigger, false if it physics simulated */
	void setIsTrigger(bool isTrigger);
	/** isTrigger getter
     @return true if it's just a trigger, false if it physics simulated
     */
	bool getIsTrigger() const;
    
	/** isQueryOnly getter
     @param [in] queryOnly true if this object is only used in queries, false otherwise */
	void setQueryOnly(bool isQueryOnly);
	/** isQueryOnly getter
     @return true if this object is only used in queries, false otherwise
     */
	bool getQueryOnly() const;
    
    /** physicsMaterial getter
     @param [in] reference to PhysicsMaterial */
	void setPhysicsMaterial(const shared_ptr<PhysicsMaterial> physMaterial);
	/** physicsMaterial getter
     @return referente to PhysicsMaterial */
	shared_ptr<PhysicsMaterial> getPhysicsMaterial() const;
    
    /** Component init override */
	virtual void init() override;
    /** Component destroy override */
    virtual void destroy() override;
    
	/** Component awake override */
	virtual void awake() override{ Component::awake(); }
	/** Component setActive override. Changes PhysX settings */
    virtual void setActive(bool isActive) override;
    

    
    /** Pure virtual function. Clones current component (Prototype Design Pattern)
        @return shared_ptr to cloned Collider Component
     */
	virtual shared_ptr<Component> clone() override = 0;
    
    /** @defgroup serialization_functions Serialization Functions
     *  Serialization Region
     *  @{
     */
#pragma region Serialization Functions
    
	/** Creates a description for the Component*/
	virtual shared_ptr<ComponentDescription> getComponentDescription() override = 0;
    /** Deserializes a description to a Component */
    virtual void deserialize(shared_ptr<ComponentDescription> desc) override = 0;
    
#pragma endregion
    /** @} */ // end of serialization_functions
    
};

