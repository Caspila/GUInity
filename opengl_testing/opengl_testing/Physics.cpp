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
#include <PxPhysicsAPI.h>
#include "PhysXAllocatorCallback.h"

PhysXEventCallback* Physics::physxEventCallback;
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

PxRigidDynamic* Physics::createRigidDynamic(shared_ptr<Actor> actor)
{
	PxTransform physxTransform = transformToPhysXTransform(actor->transform);

	PxRigidDynamic* rigidDynamic = gPhysicsSDK->createRigidDynamic(physxTransform);

	rigidDynamic->userData = static_cast<void*> (actor.get()); //(void*)actor.get();

	//scene->addActor(*rigidDynamic);

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

	PxVec3 center(0, 0, 0);
	PxVec3 boxSize(0.5f, 0.5f, 0.5f);
	if (meshFilter)
	{
		boxSize = getBoxSize(actor, meshFilter);
		center = PxVec3(glmVec3ToPhysXVec3( meshFilter->mesh->avgCenter));
	}

	PxShape* shape = nullptr;
	if (rigidBody)
	{

		shape = rigidBody->physxRigidBody->createShape(PxBoxGeometry(boxSize), *defaultPhysicsMaterial);
	}
	else
	{
		shared_ptr<RigidStatic> rigidStatic = actor->GetComponent<RigidStatic>();
		if (!rigidStatic)
			rigidStatic = actor->AddComponent<RigidStatic>();

			shape = rigidStatic->physxRigidStatic->createShape(PxBoxGeometry(boxSize), *defaultPhysicsMaterial);
			shape->userData = (void*)actor.get();
			
	}

	shape->setLocalPose(PxTransform(center, PxQuat::createIdentity()));

	return shape;
}


PxShape* Physics::createSphereCollider(shared_ptr<Actor> actor)
{
	shared_ptr<RigidBody> rigidBody = actor->GetComponent<RigidBody>();
	shared_ptr<MeshFilter> meshFilter = actor->GetComponent<MeshFilter>();

	PxVec3 center(0,0,0);
	float radius = 0.5f;// PxVec3 boxSize(0.5f, 0.5f, 0.5f);
	if (meshFilter)
	{
		radius = getSphereSize(actor, meshFilter);

		center = PxVec3(glmVec3ToPhysXVec3(meshFilter->mesh->avgCenter));
	}

	PxShape* shape = nullptr;
	if (rigidBody)
	{

		shape = rigidBody->physxRigidBody->createShape(PxSphereGeometry(radius), *defaultPhysicsMaterial);
	}
	else
	{

		shared_ptr<RigidStatic> rigidStatic = actor->GetComponent<RigidStatic>();
		if (!rigidStatic)
			rigidStatic = actor->AddComponent<RigidStatic>();

			shape = rigidStatic->physxRigidStatic->createShape(PxSphereGeometry(radius), *defaultPhysicsMaterial);
			shape->userData = (void*)actor.get();
		}


	shape->setLocalPose(PxTransform(center, PxQuat::createIdentity()));

	return shape;
}


PxShape* Physics::createCapsuleCollider(shared_ptr<Actor> actor)
{
	shared_ptr<RigidBody> rigidBody = actor->GetComponent<RigidBody>();
	//shared_ptr<MeshFilter> meshFilter = actor->GetComponent<MeshFilter>();
	//
	//float radius = 0.5f;// PxVec3 boxSize(0.5f, 0.5f, 0.5f);
	//if (meshFilter)
	//	radius = getSphereSize(actor, meshFilter);

	PxShape* shape = nullptr;
	if (rigidBody)
	{
		shape = rigidBody->physxRigidBody->createShape(PxCapsuleGeometry(0.5f,0.5f), *defaultPhysicsMaterial);
	}
	else
	{
		
		shared_ptr<RigidStatic> rigidStatic = actor->GetComponent<RigidStatic>();
		if (!rigidStatic)
			rigidStatic = actor->AddComponent<RigidStatic>();

		shape = rigidStatic->physxRigidStatic->createShape(PxCapsuleGeometry(0.5f, 0.5f), *defaultPhysicsMaterial);
		shape->userData = (void*)actor.get();
	}

	return shape;
}

