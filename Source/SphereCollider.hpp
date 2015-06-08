#pragma once

#include "Collider.hpp"

/** SphereCollider uses a sphere as the volume collider. Can either be real physics simulated or trigger only. */
class SphereCollider :

public Collider
#ifdef GUINITY_DEBUG
, public StaticCounter<SphereCollider>
#endif
{
private:
	/** The radius of the Sphere */
	float radius;
    
public:
	/** Default Constructor*/
	SphereCollider();
	/** Deserialization Constructor*/
    SphereCollider(float radius, PxVec3 center);
	/** Default Destructor*/
	virtual ~SphereCollider();
	
	/** radius Getter
     @return radius of the sphere */
	float getRadius();
	/** radius Setter
     @param [in] newRadius the radius of the sphere */
	void setRadius(float newRadius);
    
	/** Init component override. Create a new Sphere Shape in the PhysX scene. */
	virtual void init();
	
    /** Clones current component (Prototype Design Pattern)
     @return shared_ptr to cloned SphereCollider Component
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

