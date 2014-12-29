#pragma once
#include "Component.hpp"
#include "Subject.hpp"
#include <PxPhysics.h>

using namespace physx;

class Actor;

class EditorCollider : public Subject<EditorCollider>, public enable_shared_from_this<EditorCollider>,
	public Component
{
public:
	EditorCollider();
	~EditorCollider();

	weak_ptr<Actor> gameActor;

	virtual void init() override;
	virtual void tick(float deltaSeconds) override;

	void setGameActor(shared_ptr<Actor> gameActor);

	PxRigidDynamic* physxRigidStatic;
};

