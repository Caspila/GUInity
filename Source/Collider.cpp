#include "Collider.hpp"
#include <PhysicsMaterial.hpp>
#include "Converter.hpp"

/** Component Init override */
void Collider::init()
{
    Component::init();
    
    physicsMaterial = Physics::getDefaultMaterial();
    if(initWithData)
    {
        setIsTrigger(isTrigger);
        setQueryOnly(isQueryOnly);
        setCenter(center);
    }
}


/** Component destroy override */
void Collider::destroy()
{
    Component::destroy();
    
    if(shape)
        shape->release();
}

/** Component setActive override */
void Collider::setActive(bool isActive)
{
    Component::setActive(isActive);
    
    if(shape)
        shape->setFlag(PxShapeFlag::eVISUALIZATION, isActive);
}


/** center setter
 @param [in] center the center of the physics shape */
void Collider::setCenter(PxVec3 center)
{
    this->center = center;
    
//    if(shape)
//    {
//        shape->setLocalPose(PxTransform(this->center));
//    }
}
/** center getter
 @return center of the physics shape
 */
PxVec3 Collider::getCenter() const
{
    return center;
}

/** isTrigger setter
 @param [in] isTrigger - true if it's just a trigger, false if it physics simulated */
void Collider::setIsTrigger(bool isTrigger)
{
    this->isTrigger = isTrigger;
    
    if(shape)
    {
        shape->setFlag(PxShapeFlag::eSIMULATION_SHAPE, !isTrigger);
        shape->setFlag(PxShapeFlag::eTRIGGER_SHAPE, isTrigger);
    }
}
/** isTrigger getter
 @return true if it's just a trigger, false if it physics simulated
 */
bool Collider::getIsTrigger() const
{
	return isTrigger;
}

/** isQueryOnly getter
 @return true if this object is only used in queries, false otherwise
 */

void Collider::setQueryOnly(bool isQueryOnly)
{
    this->isQueryOnly = isQueryOnly;
    if(shape)
        shape->setFlag(PxShapeFlag::eSCENE_QUERY_SHAPE, isQueryOnly);
}
/** isQueryOnly getter
 @param [in] queryOnly true if this object is only used in queries, false otherwise */
bool Collider::getQueryOnly() const
{
	return isQueryOnly;
}

/** physicsMaterial getter
 @param [in] reference to PhysicsMaterial */
void Collider::setPhysicsMaterial(shared_ptr<PhysicsMaterial> physMaterial)
{
    if(physMaterial!=nullptr)
    {
        
        physicsMaterial = physMaterial;
        
        PxMaterial* mat = physicsMaterial->getMaterial();
        PxMaterial* const newMat = const_cast<PxMaterial* const>(mat);
        
        if(shape)
            shape->setMaterials(&newMat, 1);
    }
}
/** physicsMaterial getter
 @return referente to PhysicsMaterial */
shared_ptr<PhysicsMaterial> Collider::getPhysicsMaterial() const
{
	return physicsMaterial;
}



