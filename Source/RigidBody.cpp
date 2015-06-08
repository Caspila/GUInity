#include "RigidBody.hpp"
#include "Physics.hpp"
#include "Converter.hpp"
#include "Actor.hpp"
#include <PxRigidBody.h>
#include "Transform.hpp"

/** Default Constructor */
RigidBody::RigidBody()
{
    setCopyMode(false);
    physxRigidBody = nullptr;
#ifdef GUINITY_DEBUG
    nCount++;
#endif
}

/** Default Destructor */
RigidBody::~RigidBody()
{
    
#ifdef GUINITY_DEBUG
	nCount--;
	cout << "RigidBody destroyed (" << nCount << " remaining)" << endl;
#endif
}



/** Component init override. Creates a RigidDynamic body in the PhysX scene */
void RigidBody::init()
{
    Component::init();
	
	physxRigidBody = Physics::createRigidDynamic(getActor());
    if(initWithData)
    {
        setMoveEnabled(TransformAxis::x, lockMoveX);
        setMoveEnabled(TransformAxis::y, lockMoveY);
        setMoveEnabled(TransformAxis::z, lockMoveZ);
        
        setRotateEnabled(TransformAxis::x, lockRotateX);
        setRotateEnabled(TransformAxis::y, lockRotateY);
        setMoveEnabled(TransformAxis::z, lockRotateZ);
        
        setKinematic(isKinematic);
        setGravity(gravityEnabled);
        
    }
    else
    {
        lockMoveX = lockMoveY = lockMoveZ = lockRotateX = lockRotateY = lockRotateZ = false;
        
    }
    //    d6Joint = Physics::createD6Joint(getActor(),physxRigidBody);
    
    
    
    //    physxRigidBody->setRigidDynamicFlag(PxRigidDynamicFlag::, <#bool value#>)
    //    physxRigidBody->setClientBehaviorFlags(PxActorClientBehaviorFlags)
    //    physxRigidBody->setc
    
    
    
    
    
    //    physxRigidBody->setBaseFlag(PxBaseFlag::, <#bool value#>)
    
	notify(NewRigidBody, shared_from_this(), getActor()->getEditorFlag());
}

/** Component destroy override. Releases the RigidDynamic body */
void RigidBody::destroy()
{
    Component::destroy();
    physxRigidBody->release();
}



/** Component tick override. Updates the PhysX scene with the Actor transform */
void RigidBody::tick(float deltaSeconds)
{
    Component::tick(deltaSeconds);
	shared_ptr<Actor> actor = getActor();
    
    
    //	physxRigidBody->setGlobalPose(transformToPhysXTransform(actor->transform));
    physxRigidBody->setGlobalPose(PxTransform(glmMat4ToPhysxMat4(actor->transform->getModelMatrix())));
}


/** Component setActive override. Disables visualization and physics simulation in the PhysX scene */
void RigidBody::setActive(bool isActive)
{
    Component::setActive(isActive);
    
    physxRigidBody->setActorFlag(PxActorFlag::eVISUALIZATION, isActive);
	physxRigidBody->setActorFlag(PxActorFlag::eDISABLE_SIMULATION, !isActive);
    
    
}


/** physxRigidBody getter
 @return pointer to PhysX RigidBody*/
PxRigidBody* RigidBody::getRigidbody()
{
	return physxRigidBody;
}

/** isKinematic setter
 @param true if physics should be not be simulated, false if it should */
void RigidBody::setKinematic(bool isKinematic)
{
    this->isKinematic = isKinematic;
    
	physxRigidBody->setRigidBodyFlag(PxRigidBodyFlag::eKINEMATIC, isKinematic);
}

/** isKinematic getter
 @return true if physics is being simulated, false if it's not */
bool RigidBody::getKinematic()
{
    return isKinematic;
    
    //    return physxRigidBody->getRigidBodyFlags() & (PxRigidBodyFlag::eKINEMATIC);
}

/** gravity setter
 @param [in] enabled true if gravity is enabled, false otherwise */
void RigidBody::setGravity(bool enabled)
{
    this->gravityEnabled = enabled;
	physxRigidBody->setActorFlag(PxActorFlag::eDISABLE_GRAVITY, true);
}
/** gravity getter
 @return true if gravity is enabled, false otherwise */
bool RigidBody::getGravity()
{
    return gravityEnabled;
    //	return physxRigidBody->getActorFlags() & (PxActorFlag::eDISABLE_GRAVITY);
}

/** Allow or constrain translation in one of the 3 axis
 @param [in] axis one of the 3 axis (X,Y,Z)
 @param [in] true to allow, false to constrain */
