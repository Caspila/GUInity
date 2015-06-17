#include "RigidStatic.hpp"
#include "Physics.hpp"
#include "Converter.hpp"
#include "Actor.hpp"
#include "Transform.hpp"

/** Default Constructor */
RigidStatic::RigidStatic()
{
    setCopyMode(false);
    physxRigidStatic = nullptr;
}
/** Default Destructor */
RigidStatic::~RigidStatic()
{
}

/** Component init override. Creates a RigidDynamic body in the PhysX scene and sets it as Kinematic by default */
void RigidStatic::init()
{
	physxRigidStatic = Physics::createRigidDynamic(getActor());
	//physxRigidStatic->setActorFlag(PxActorFlag::eDISABLE_SIMULATION,true);
	physxRigidStatic->setRigidDynamicFlag(PxRigidDynamicFlag::eKINEMATIC, true);
    
	notify(NewRigidStatic, shared_from_this(), getActor()->getEditorFlag());
}
/** Component destroy override. Releases the RigidDynamic body */
void RigidStatic::destroy()
{
    physxRigidStatic->release();
    //	notify(RemovedRigidStatic, shared_from_this(), getActor()->getEditorFlag());
}

/** Component tick override. Updates the PhysX scene with the Actor transform
 @param [in] deltaSeconds last frame duration */
void RigidStatic::tick(float deltaSeconds)
{
	shared_ptr<Actor> actor = getActor();
    
//    physxRigidStatic->setGlobalPose(transformToPhysXTransform(actor->transform));

    physxRigidStatic->setGlobalPose(PxTransform(glmMat4ToPhysxMat4(actor->transform->getPosRotMatrix())));
    
}


/** Component setActive override. Disables visualization and physics simulation in the PhysX scene */
void RigidStatic::setActive(bool isActive)
{
    physxRigidStatic->setActorFlag(PxActorFlag::eVISUALIZATION, isActive);
	physxRigidStatic->setActorFlag(PxActorFlag::eDISABLE_SIMULATION, !isActive);
    
    
}

/** physxRigidBody getter
 @return pointer to PhysX RigidBody*/
PxRigidDynamic* RigidStatic::getRigidDynamic()
{
    return physxRigidStatic;
}

/** Clones current component (Prototype Design Pattern)
 @return shared_ptr to cloned RigidStatic Component
 */
shared_ptr<Component> RigidStatic::clone()
{
    shared_ptr<RigidStatic> compClone = make_shared<RigidStatic>();
    
    return compClone;
};

shared_ptr<ComponentDescription> RigidStatic::getComponentDescription()
{
    return make_shared<RigidStaticDescription>();
}

void RigidStatic::deserialize(shared_ptr<ComponentDescription> desc)
{
    shared_ptr<RigidStaticDescription> rigidBodyDesc = dynamic_pointer_cast<RigidStaticDescription>(desc);
    
    setCopyMode(true);
}
