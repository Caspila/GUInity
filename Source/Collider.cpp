#include "Collider.hpp"
#include <PhysicsMaterial.hpp>

/** Component Init override */
void Collider::init()
{
    Component::init();
    
    physicsMaterial = Physics::getDefaultMaterial();
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
    
	shape->setFlag(PxShapeFlag::eVISUALIZATION, isActive);
}

/** isTrigger setter
 @param [in] isTrigger - true if it's just a trigger, false if it physics simulated */
void Collider::setTrigger(bool isTrigger)
{
    this->isTrigger = isTrigger;
    
	shape->setFlag(PxShapeFlag::eSIMULATION_SHAPE, !isTrigger);
	shape->setFlag(PxShapeFlag::eTRIGGER_SHAPE, isTrigger);
}
/** isTrigger getter
 @return true if it's just a trigger, false if it physics simulated
 */
bool Collider::getIsTrigger()
{
	return isTrigger;
}

/** isQueryOnly getter
 @return true if this object is only used in queries, false otherwise
 */

void Collider::setQueryOnly(bool isQueryOnly)
{
    this->isQueryOnly = isQueryOnly;
	shape->setFlag(PxShapeFlag::eSCENE_QUERY_SHAPE, isQueryOnly);
}
/** isQueryOnly getter
 @param [in] queryOnly true if this object is only used in queries, false otherwise */
bool Collider::getQueryOnly()
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
shared_ptr<PhysicsMaterial> Collider::getPhysicsMaterial()
{
	return physicsMaterial;
}



