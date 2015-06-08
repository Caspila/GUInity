#pragma once
#include <PxPhysicsAPI.h>
#include "Ray.hpp"
#include "PhysXEventCallback.hpp"
#include "Enums.hpp"
#include <map>


class Actor;
class PhysicsMaterial;
class Mesh;

using namespace physx;


class Physics
{
	//enum ColliderType {sphere, box};


	/*static PxMaterial* defaultPhysicsMaterial;*/
	static shared_ptr<PhysicsMaterial> defaultPhysicsMaterial;

public:
	Physics();// shared_ptr<PxScene> physicsScene);
	~Physics();

	int init();

	static PxPhysics* gPhysicsSDK;
	static PxDefaultErrorCallback gDefaultErrorCallback;
	static PxDefaultAllocator gDefaultAllocatorCallback;
	static PxFoundation* gFoundation;
	//static PxScene* scene;


	static PhysXEventCallback* physxEventCallback;

	static bool rayCast(PxScene* scene, const Ray& r, const float distance, PxRaycastBuffer& hitCallback);

	//static PxTransform getActorTransform(shared_ptr<Actor> actor);

//    static void applyRigidBodyConstraints(PxScene* scene);
	static void updateActorsTransform(PxScene* scene);
	//static void createSphereRigidBody(shared_ptr<Actor> actor, shared_ptr<PhysicsMaterial> physicsMaterial, bool isKinematic);
	//static void createBoxRigidBody(shared_ptr<Actor> actor, shared_ptr<PhysicsMaterial> physicsMaterial, bool isKinematic);

	//static PxRigidStatic* createRigidStatic(shared_ptr<Actor> actor);
	static PxRigidDynamic* createRigidDynamic(shared_ptr<Actor> actor);
    static PxD6Joint* createD6Joint(shared_ptr<Actor> actor,PxRigidBody* rigidBody);
    
	static PxShape* createBoxCollider(glm::vec3 halfExtent,glm::vec3 center, shared_ptr<Actor> actor);
	static PxShape* createBoxCollider(PxVec3 halfExtent,PxVec3 center, shared_ptr<Actor> actor);
    static PxShape* createBoxCollider(shared_ptr<Actor> actor);
    

    
    static PxShape* createSphereCollider(float radius, glm::vec3 center, shared_ptr<Actor> actor);
    static PxShape* createSphereCollider(float radius, PxVec3 center, shared_ptr<Actor> actor);
	static PxShape* createSphereCollider(shared_ptr<Actor> actor);
    

    
    static void setCapsuleOrientation(PxShape* shape,RotateAxis orientation);
    static PxShape* createCapsuleCollider(float radius, float halfHeight, RotateAxis orientation, glm::vec3 center, shared_ptr<Actor> actor);
    static PxShape* createCapsuleCollider(float radius, float halfHeight, RotateAxis orientation, PxVec3 center, shared_ptr<Actor> actor);
	static PxShape* createCapsuleCollider(shared_ptr<Actor> actor);
	
    static PxShape* createMeshCollider(shared_ptr<Actor> actor);
	static PxConvexMesh* getPxConvexMesh(shared_ptr<Mesh> mesh);

	static PxScene* createPhysicsScene();

	static PxMaterial* createMaterial(float friction, float dynamicFriction, float restitution);

	static shared_ptr<PhysicsMaterial> getDefaultMaterial();
	//static void tick();
	static void tickScene(PxScene* scene);

	static void shutdown();

	static PxReal myTimestep;
    
    static map<shared_ptr<Mesh>,PxConvexMesh*> convexMeshes;
    
    static bool convexMeshComputed(shared_ptr<Mesh> mesh);
};

