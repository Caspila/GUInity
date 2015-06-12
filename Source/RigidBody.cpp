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
    lockConstraints = 0;
    isKinematic = false;
    gravityEnabled = true;
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
        setConstraintsFlags(lockConstraints);
        
        
        setKinematic(isKinematic);
        setGravity(gravityEnabled);
        setActive(isActive);
        
    }
    else
    {
        
        lockConstraints = 0;
        
    }
    
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
    
    physxRigidBody->setGlobalPose(PxTransform(glmMat4ToPhysxMat4(actor->transform->getModelMatrix())));
}


/** Component setActive override. Disables visualization and physics simulation in the PhysX scene */
void RigidBody::setActive(bool isActive)
{
    Component::setActive(isActive);
    
        if(physxRigidBody)
        {
    physxRigidBody->setActorFlag(PxActorFlag::eVISUALIZATION, isActive);
	physxRigidBody->setActorFlag(PxActorFlag::eDISABLE_SIMULATION, !isActive);
        }
    
}


/** physxRigidBody getter
 @return pointer to PhysX RigidBody*/
PxRigidBody* RigidBody::getRigidbody() const
{
	return physxRigidBody;
}

/** isKinematic setter
 @param true if physics should be not be simulated, false if it should */
void RigidBody::setKinematic(bool isKinematic)
{
    this->isKinematic = isKinematic;
    
    if(physxRigidBody)
        physxRigidBody->setRigidBodyFlag(PxRigidBodyFlag::eKINEMATIC, isKinematic);
}

/** isKinematic getter
 @return true if physics is being simulated, false if it's not */
bool RigidBody::getKinematic() const
{
    return isKinematic;
}

/** gravity setter
 @param [in] enabled true if gravity is enabled, false otherwise */
void RigidBody::setGravity(bool enabled)
{
    this->gravityEnabled = enabled;
    
    if(physxRigidBody)
        physxRigidBody->setActorFlag(PxActorFlag::eDISABLE_GRAVITY, !enabled);
}
/** gravity getter
 @return true if gravity is enabled, false otherwise */
bool RigidBody::getGravity() const
{
    return gravityEnabled;
}


int RigidBody::getConstraintsFlags() const
{
    return lockConstraints;
}

void RigidBody::setConstraintsFlags(int constraintFlags)
{
    lockConstraints = constraintFlags;

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
    
    if(lockConstraints & TransformConstraintAxis::X_MOVE_LOCK)
    {
        newPosition.x = position.x;
        currentVelocity.x = 0;
    }
    if(lockConstraints & TransformConstraintAxis::Y_MOVE_LOCK)

    {
        newPosition.y = position.y;
        currentVelocity.y = 0;
    }
    if(lockConstraints & TransformConstraintAxis::Z_MOVE_LOCK)

    {
        newPosition.z = position.z;
        currentVelocity.z = 0;
    }
    
    if(lockConstraints & TransformConstraintAxis::X_ROTATE_LOCK)

    {
        newRotationEuler.x = rotationEuler.x;
        angularVelocity.x = 0;
    }
    if(lockConstraints & TransformConstraintAxis::Y_ROTATE_LOCK)

    {
        newRotationEuler.y = rotationEuler.y;
        angularVelocity.y = 0;
    }
    if(lockConstraints & TransformConstraintAxis::Z_ROTATE_LOCK)

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
    compClone->setConstraintsFlags(lockConstraints);

    
    compClone->isKinematic = isKinematic;
    
    compClone->gravityEnabled = gravityEnabled;
    
    return compClone;
};


/** Creates a description for the Component*/
shared_ptr<ComponentDescription> RigidBody::getComponentDescription()
{
    return make_shared<RigidBodyDescription>(getKinematic(),lockConstraints,gravityEnabled);
}

/** Deserializes a description to a Component */
void RigidBody::deserialize(shared_ptr<ComponentDescription> desc)
{
    shared_ptr<RigidBodyDescription> rigidBodyDesc = dynamic_pointer_cast<RigidBodyDescription>(desc);
    this->lockConstraints = rigidBodyDesc->lockConstraints;
    this->gravityEnabled = rigidBodyDesc->gravityEnabled;
    this->isKinematic = rigidBodyDesc->isKinematic;
    
    setCopyMode(true);
    
}

