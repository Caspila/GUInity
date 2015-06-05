#pragma once
#include "Component.hpp"
#include "Subject.hpp"
#include <PxPhysics.h>

using namespace physx;

class Actor;

/** EditorCollider is a component used only by editor actors. They're used for queries only, so that when the user
clicks on whatever Actor in the scene, we can find it using PhysX queries. The basic difference between the 
EditorCollider and the regular Collider is that this one has a reference to the real Game Actor.*/

class EditorCollider : public Subject<EditorCollider>,
	public Component
{
private:
	/** Reference to the real Game Actor */
	weak_ptr<Actor> gameActor;
	/** PhysX rigid body*/
	PxRigidDynamic* physxRigidStatic;
public:
	/** Default Constructor */
	EditorCollider() { physxRigidStatic = nullptr; };
	/** Default Destructor. Virtual because inherits from Component */
	virtual ~EditorCollider() {};

	

	/** Component init override. Initializes the rigid body in the PhysX scene. */
	virtual void init() override;
	/** Component tick override. Updates the fake collider position and rotation to match the real Game Actor */
	virtual void tick(float deltaSeconds) override;
	/** gameActor setter*/
	void setGameActor(shared_ptr<Actor> gameActor);
	/** gameActor getter*/
	shared_ptr<Actor> getGameActor();

	/** physxRigidStatic getter*/
	PxRigidDynamic* getRigidStatic();


};

