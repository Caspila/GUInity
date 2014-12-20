#pragma once
#include <PxPhysicsAPI.h>
#include "Ray.h"
#include "print.h"
#include "Actor.h"
#include "PhysXEventCallback.h"
#include "PhysicsMaterial.h"

using namespace physx;


class Physics
{
	enum ColliderType {sphere, box};

public:
	Physics();// shared_ptr<PxScene> physicsScene);
	~Physics();

	int init();

	static PxPhysics* gPhysicsSDK;
	static PxDefaultErrorCallback gDefaultErrorCallback;
	static PxDefaultAllocator gDefaultAllocatorCallback;
	static PxFoundation* gFoundation;
	static PxScene* scene;

	PhysXEventCallback physxEventCallback;

	static bool rayCast(const Ray& r, const float distance, PxRaycastBuffer& hitCallback);

	static PxTransform getActorTransform(shared_ptr<Actor> actor);

	static void updateActorsTransform();
	static void createSphereRigidBody(shared_ptr<Actor> actor, shared_ptr<PhysicsMaterial> physicsMaterial, bool isKinematic);
	static void createBoxRigidBody(shared_ptr<Actor> actor, shared_ptr<PhysicsMaterial> physicsMaterial, bool isKinematic);
	//static void createBoxRigidBody(shared_ptr<Actor> actor, const glm::vec3& boxSize, float friction, float dynamicFriction, float restitution, bool isKinematic);
	//static void createSphereRigidBody(shared_ptr<Actor> actor, float radius, float friction, float dynamicFriction, float restitution, bool isKinematic);
	//static void CreateSphereRigidBody(weak_ptr<Actor> actor);

	static shared_ptr<PhysicsMaterial> createMaterial(float friction, float dynamicFriction, float restitution);

	static void tick();

	static void shutdown();

	static PxReal myTimestep;
};

