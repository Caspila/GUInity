#include "Physics.hpp"
#include <math.h>
#include "Transform.hpp"
#include "MeshRenderer.hpp"
#include "Mesh.hpp"
#include "RigidBody.hpp"


#include "Converter.hpp"
#include "Actor.hpp"
#include "PhysicsMaterial.hpp"
#include "MeshFilter.hpp"
#include "RigidStatic.hpp"


PxScene* Physics::scene;
PxPhysics* Physics::gPhysicsSDK;
PxDefaultErrorCallback Physics::gDefaultErrorCallback;
PxDefaultAllocator Physics::gDefaultAllocatorCallback;
PxFoundation* Physics::gFoundation;
PxReal Physics::myTimestep = 1.0f / 60.0f;
PxMaterial* Physics::defaultPhysicsMaterial;

PxFilterFlags CustomSimulationFilterShader(
	PxFilterObjectAttributes attribute0, PxFilterData filterData0,
	PxFilterObjectAttributes attribute1, PxFilterData filterData1,
	PxPairFlags& pairFlags, const void* constantBlock, PxU32 constantBlockSize)
{
	

	if ((attribute0 & PxFilterObjectFlag::eTRIGGER) != 0 || (attribute1 & PxFilterObjectFlag::eTRIGGER) != 0)
	{
		pairFlags = PxPairFlag::eTRIGGER_DEFAULT;
		//return pairFlags;

		//cout << "aqu1" << endl;
		return PxFilterFlags();
	}

	//cout << "aquo222" << endl;

	pairFlags = PxPairFlag::eCONTACT_DEFAULT | PxPairFlag::eNOTIFY_TOUCH_FOUND;
	//return pairFlags;
	return PxFilterFlags();
}


void releaseMaterial(PxMaterial* material)
{
	//	material->release();
}
void releaseRigidDynamic(PxRigidDynamic* rigidDynamic)
{
	//	material->release();
}

int Physics::init()
{
	gFoundation = NULL;
	gPhysicsSDK = NULL;

	//Creating foundation for PhysX
	gFoundation = PxCreateFoundation
		(PX_PHYSICS_VERSION, gDefaultAllocatorCallback,
		gDefaultErrorCallback);


	//Creating instance of PhysX SDK
	gPhysicsSDK = PxCreatePhysics
		(PX_PHYSICS_VERSION, *gFoundation, PxTolerancesScale());
	if (gPhysicsSDK == NULL)
	{
		cerr << "Error creating PhysX3 device, Exiting..." << endl;
		return 1;
	}

	physxEventCallback = new PhysXEventCallback();

	//gScene->setSimulationEventCallback(&);
	//PxScene* gScene = NULL;

	//gPhysicsSDK->createRigidStatic(();

	//Creating scene
	PxSceneDesc sceneDesc(gPhysicsSDK->getTolerancesScale());
	sceneDesc.flags = PxSceneFlag::eENABLE_ACTIVETRANSFORMS;
	sceneDesc.simulationEventCallback = physxEventCallback;
	sceneDesc.gravity = PxVec3(0.0f, -9.8f, 0.0f);
	sceneDesc.cpuDispatcher = PxDefaultCpuDispatcherCreate(1);
	//sceneDesc.filterShader = PxDefaultSimulationFilterShader;
	sceneDesc.filterShader = CustomSimulationFilterShader;
	//gScene = gPhysicsSDK->createScene(sceneDesc);

	//shared_ptr<PxScene>gScene;
	//gScene.reset(
	scene = gPhysicsSDK->createScene(sceneDesc);// , releaseScene);

	scene->setSimulationEventCallback(physxEventCallback);
	scene->setVisualizationParameter(PxVisualizationParameter::eSCALE, 1.0f);
	scene->setVisualizationParameter(PxVisualizationParameter::eACTOR_AXES, 1.0f);
	scene->setVisualizationParameter(PxVisualizationParameter::eCOLLISION_SHAPES, 1.0f);
    
	defaultPhysicsMaterial = gPhysicsSDK->createMaterial(0.5f, 0.5f, 0.1f);

    return 0;
}
	


