#pragma once
#include "Collider.hpp"
#include "Enums.hpp"

/** CapsuleCollider is a volume collider with radius, height and orientation. Can either be real physics simulated or trigger only. */
class CapsuleCollider :
	public Collider
#ifdef GUINITY_DEBUG
, public StaticCounter<CapsuleCollider>
#endif
{
private:
	/** The orientation of the Capsule (X,Y,Z) */
	RotateAxis orientation;
	/** The height of the Capsule (half) */
	float halfHeight;
	/** The radius of the Capsule */
	float radius;
public:
	/** Default Constructor*/
	CapsuleCollider();
	/** Deserialization Constructor*/
    CapsuleCollider(RotateAxis orientation, float halfHeight, float radius,PxVec3 center);
	/** Default Destructor*/
	~CapsuleCollider();

	/** orientation Setter*/
	void setOrientation(RotateAxis orientation);
	/** orientation Getter*/
	RotateAxis getOrientation() const;

	/** height Setter*/
	void setHeight(float height);
	/** height Getter*/
	float getHeight() const;

	/** radius Setter*/
	void setRadius(float radius);
	/** radius Getter*/
	float getRadius() const;

	/** Component init override. Create a new Capsule Shape in the PhysX scene. */
	virtual void init();

    /** Looks for a MeshComponent and gets the extent for the collider */
    virtual void recalculateBounds() override;
	
    /** Clones current component (Prototype Design Pattern)
     @return shared_ptr to cloned CapsuleCollider Component
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


