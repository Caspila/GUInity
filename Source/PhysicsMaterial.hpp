#pragma once
#include "Module.hpp"
#include "Asset.hpp"
#include <PxPhysics.h>

using namespace physx;

/** PhysicsMaterial is an Asset that encapsulates a PhysX PxMaterial allowing for multiple PxShapes to reference the same Physics Material */
class PhysicsMaterial : public Asset
#ifdef GUINITY_DEBUG
, public StaticCounter<PhysicsMaterial>
#endif
{
private:
    
    /** Reference to the PhysX PxMaterial */
	PxMaterial*  material;
    
    /** The friction of the material */
    float friction;
    /** The dynamic friction of the material */
    float dynamicFriction;
    /** The restiturion of the material */
    float restitution;
    
public:
    
    /** Constructor
     @param[in] friction The friction of the material
     @param[in] dynamicFriction The dynamic friction of the material
     @param[in] restitution The restiturion of the material
     */
	PhysicsMaterial(float friction, float dynamicFriction, float restitution);
    /** Default Destructor */
	virtual ~PhysicsMaterial();
    

    /** material Getter 
     @return reference to the PhysX material
     */
	 PxMaterial *const   getMaterial() const;
    
};