PxConvexMesh* Physics::getPxConvexMesh(shared_ptr<Mesh> mesh)
{

	//desc.points.


	PxVec3* mMeshVertices = new physx::PxVec3[mesh->meshVertices.size()];
	for (int i = 0; i < mesh->meshVertices.size(); i++)
	{
		mMeshVertices[i] = PxVec3(mesh->meshVertices[i].position.x, mesh->meshVertices[i].position.y, mesh->meshVertices[i].position.z);
	}
	PxU32* triangles = new PxU32[mesh->triangles.size()];
	for (int i = 0; i < mesh->triangles.size(); i++)
	{
		triangles[i] = mesh->triangles[i];
	}

	PxSimpleTriangleMesh triangleMesh;
	//desc.
	//PxSimpleTriangleMesh triangleMesh;
	triangleMesh.points.count = mesh->meshVertices.size();
	triangleMesh.points.stride = sizeof(PxVec3);
	triangleMesh.points.data = mMeshVertices;

	triangleMesh.triangles.count = mesh->triangles.size();
	triangleMesh.triangles.stride = 3*sizeof(PxU32);
	triangleMesh.triangles.data = triangles;

	//triangleMesh.flags = PxMeshFlag::eFLIPNORMALS;

	bool ok = triangleMesh.isValid();


	PhysXAllocatorCallback callback;

	PxCooking *cooking = PxCreateCooking(PX_PHYSICS_VERSION, PxGetFoundation(), PxCookingParams(PxTolerancesScale()));

	//PxPhysicsInsertionCallback

	//cooking->createTriangleMesh(triangleMeshDesc,pxdefaultinser)

	PxU32 nbVertices, nbIndices, nbPolygons ;
	PxU32 *indices ;
	PxHullPolygon *polygons;
	PxVec3 *vertices;

	
    PxDefaultAllocator defaultAllocator;
    
	//cooking->cre
	//cooking->createTriangleMesh()
	bool status = cooking->computeHullPolygons(triangleMesh, defaultAllocator, nbVertices, vertices, nbIndices, indices, nbPolygons, polygons);

	PxConvexMeshDesc convexDesc;
	convexDesc.points.count = nbVertices;
	convexDesc.points.stride = sizeof(PxVec3);
	convexDesc.points.data = vertices;
	
	convexDesc.indices.count = nbIndices;
	convexDesc.indices.stride = sizeof(PxU32);
	convexDesc.indices.data = indices;

	convexDesc.polygons.count = nbPolygons;
	convexDesc.polygons.stride = sizeof(PxHullPolygon);
	convexDesc.polygons.data = polygons;

	PxDefaultMemoryOutputStream output;
	
	status = cooking->cookConvexMesh(convexDesc, output);
	
	PxDefaultMemoryInputData input(output.getData(), output.getSize());
	physx::PxConvexMesh* convexMesh = gPhysicsSDK->createConvexMesh(input);
	
	return convexMesh;

	//PxU32* mMeshFaces = new physx::PxU32[mIndexCount];
}

PxShape* Physics::createMeshCollider(shared_ptr<Actor> actor)
{
	shared_ptr<RigidBody> rigidBody = actor->GetComponent<RigidBody>();
	shared_ptr<MeshFilter> meshFilter = actor->GetComponent<MeshFilter>();

	PxConvexMeshGeometry geo(getPxConvexMesh(meshFilter->mesh));
	PxShape* shape = nullptr;
	if (rigidBody)
	{
		
		shape = rigidBody->physxRigidBody->createShape(geo, *defaultPhysicsMaterial);
	
	}
	else
	{

		shared_ptr<RigidStatic> rigidStatic = actor->GetComponent<RigidStatic>();
		if (!rigidStatic)
			rigidStatic = actor->AddComponent<RigidStatic>();
		//
		shape = rigidStatic->physxRigidStatic->createShape(geo, *defaultPhysicsMaterial);
		//shape->userData = (void*)actor.get();
	}

	return shape;
}

void Physics::updateActorsTransform(PxScene* scene)
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


bool Physics::rayCast(PxScene* scene, const Ray& r, const float distance, PxRaycastBuffer& hitCallback)
{
	return scene->raycast(glmVec3ToPhysXVec3(r.origin), glmVec3ToPhysXVec3(r.direction), distance, hitCallback);
}

void Physics::tickScene(PxScene* scene)
{
	scene->simulate(myTimestep);
	scene->fetchResults(true);
}

//void Physics::tick()
//{
//	scene->simulate(myTimestep);
//	scene->fetchResults(true);
//}

void Physics::shutdown()
{
//	scene->release();
	gPhysicsSDK->release();
	gFoundation->release();
	
}

PxScene* Physics::createPhysicsScene()
{

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
	PxScene* scene = gPhysicsSDK->createScene(sceneDesc);// , releaseScene);

	scene->setSimulationEventCallback(physxEventCallback);
	scene->setVisualizationParameter(PxVisualizationParameter::eSCALE, 1.0f);
	scene->setVisualizationParameter(PxVisualizationParameter::eACTOR_AXES, 1.0f);
	scene->setVisualizationParameter(PxVisualizationParameter::eCOLLISION_SHAPES, 1.0f);

	return scene;
}