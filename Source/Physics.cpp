#include "Physics.hpp"
#include <math.h>
#include "Math.hpp"
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
//#include <PxToolkit.h>
#include <PxConstraint.h>
#include <PxConstraintDesc.h>
#include <PxPhysics.h>
#include "AssetDatabase.hpp"

PhysXEventCallback* Physics::physxEventCallback;
PxPhysics* Physics::gPhysicsSDK;
PxDefaultErrorCallback Physics::gDefaultErrorCallback;
PxDefaultAllocator Physics::gDefaultAllocatorCallback;
PxFoundation* Physics::gFoundation;
PxReal Physics::myTimestep = 1.0f / 60.0f;
//PxMaterial* Physics::defaultPhysicsMaterial;
shared_ptr<PhysicsMaterial> Physics::defaultPhysicsMaterial;
map<shared_ptr<Mesh>,PxConvexMesh*> Physics::convexMeshes;

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

    
	defaultPhysicsMaterial = AssetDatabase::createPhysicsMaterial("default",0.5f, 0.5f, 0.1f);

	//defaultPhysicsMaterial = gPhysicsSDK->createMaterial(0.5f, 0.5f, 0.1f);

    return 0;
}
	
shared_ptr<PhysicsMaterial> Physics::getDefaultMaterial()
{
	return defaultPhysicsMaterial;
}

PxMaterial* Physics::createMaterial(float friction, float dynamicFriction, float restitution)
{
	//shared_ptr<PxMaterial> material;
	//material.reset(gPhysicsSDK->createMaterial(friction, dynamicFriction, restitution), releaseMaterial);

	//shared_ptr<PhysicsMaterial> physics = make_shared<PhysicsMaterial>(friction, dynamicFriction, restitution, material);

	//return physics;

	return gPhysicsSDK->createMaterial(friction, dynamicFriction, restitution);
}

PxRigidDynamic* Physics::createRigidDynamic(shared_ptr<Actor> actor)
{
	PxTransform physxTransform = transformToPhysXTransform(actor->transform);

	PxRigidDynamic* rigidDynamic = gPhysicsSDK->createRigidDynamic(physxTransform);

	rigidDynamic->userData = static_cast<void*> (actor.get()); //(void*)actor.get();

	//scene->addActor(*rigidDynamic);


    
    
	return rigidDynamic;
}
PxD6Joint* Physics::createD6Joint(shared_ptr<Actor> actor,PxRigidBody* rigidBody)
{
//    PxD6Joint* d6Joint = PxD6JointCreate(*gPhysicsSDK, rigidBody, PxTransform::createIdentity(), nullptr, rigidBody->getGlobalPose());
    PxD6Joint* d6Joint = PxD6JointCreate(*gPhysicsSDK, rigidBody,rigidBody->getGlobalPose(), nullptr, PxTransform::createIdentity());
  

//    nxDesc.actor[0]                         = desc.actor[0];
//    nxDesc.actor[1]                         = desc.actor[1];
//    PxConstraintDesc myDesc;
//    desc..
    
    
    d6Joint->setMotion(PxD6Axis::eX, PxD6Motion::eFREE);
    d6Joint->setMotion(PxD6Axis::eY, PxD6Motion::eFREE);
    d6Joint->setMotion(PxD6Axis::eZ, PxD6Motion::eFREE);
    d6Joint->setMotion(PxD6Axis::eTWIST, PxD6Motion::eFREE);
    d6Joint->setMotion(PxD6Axis::eSWING1, PxD6Motion::eFREE);
    d6Joint->setMotion(PxD6Axis::eSWING2, PxD6Motion::eFREE);
    
//    d6Joint->setBreakForce(1000, 1000);
    //d6Joint->s
    
    return d6Joint;
}