shared_ptr<PhysicsMaterial> Physics::createMaterial(float friction, float dynamicFriction, float restitution)
{
	shared_ptr<PxMaterial> material;
	material.reset(gPhysicsSDK->createMaterial(friction, dynamicFriction, restitution), releaseMaterial);

	shared_ptr<PhysicsMaterial> physics = make_shared<PhysicsMaterial>(friction, dynamicFriction, restitution, material);

	return physics;
}
//
//
//void Physics::createBoxRigidBody(shared_ptr<Actor> actor, shared_ptr<PhysicsMaterial> physicsMaterial, bool isKinematic)
//{
//	//PxMaterial* mMaterial = gPhysicsSDK->createMaterial(friction, dynamicFriction, restitution);
//
//	PxTransform physxTransform = transformToPhysXTransform(actor->transform); //getActorTransform(actor);
//
//	PxVec3 boxSize(actor->meshRenderer->mesh->boundsMax.x - actor->meshRenderer->mesh->boundsMin.x,
//		actor->meshRenderer->mesh->boundsMax.y - actor->meshRenderer->mesh->boundsMin.y,
//		actor->meshRenderer->mesh->boundsMax.z - actor->meshRenderer->mesh->boundsMin.z );
//
//	boxSize = boxSize / 2;
//
//	boxSize.x = std::fmaxf(boxSize.x,0.001f);
//	boxSize.y = std::fmaxf(boxSize.y, 0.001f);
//	boxSize.z = std::fmaxf(boxSize.z, 0.001f);
//
//	boxSize.x *= actor->transform->scale.x;
//	boxSize.y *= actor->transform->scale.y;
//	boxSize.z *= actor->transform->scale.z;
//
//	//cout << "boxSize" << boxSize << endl;
//	PxRigidDynamic*rigidDynamic = gPhysicsSDK->createRigidDynamic(physxTransform);
//	//shared_ptr<PxRigidDynamic> rigidDynamic;
//	//rigidDynamic.reset(gPhysicsSDK->createRigidDynamic(physxTransform),releaseRigidDynamic);
//
//	PxShape* shape = rigidDynamic->createShape(PxBoxGeometry(boxSize), *physicsMaterial->material.get());
//	rigidDynamic->setRigidBodyFlag(PxRigidBodyFlag::eKINEMATIC, isKinematic);
//	//shape->setFlag(PxShapeFlag::eSIMULATION_SHAPE, true);
//	//rigidDynamic->setActorFlag(PxActorFlag::eDISABLE_SIMULATION, false);
//
//	rigidDynamic->userData = (void*)actor.get();
//
//	scene->addActor(*rigidDynamic);
//
//	actor->transform->setRigidBody(rigidDynamic);
//}
//
//
//void Physics::createSphereRigidBody(shared_ptr<Actor> actor, shared_ptr<PhysicsMaterial> physicsMaterial, bool isKinematic)
//{
//	//PxMaterial* mMaterial = gPhysicsSDK->createMaterial(friction, dynamicFriction, restitution);
//
//	PxTransform physxTransform = transformToPhysXTransform(actor->transform);//getActorTransform(actor);
//
//	PxVec3 boxSize(actor->meshRenderer->mesh->boundsMax.x - actor->meshRenderer->mesh->boundsMin.x,
//		actor->meshRenderer->mesh->boundsMax.y - actor->meshRenderer->mesh->boundsMin.y,
//		actor->meshRenderer->mesh->boundsMax.z - actor->meshRenderer->mesh->boundsMin.z);
//
//	boxSize = boxSize / 2;
//
//	boxSize.x = std::fmaxf(boxSize.x, 0.001f);
//	boxSize.y = std::fmaxf(boxSize.y, 0.001f);
//	boxSize.z = std::fmaxf(boxSize.z, 0.001f);
//
//	boxSize.x *= actor->transform->scale.x;
//	boxSize.y *= actor->transform->scale.y;
//	boxSize.z *= actor->transform->scale.z;
//
//	float radius = fmaxf(boxSize.x, boxSize.y);
//	radius = fmaxf(radius, boxSize.z);
//
//	PxRigidDynamic*rigidDynamic = gPhysicsSDK->createRigidDynamic(physxTransform);
//	//shared_ptr<PxRigidDynamic> rigidDynamic;
//	//rigidDynamic.reset(gPhysicsSDK->createRigidDynamic(physxTransform),releaseRigidDynamic);
//	PxShape* shape = rigidDynamic->createShape(PxSphereGeometry(radius), *physicsMaterial->material.get());
//
//	rigidDynamic->setRigidBodyFlag(PxRigidBodyFlag::eKINEMATIC, isKinematic);
//	//shape->setFlag(PxShapeFlag::eSIMULATION_SHAPE, true);
//	//rigidDynamic->setActorFlag(PxActorFlag::eDISABLE_SIMULATION, false);
//
//	rigidDynamic->userData = (void*)actor.get();
//
//	scene->addActor(*rigidDynamic);
//
//	actor->transform->setRigidBody(rigidDynamic);
//
//
//}


//PxRigidStatic* Physics::createRigidStatic(shared_ptr<Actor> actor)
//{
//	//PxTransform physxTransform = transformToPhysXTransform(actor->transform);
//	//
//	//PxRigidStatic* rigidStatic = gPhysicsSDK->createRigidStatic(physxTransform);
//	//
//	//rigidStatic->userData = (void*)actor.get();
//	//
//	//scene->addActor(*rigidStatic);
//	//
//	//return rigidStatic;
//	
//	PxRigidDynamic* rigidStatic = createRigidDynamic(actor);
//	
//
//
//}
PxRigidDynamic* Physics::createRigidDynamic(shared_ptr<Actor> actor)
{
	PxTransform physxTransform = transformToPhysXTransform(actor->transform);

	PxRigidDynamic* rigidDynamic = gPhysicsSDK->createRigidDynamic(physxTransform);

	rigidDynamic->userData = static_cast<void*> (actor.get()); //(void*)actor.get();

	scene->addActor(*rigidDynamic);

	return rigidDynamic;
}