void RigidBody::setMoveEnabled(TransformAxis axis, bool enabled)
{
    PxD6Motion::Enum d6Motion = enabled ? PxD6Motion::eFREE : PxD6Motion::eLOCKED;
    
    switch(axis)
    {
        case TransformAxis::x:
            
            //            d6Joint->setMotion(PxD6Axis::eX, d6Motion);
            lockMoveX = !enabled;
            break;
        case TransformAxis::y:
            //                        d6Joint->setMotion(PxD6Axis::eY, d6Motion);
            lockMoveY = !enabled;
            break;
        case TransformAxis::z:
            //                        d6Joint->setMotion(PxD6Axis::eZ, d6Motion);
            lockMoveZ = !enabled;
            break;
            
            
    }
}

/** Allow or constrain rotation in one of the 3 axis
 @param [in] axis one of the 3 axis (X,Y,Z)
 @param [in] true to allow, false to constrain */
void RigidBody::setRotateEnabled(TransformAxis axis, bool enabled)
{
    PxD6Motion::Enum d6Motion = enabled ? PxD6Motion::eFREE : PxD6Motion::eLOCKED;
    
    switch(axis)
    {
        case TransformAxis::x:
            
            //            d6Joint->setMotion(PxD6Axis::eTWIST, d6Motion);
            lockRotateX = !enabled;
            break;
        case TransformAxis::y:
            //            d6Joint->setMotion(PxD6Axis::eSWING1, d6Motion);
            lockRotateY = !enabled;
            break;
        case TransformAxis::z:
            //            d6Joint->setMotion(PxD6Axis::eSWING2, d6Motion);
            lockRotateZ = !enabled;
            break;
            
            
    }
}

/** Update the transform based on the PhysX physics simulation and current constraints
 @param [in] the PhysX transform*/
void RigidBody::updateTransform(const PxTransform& newTransform)
{
    shared_ptr<Transform> transform = getActor()->transform;
    
    glm::vec3 position = transform->position;
    glm::vec3 rotationEuler = glm::eulerAngles(transform->rotation);
    
    glm::vec3 newPosition = PhysXVec3ToglmVec3(newTransform.p);
    glm::vec3 newRotationEuler = glm::eulerAngles(PhysXQuatToglmQuat(newTransform.q));
    
    PxVec3 currentVelocity = physxRigidBody->getLinearVelocity();
    PxVec3 angularVelocity = physxRigidBody->getAngularVelocity();
    
    if(lockMoveX)
    {
        newPosition.x = position.x;
        currentVelocity.x = 0;
    }
    if(lockMoveY)
    {
        newPosition.y = position.y;
        currentVelocity.y = 0;
    }
    if(lockMoveZ)
    {
        newPosition.z = position.z;
        currentVelocity.z = 0;
    }
    
    if(lockRotateX)
    {
        newRotationEuler.x = rotationEuler.x;
        angularVelocity.x = 0;
    }
    if(lockRotateY)
    {
        newRotationEuler.y = rotationEuler.y;
        angularVelocity.y = 0;
    }
    if(lockRotateZ)
    {
        newRotationEuler.z = rotationEuler.z;
        angularVelocity.z = 0;
    }
    
    
    
    transform->position = newPosition;
    transform->rotation = glm::quat(newRotationEuler);
    
    physxRigidBody->setLinearVelocity(currentVelocity);
    physxRigidBody->setAngularVelocity(angularVelocity);
    
    physxRigidBody->setGlobalPose(PxTransform(glmVec3ToPhysXVec3(transform->position),glmQuatToPhysXQuat(transform->rotation)));
    
}

/** Add force to the RigidBody
 @param [in] the force that will be added (direction and magnitude)
 */
void RigidBody::addForce(glm::vec3 axis)
{
    
    physxRigidBody->addForce(glmVec3ToPhysXVec3(axis));
    
}







/** Clones current component (Prototype Design Pattern)
 @return shared_ptr to cloned RigidBody Component
 */
shared_ptr<Component> RigidBody::clone()
{
    shared_ptr<RigidBody> compClone = make_shared<RigidBody>();
    
    compClone->setCopyMode(true);
    compClone->lockMoveX = lockMoveX;
    compClone->lockMoveY = lockMoveY;
    compClone->lockMoveZ = lockMoveZ;
    
    compClone->lockRotateX = lockRotateX;
    compClone->lockRotateY = lockRotateY;
    compClone->lockRotateZ = lockRotateZ;
    
    compClone->isKinematic = isKinematic;
    
    compClone->gravityEnabled = gravityEnabled;
    
    return compClone;
};


	/** Creates a description for the Component*/
shared_ptr<ComponentDescription> RigidBody::getComponentDescription()
{
    return make_shared<RigidBodyDescription>(getKinematic());
}

    /** Deserializes a description to a Component */
void RigidBody::deserialize(shared_ptr<ComponentDescription> desc)
{
    
}