PxVec3 getBoxSize(shared_ptr<Actor> actor, shared_ptr<MeshFilter> meshFilter)
{
	shared_ptr<Mesh> mesh = meshFilter->getMesh();

	glm::vec3 boundsMax = mesh->getBoundsMax();
	glm::vec3 boundsMin = mesh->getBoundsMin();

	PxVec3 boxSize(boundsMax.x - boundsMin.x,
		boundsMax.y - boundsMin.y,
		boundsMax.z - boundsMin.z);

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
	shared_ptr<Mesh> mesh = meshFilter->getMesh();

	glm::vec3 boundsMax = mesh->getBoundsMax();
	glm::vec3 boundsMin = mesh->getBoundsMin();

	PxVec3 boxSize(boundsMax.x - boundsMin.x,
		boundsMax.y - boundsMin.y,
		boundsMax.z - boundsMin.z);
	
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


PxShape* Physics::createBoxCollider(glm::vec3 halfExtent, glm::vec3 center, shared_ptr<Actor> actor)
{
    return createBoxCollider(glmVec3ToPhysXVec3(halfExtent),glmVec3ToPhysXVec3(center),actor);
}
PxShape* Physics::createBoxCollider(PxVec3 halfExtent, PxVec3 center, shared_ptr<Actor> actor)
{
    
	shared_ptr<RigidBody> rigidBody = actor->GetComponent<RigidBody>();
    
    PxShape* shape = nullptr;
	if (rigidBody)
	{
		shape = rigidBody->getRigidbody()->createShape(PxBoxGeometry(halfExtent), *defaultPhysicsMaterial->getMaterial());// , *defaultPhysicsMaterial);
	}
	else
	{
		shared_ptr<RigidStatic> rigidStatic = actor->GetComponent<RigidStatic>();
		if (!rigidStatic)
			rigidStatic = actor->AddComponent<RigidStatic>();
        
		shape = rigidStatic->getRigidDynamic()->createShape(PxBoxGeometry(halfExtent), *defaultPhysicsMaterial->getMaterial());
        shape->userData = (void*)actor.get();
        
	}
	shape->setLocalPose(PxTransform(center, PxQuat::createIdentity()));
    
	return shape;
}

PxShape* Physics::createBoxCollider(shared_ptr<Actor> actor)
{
	shared_ptr<MeshFilter> meshFilter = actor->GetComponent<MeshFilter>();

	PxVec3 center(0, 0, 0);
	PxVec3 boxSize(0.5f, 0.5f, 0.5f);
	if (meshFilter)
	{
		boxSize = getBoxSize(actor, meshFilter);
		center = PxVec3(glmVec3ToPhysXVec3( meshFilter->getMesh()->getAverageCenter()));
	}

    return createBoxCollider(boxSize,center,actor);
    
	
}


PxShape* Physics::createSphereCollider(float radius, glm::vec3 center, shared_ptr<Actor> actor)
{
    return createSphereCollider(radius,glmVec3ToPhysXVec3(center),actor);
}

PxShape* Physics::createSphereCollider(float radius, PxVec3 center, shared_ptr<Actor> actor)
{
	shared_ptr<RigidBody> rigidBody = actor->GetComponent<RigidBody>();
	
	PxShape* shape = nullptr;
	if (rigidBody)
	{
        
		shape = rigidBody->getRigidbody()->createShape(PxSphereGeometry(radius), *defaultPhysicsMaterial->getMaterial());
	}
	else
	{
        
		shared_ptr<RigidStatic> rigidStatic = actor->GetComponent<RigidStatic>();
		if (!rigidStatic)
			rigidStatic = actor->AddComponent<RigidStatic>();
        
		shape = rigidStatic->getRigidDynamic()->createShape(PxSphereGeometry(radius), *defaultPhysicsMaterial->getMaterial());
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

		center = PxVec3(glmVec3ToPhysXVec3(meshFilter->getMesh()->getAverageCenter()));
	}
    return createSphereCollider(radius, center, actor);
}


void getCapsuleGeometry(shared_ptr<Actor>actor,shared_ptr<MeshFilter>meshFilter,float &radius,float &halfHeight,RotateAxis&orientation)
{
	shared_ptr<Mesh> mesh = meshFilter->getMesh();

	glm::vec3 boundsMax = mesh->getBoundsMax();
	glm::vec3 boundsMin = mesh->getBoundsMin();

	PxVec3 boxSize(boundsMax.x - boundsMin.x,
		boundsMax.y - boundsMin.y,
		boundsMax.z - boundsMin.z);
	
    boxSize = boxSize / 2;
	
    boxSize.x = std::fmaxf(boxSize.x, 0.001f);
    boxSize.y = std::fmaxf(boxSize.y, 0.001f);
    boxSize.z = std::fmaxf(boxSize.z, 0.001f);
	
    boxSize.x *= actor->transform->scale.x;
    boxSize.y *= actor->transform->scale.y;
    boxSize.z *= actor->transform->scale.z;
    
    bool maxX, maxY, maxZ;
    maxX = maxY = maxZ = false;
    if(boxSize.x > boxSize.y && boxSize.x > boxSize.z)
        maxX = true;
    else if(boxSize.y > boxSize.x && boxSize.y > boxSize.z)
        maxY = true;
    else if(boxSize.z > boxSize.y && boxSize.z > boxSize.x)
        maxZ = true;
    
    if(maxX)
    {
        orientation = RotateAxis::x;
        halfHeight = boxSize.x / 2;
        radius = boxSize.y/2;
    }
    else if(maxY)
    {
        orientation = RotateAxis::y;
        halfHeight = boxSize.y / 2;
        radius = boxSize.x/2;
    }
    else if(maxZ)
    {
        orientation = RotateAxis::z;
        halfHeight = boxSize.z / 2;
        radius = boxSize.y/2;
    }
    
    
}

void Physics::setCapsuleOrientation(PxShape* shape,RotateAxis orientation)
{
	PxTransform transform = shape->getLocalPose();
	switch (orientation)
	{
        case x:
            shape->setLocalPose(PxTransform(transform.p, PxQuat::createIdentity()));
            break;
        case z:
            shape->setLocalPose(PxTransform(transform.p, PxQuat(Deg2Radian * 90, PxVec3(0,1,0))));
            break;
        case y:
            shape->setLocalPose(PxTransform(transform.p, PxQuat(Deg2Radian * 90, PxVec3(0, 0, 1))));
            break;
        default:
            break;
	}
}

PxShape* Physics::createCapsuleCollider(float radius, float halfHeight, RotateAxis orientation, glm::vec3 center, shared_ptr<Actor> actor)
{
    return createCapsuleCollider(radius,halfHeight,orientation,glmVec3ToPhysXVec3(center),actor);
}

PxShape* Physics::createCapsuleCollider(float radius, float halfHeight, RotateAxis orientation, PxVec3 center, shared_ptr<Actor> actor)
{
	shared_ptr<RigidBody> rigidBody = actor->GetComponent<RigidBody>();
	
    PxShape* shape = nullptr;
	if (rigidBody)
	{
		shape = rigidBody->getRigidbody()->createShape(PxCapsuleGeometry(radius, halfHeight), *defaultPhysicsMaterial->getMaterial());
	}
	else
	{
		
		shared_ptr<RigidStatic> rigidStatic = actor->GetComponent<RigidStatic>();
		if (!rigidStatic)
			rigidStatic = actor->AddComponent<RigidStatic>();
        
		shape = rigidStatic->getRigidDynamic()->createShape(PxCapsuleGeometry(radius, halfHeight), *defaultPhysicsMaterial->getMaterial());
		shape->userData = (void*)actor.get();
	}
    
    setCapsuleOrientation(shape,orientation);
    
	return shape;
}


PxShape* Physics::createCapsuleCollider(shared_ptr<Actor> actor)
{
	shared_ptr<RigidBody> rigidBody = actor->GetComponent<RigidBody>();

    shared_ptr<MeshFilter> meshFilter = actor->GetComponent<MeshFilter>();
    
	PxVec3 center(0,0,0);
	float radius = 0.5f;// PxVec3 boxSize(0.5f, 0.5f, 0.5f);
    float halfHeight = 0.5f;
    RotateAxis orientation = RotateAxis::x;
	
    if (meshFilter)
	{
        getCapsuleGeometry(actor,meshFilter,radius,halfHeight,orientation);
		radius = getSphereSize(actor, meshFilter);
        
		center = PxVec3(glmVec3ToPhysXVec3(meshFilter->getMesh()->getAverageCenter()));
	}
    return  createCapsuleCollider(radius, halfHeight,orientation, center, actor);
}

bool Physics::convexMeshComputed(shared_ptr<Mesh> mesh)
{
    map<shared_ptr<Mesh>,PxConvexMesh* >::iterator it;
    it = convexMeshes.find(mesh);
    
    if(it == convexMeshes.end())
        return false;
    
    else
        return true;
}

PxConvexMesh* Physics::getPxConvexMesh(shared_ptr<Mesh> mesh)
{
    
    
    if(convexMeshComputed(mesh))
        return convexMeshes[mesh];

	//desc.points.
//    vector<glm::vec3> nonDupVertex = mesh->getNonDuplicateMeshVertex();
//
//	PxVec3* mMeshVertices = new physx::PxVec3[nonDupVertex.size()];
//	for (int i = 0; i < nonDupVertex.size(); i++)
//	{
//		mMeshVertices[i] = PxVec3(nonDupVertex[i].position.x, nonDupVertex[i].position.y, mesh->meshVertices[i].position.z);
//	}

//    vector<glm::vec3> vertexNoDup = mesh->getNonDuplicateMeshVertex();
//    vector<int> usedIndexes;
//    vector<int> tris;
//    
//    convexHull(vertexNoDup, usedIndexes, tris);
//    
//    	PxVec3* mMeshVertices = new physx::PxVec3[usedIndexes.size()];
//    	for (int i = 0; i < usedIndexes.size(); i++)
//    	{
//            mMeshVertices[i] = glmVec3ToPhysXVec3(vertexNoDup[usedIndexes[i]]);
//            
//    		//mMeshVertices[i] = PxVec3(mesh->meshVertices[i].position.x, mesh->meshVertices[i].position.y, mesh->meshVertices[i].position.z);
//    	}
//    	PxU32* triangles = new PxU32[mesh->triangles.size()];
//    	for (int i = 0; i < tris.size(); i++)
//    	{
//    		triangles[i] = tris[i];
//    	}
    
    
    vector<glm::vec3> nonDupVertex = mesh->getNonDuplicateMeshVertex();
    
//	PxVec3* mMeshVertices = new physx::PxVec3[mesh->meshVertices.size()];
//	for (int i = 0; i < mesh->meshVertices.size(); i++)
//	{
//		mMeshVertices[i] = PxVec3(mesh->meshVertices[i].position.x, mesh->meshVertices[i].position.y, mesh->meshVertices[i].position.z);
//	}
//	PxU32* triangles = new PxU32[mesh->triangles.size()];
//	for (int i = 0; i < mesh->triangles.size(); i++)
//	{
//		triangles[i] = mesh->triangles[i];
//	}

//	PxSimpleTriangleMesh triangleMesh;
//	//desc.
//	//PxSimpleTriangleMesh triangleMesh;
//	triangleMesh.points.count = mesh->meshVertices.size();
//	triangleMesh.points.stride = sizeof(PxVec3);
//	triangleMesh.points.data = mMeshVertices;

//	triangleMesh.triangles.count = mesh->triangles.size();
//	triangleMesh.triangles.stride = 3*sizeof(PxU32);
//	triangleMesh.triangles.data = triangles;

	PxSimpleTriangleMesh triangleMesh;
	//desc.
	//PxSimpleTriangleMesh triangleMesh;
	triangleMesh.points.count = nonDupVertex.size();
	triangleMesh.points.stride = sizeof(glm::vec3);
	triangleMesh.points.data = &nonDupVertex[0];
    
//	triangleMesh.triangles.count = tris.size();
//	triangleMesh.triangles.stride = 3*sizeof(PxU32);
//	triangleMesh.triangles.data = triangles;
    
	//triangleMesh.flags = PxMeshFlag::eFLIPNORMALS;

	bool ok = triangleMesh.isValid();


//	PhysXAllocatorCallback callback;

	PxCooking *cooking = PxCreateCooking(PX_PHYSICS_VERSION, PxGetFoundation(), PxCookingParams(PxTolerancesScale()));

//    physx::PxConvexMesh* convexMesh2 = PxToolkit::createConvexMesh(*gPhysicsSDK, *cooking, mMeshVertices, usedIndexes.size(), PxConvexFlag::eCOMPUTE_CONVEX);
//    physx::PxConvexMesh* convexMesh2 = PxToolkit::createConvexMesh(*gPhysicsSDK, *cooking, mMeshVertices, mesh->meshVertices.size(),  PxConvexFlag::eCOMPUTE_CONVEX);
//    
//
//    if(convexMesh2 == nullptr)
//    {
//        convexMesh2 = PxToolkit::createConvexMesh(*gPhysicsSDK, *cooking, mMeshVertices, mesh->meshVertices.size(),  PxConvexFlag::eINFLATE_CONVEX | PxConvexFlag::eCOMPUTE_CONVEX);
//        
//    }
//    
//    cooking->release();
//    delete []mMeshVertices;
//    
//    return convexMesh2;
	
    //PxPhysicsInsertionCallback

	//cooking->createTriangleMesh(triangleMeshDesc,pxdefaultinser)

//	PxU32 nbVertices, nbIndices, nbPolygons ;
//	PxU32 *indices ;
//	PxHullPolygon *polygons;
//	PxVec3 *vertices;

	
//    PxDefaultAllocator defaultAllocator;
    
	//cooking->cre
	//cooking->createTriangleMesh()
	//bool status = cooking->computeHullPolygons(triangleMesh, defaultAllocator, nbVertices, vertices, nbIndices, indices, nbPolygons, polygons);

    PxConvexMeshDesc convexDesc;
	convexDesc.points.count = nonDupVertex.size();
	convexDesc.points.stride = sizeof(glm::vec3);
	convexDesc.points.data = &nonDupVertex[0];

    
//	PxConvexMeshDesc convexDesc;
//	convexDesc.points.count = nbVertices;
//	convexDesc.points.stride = sizeof(PxVec3);
//	convexDesc.points.data = vertices;
	
//	convexDesc.indices.count = nbIndices;
//	convexDesc.indices.stride = sizeof(PxU32);
//	convexDesc.indices.data = indices;
//
//	convexDesc.polygons.count = nbPolygons;
//	convexDesc.polygons.stride = sizeof(PxHullPolygon);
//	convexDesc.polygons.data = polygons;
    
    convexDesc.flags = PxConvexFlag::eCOMPUTE_CONVEX;

	PxDefaultMemoryOutputStream output;
	
	bool status = cooking->cookConvexMesh(convexDesc, output);
    if(!status)
    {
        
        cout << "Was not able to create Convex Mesh for Mesh Collider, trying to inflate." << endl;
        
        convexDesc.flags =PxConvexFlag::eCOMPUTE_CONVEX | PxConvexFlag::eINFLATE_CONVEX;
        
        status = cooking->cookConvexMesh(convexDesc, output);
        if(!status)
        {
                    cout << "Was not able create Convex Mesh for Mesh Collider using eInflate." << endl;
            
            return nullptr;
        }
    }
	
	PxDefaultMemoryInputData input(output.getData(), output.getSize());
	physx::PxConvexMesh* convexMesh = gPhysicsSDK->createConvexMesh(input);
    
    convexMeshes[mesh] = convexMesh;
	
	cooking->release();

	return convexMesh;

	//PxU32* mMeshFaces = new physx::PxU32[mIndexCount];
}

PxShape* Physics::createMeshCollider(shared_ptr<Actor> actor)
{
	shared_ptr<RigidBody> rigidBody = actor->GetComponent<RigidBody>();
	shared_ptr<MeshFilter> meshFilter = actor->GetComponent<MeshFilter>();

    if(!meshFilter)
    {
        cerr << "Trying to add a MeshCollider to an actor that has no MeshFilter" << endl;
        
        return nullptr;
    }
    
	PxConvexMeshGeometry geo(getPxConvexMesh(meshFilter->getMesh()));
	PxShape* shape = nullptr;
	if (rigidBody)
	{
		
		shape = rigidBody->getRigidbody()->createShape(geo, *defaultPhysicsMaterial->getMaterial());
	
	}
	else
	{

		shared_ptr<RigidStatic> rigidStatic = actor->GetComponent<RigidStatic>();
		if (!rigidStatic)
			rigidStatic = actor->AddComponent<RigidStatic>();
		//
		shape = rigidStatic->getRigidDynamic()->createShape(geo, *defaultPhysicsMaterial->getMaterial());
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

void Physics::applyRigidBodyConstraints(PxScene* scene)
{
	PxU32 nActiveTransforms;
	const PxActiveTransform* activeTransforms = scene->getActiveTransforms(nActiveTransforms);
    
	for (int i = 0; i < nActiveTransforms; i++)
	{
		const PxActiveTransform activeTransform = activeTransforms[i];
        
		Actor*a = (Actor*)(activeTransform.userData);
	
        shared_ptr<RigidBody> rigidBody = a->GetComponent<RigidBody>();
        
        
		PxVec3 currentVelocity = rigidBody->getRigidbody()->getLinearVelocity();
		PxVec3 angularVelocity = rigidBody->getRigidbody()->getAngularVelocity();
        if(rigidBody->lockMoveX)
            currentVelocity.x = 0;
        if(rigidBody->lockMoveY)
            currentVelocity.y = 0;
        if(rigidBody->lockMoveZ)
            currentVelocity.z = 0;

        if(rigidBody->lockRotateX)
            angularVelocity.x = 0;
        if(rigidBody->lockRotateY)
            angularVelocity.y = 0;
        if(rigidBody->lockRotateZ)
            angularVelocity.z = 0;
        
		rigidBody->getRigidbody()->setLinearVelocity(currentVelocity);
		rigidBody->getRigidbody()->setAngularVelocity(angularVelocity);
        
	}
}

void Physics::tickScene(PxScene* scene)
{
    //applyRigidBodyConstraints(scene);
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
    convexMeshes.clear();
    
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
	scene->setVisualizationParameter(PxVisualizationParameter::eACTOR_AXES, 2.0f);
	scene->setVisualizationParameter(PxVisualizationParameter::eCOLLISION_SHAPES, 1.0f);

	return scene;
}