PxVec3 getBoxSize(shared_ptr<Actor> actor, shared_ptr<MeshFilter> meshFilter)
{
	PxVec3 boxSize(meshFilter->mesh->boundsMax.x - meshFilter->mesh->boundsMin.x,
		meshFilter->mesh->boundsMax.y - meshFilter->mesh->boundsMin.y,
		meshFilter->mesh->boundsMax.z - meshFilter->mesh->boundsMin.z);

	boxSize = boxSize / 2;

	boxSize.x = std::fmaxf(boxSize.x, 0.001f);
	boxSize.y = std::fmaxf(boxSize.y, 0.001f);
	boxSize.z = std::fmaxf(boxSize.z, 0.001f);

	boxSize.x *= actor->transform->scale.x;
	boxSize.y *= actor->transform->scale.y;
	boxSize.z *= actor->transform->scale.z;

	return boxSize;
}


float getSphereSize(shared_ptr<Actor> actor, shared_ptr<MeshFilter> meshFilter)
{
	PxVec3 boxSize(meshFilter->mesh->boundsMax.x - meshFilter->mesh->boundsMin.x,
		meshFilter->mesh->boundsMax.y - meshFilter->mesh->boundsMin.y,
		meshFilter->mesh->boundsMax.z - meshFilter->mesh->boundsMin.z);
	
		boxSize = boxSize / 2;
	
		boxSize.x = std::fmaxf(boxSize.x, 0.001f);
		boxSize.y = std::fmaxf(boxSize.y, 0.001f);
		boxSize.z = std::fmaxf(boxSize.z, 0.001f);
	
		boxSize.x *= actor->transform->scale.x;
		boxSize.y *= actor->transform->scale.y;
		boxSize.z *= actor->transform->scale.z;
	
		float radius = fmaxf(boxSize.x, boxSize.y);
		radius = fmaxf(radius, boxSize.z);

	return radius;
}

PxShape* Physics::createBoxCollider(shared_ptr<Actor> actor)
{
	shared_ptr<RigidBody> rigidBody = actor->GetComponent<RigidBody>();
	shared_ptr<MeshFilter> meshFilter = actor->GetComponent<MeshFilter>();

	PxVec3 boxSize(0.5f, 0.5f, 0.5f);
	if (meshFilter)
		boxSize = getBoxSize(actor,meshFilter);

	PxShape* shape = nullptr;
	if (rigidBody)
	{

		shape = rigidBody->physxRigidBody->createShape(PxBoxGeometry(boxSize), *defaultPhysicsMaterial);
	}
	else
	{
		shared_ptr<RigidStatic> rigidStatic = actor->AddComponent<RigidStatic>();

		if (rigidStatic)
		{
			shape = rigidStatic->physxRigidStatic->createShape(PxBoxGeometry(boxSize), *defaultPhysicsMaterial);
			shape->userData = (void*)actor.get();
		}
		else
			cerr << "Error when trying to create rigid static for collider";
			
	}

	return shape;
}


PxShape* Physics::createSphereCollider(shared_ptr<Actor> actor)
{
	shared_ptr<RigidBody> rigidBody = actor->GetComponent<RigidBody>();
	shared_ptr<MeshFilter> meshFilter = actor->GetComponent<MeshFilter>();

	float radius = 0.5f;// PxVec3 boxSize(0.5f, 0.5f, 0.5f);
	if (meshFilter)
		radius = getSphereSize(actor, meshFilter);

	PxShape* shape = nullptr;
	if (rigidBody)
	{
		shape = rigidBody->physxRigidBody->createShape(PxSphereGeometry(radius), *defaultPhysicsMaterial);
	}
	else
	{
		shared_ptr<RigidStatic> rigidStatic = actor->AddComponent<RigidStatic>();

		if (rigidStatic)
		{
			shape = rigidStatic->physxRigidStatic->createShape(PxSphereGeometry(radius), *defaultPhysicsMaterial);
			shape->userData = (void*)actor.get();
		}
		else
			cerr << "Error when trying to create rigid static for collider";
	}

	return shape;
}

void Physics::updateActorsTransform()
{
	PxU32 nActiveTransforms;
	const PxActiveTransform* activeTransforms = scene->getActiveTransforms(nActiveTransforms);

	for (int i = 0; i < nActiveTransforms; i++)
	{
		const PxActiveTransform activeTransform = activeTransforms[i];

		Actor*a = (Actor*)(activeTransform.userData);
		a->transform->updateTransform(activeTransform.actor2World);


	}
}

Physics::Physics()//shared_ptr<PxScene> physicsScene)
{
	//this->physicsScene = physicsScene;
}


Physics::~Physics()
{
	//scene->release();
	//gPhysicsSDK->release();
	//gFoundation->release();
}


bool Physics::rayCast(const Ray& r, const float distance, PxRaycastBuffer& hitCallback)
{
	return scene->raycast(glmVec3ToPhysXVec3(r.origin), glmVec3ToPhysXVec3(r.direction), distance, hitCallback);
}

void Physics::tick()
{
	scene->simulate(myTimestep);
	scene->fetchResults(true);
}

void Physics::shutdown()
{
	scene->release();
	gPhysicsSDK->release();
	gFoundation->release();
	
}