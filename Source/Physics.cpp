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

/** PhysX EventCallback */
PhysXEventCallback* Physics::physxEventCallback;
/** Reference to the PhysX System */
PxPhysics* Physics::gPhysicsSDK;
/** PhysX Error Callback */
PxDefaultErrorCallback Physics::gDefaultErrorCallback;
/** PhysX Allocator */
PxDefaultAllocator Physics::gDefaultAllocatorCallback;
/** PhysX Foundation */
PxFoundation* Physics::gFoundation;

/** Reference to the default Physics Material */
shared_ptr<PhysicsMaterial> Physics::defaultPhysicsMaterial;
/** Map that holds all the PxConvexMeshes that have been computed already */
map<shared_ptr<Mesh>,PxConvexMesh*> Physics::convexMeshes;
/** Physics timeStep */
PxReal Physics::timeStep = 1.0f / 60.0f;
/** Time Accumulator to run on fixed timeStep */
float Physics::timeAccumulator = 0.0f;

PxFilterFlags CustomSimulationFilterShader(
                                           PxFilterObjectAttributes attribute0, PxFilterData filterData0,
                                           PxFilterObjectAttributes attribute1, PxFilterData filterData1,
                                           PxPairFlags& pairFlags, const void* constantBlock, PxU32 constantBlockSize)
{
	
    
	if ((attribute0 & PxFilterObjectFlag::eTRIGGER) != 0 || (attribute1 & PxFilterObjectFlag::eTRIGGER) != 0)
	{
		pairFlags = PxPairFlag::eTRIGGER_DEFAULT;
        
		return PxFilterFlags();
	}
    
	pairFlags = PxPairFlag::eCONTACT_DEFAULT | PxPairFlag::eNOTIFY_TOUCH_FOUND;
    
	return PxFilterFlags();
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
    
	
	defaultPhysicsMaterial = AssetDatabase::createPhysicsMaterial("default",0.5f, 0.5f, 0.1f);
    
    
    return 0;
}

/** Gets current debug render state
 @param[in]scene The scene
 @return true if render debug is enabled, false otherwise */
bool Physics::getDebugRendererMode(PxScene* scene)
{
    cout << "eScale: " <<scene->getVisualizationParameter(PxVisualizationParameter::eSCALE);
    return compareFloat(scene->getVisualizationParameter(PxVisualizationParameter::eSCALE),1.0f);
}

/** Sets the render debug enabled or disabled
 @param[in]scene The scene
 @param[in]debugRenderEnabled true to enable render debug, false otherwise */
void Physics::setDebugRendererMode(PxScene* scene, bool debugRenderEnabled)
{

    float value = debugRenderEnabled? 1.0f : 0.0f;
    
        cout << "value: " <<value;
    
    scene->setVisualizationParameter(PxVisualizationParameter::eSCALE, value);
}

/** Toggles between render or not render debug 
  @param[in]scene The scene*/
void Physics::toggleDebugVisualization(PxScene* scene)
{
    setDebugRendererMode(scene,!getDebugRendererMode(scene));
}

/** Create a PhysX scene
 @return The created scene
 */
PxScene* Physics::createPhysicsScene()
{
    
	//Creating scene
	PxSceneDesc sceneDesc(gPhysicsSDK->getTolerancesScale());
	sceneDesc.flags = PxSceneFlag::eENABLE_ACTIVETRANSFORMS;
	sceneDesc.simulationEventCallback = physxEventCallback;
	sceneDesc.gravity = PxVec3(0.0f, -9.8f, 0.0f);
	sceneDesc.cpuDispatcher = PxDefaultCpuDispatcherCreate(1);
	sceneDesc.filterShader = CustomSimulationFilterShader;
    
	PxScene* scene = gPhysicsSDK->createScene(sceneDesc);
    
	scene->setSimulationEventCallback(physxEventCallback);
	scene->setVisualizationParameter(PxVisualizationParameter::eSCALE, 1.0f);
	scene->setVisualizationParameter(PxVisualizationParameter::eACTOR_AXES, 2.0f);
	scene->setVisualizationParameter(PxVisualizationParameter::eCOLLISION_SHAPES, 1.0f);
    
	return scene;
}


/** defaultPhysicsMaterial Getter
 @return Reference to the default Physics Material
 */
shared_ptr<PhysicsMaterial> Physics::getDefaultMaterial()
{
	return defaultPhysicsMaterial;
}

/** Create a physics material
 @param[in] friction The friction of the material
 @param[in] dynamicFriction The dynamic friction of the material
 @param[in] restitution The restitution of the material
 @return The created Material */
PxMaterial* Physics::createMaterial(float friction, float dynamicFriction, float restitution)
{
    
	return gPhysicsSDK->createMaterial(friction, dynamicFriction, restitution);
}


/** Create a rigid dynamic
 @param[in] actor Actor which Transform will be copied to create the rigid dynamic
 @return Created rigid dynamic */
PxRigidDynamic* Physics::createRigidDynamic(shared_ptr<Actor> actor)
{
	PxTransform physxTransform = transformToPhysXTransform(actor->transform);
    
	PxRigidDynamic* rigidDynamic = gPhysicsSDK->createRigidDynamic(physxTransform);
    
	rigidDynamic->userData = static_cast<void*> (actor.get());
    
	return rigidDynamic;
}

/** Create a d6 joint (fully configurable joint)
 @param[in] actor Actor which Transform will be copied to create the rigid dynamic
 @return Created d6 joint */
PxD6Joint* Physics::createD6Joint(shared_ptr<Actor> actor,PxRigidBody* rigidBody)
{
    
    PxD6Joint* d6Joint = PxD6JointCreate(*gPhysicsSDK, rigidBody,rigidBody->getGlobalPose(), nullptr, PxTransform::createIdentity());
    
    d6Joint->setMotion(PxD6Axis::eX, PxD6Motion::eFREE);
    d6Joint->setMotion(PxD6Axis::eY, PxD6Motion::eFREE);
    d6Joint->setMotion(PxD6Axis::eZ, PxD6Motion::eFREE);
    d6Joint->setMotion(PxD6Axis::eTWIST, PxD6Motion::eFREE);
    d6Joint->setMotion(PxD6Axis::eSWING1, PxD6Motion::eFREE);
    d6Joint->setMotion(PxD6Axis::eSWING2, PxD6Motion::eFREE);
    
    return d6Joint;
}


/** Update Actors transform based on Physics simulation
 @param[in] scene The physics scene
 */
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

/** Create a box collider
 @param[in] halfExtent Half extent of the AABB
 @param[in] center The position of the center of the collider
 @param[in] actor The Actor. The actor is needed because if it does not contain a RigidBody or a RigidStatic one must be added first.
 @return The created shape*/
PxShape* Physics::createBoxCollider(glm::vec3 halfExtent, glm::vec3 center, shared_ptr<Actor> actor)
{
    return createBoxCollider(glmVec3ToPhysXVec3(halfExtent),glmVec3ToPhysXVec3(center),actor);
}
/** Create a box collider
 @param[in] halfExtent Half extent of the AABB
 @param[in] center The position of the center of the collider
 @param[in] actor The Actor. The actor is needed because if it does not contain a RigidBody or a RigidStatic one must be added first.
 @return The created shape*/
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


/** Create a sphere collider
 @param[in] radius The radius of the sphere
 @param[in] center The position of the center of the collider
 @param[in] actor The Actor. The actor is needed because if it does not contain a RigidBody or a RigidStatic one must be added first.
 @return The created shape*/
PxShape* Physics::createSphereCollider(float radius, glm::vec3 center, shared_ptr<Actor> actor)
{
    return createSphereCollider(radius,glmVec3ToPhysXVec3(center),actor);
}
/** Create a sphere collider
 @param[in] radius The radius of the sphere
 @param[in] center The position of the center of the collider
 @param[in] actor The Actor. The actor is needed because if it does not contain a RigidBody or a RigidStatic one must be added first.
 @return The created shape*/
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


/** Set the orientation of the capsule
 @param[in,out] shape The shape that will be oriented
 @param[in] orientation The orientation of the capsule
 */
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

/** Create a capsule collider
 @param[in] radius The radius of the sphere
 @param[in] height Half height of the capsule
 @param[in] orientation The orientation of the capsule
 @param[in] center The position of the center of the collider
 @param[in] actor The Actor. The actor is needed because if it does not contain a RigidBody or a RigidStatic one must be added first.
 @return The created shape*/
PxShape* Physics::createCapsuleCollider(float radius, float halfHeight, RotateAxis orientation, glm::vec3 center, shared_ptr<Actor> actor)
{
    return createCapsuleCollider(radius,halfHeight,orientation,glmVec3ToPhysXVec3(center),actor);
}

/** Create a capsule collider
 @param[in] radius The radius of the sphere
 @param[in] height Half height of the capsule
 @param[in] center The position of the center of the collider
 @param[in] actor The Actor. The actor is needed because if it does not contain a RigidBody or a RigidStatic one must be added first.
 @return The created shape*/
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

/** Checks the map to see if the ConvexMesh has already been computed for the Mesh
 @param[in] mesh The Mesh to be checked
 */
bool Physics::convexAlreadyComputed(shared_ptr<Mesh> mesh)
{
    map<shared_ptr<Mesh>,PxConvexMesh* >::iterator it;
    it = convexMeshes.find(mesh);
    
    if(it == convexMeshes.end())
        return false;
    
    else
        return true;
}

/** Get the convex shape of a Mesh
 @param[in] mesh The mesh to extract the convex shape from
 @return The convex shape
 */
PxConvexMesh* Physics::getPxConvexMesh(shared_ptr<Mesh> mesh)
{
    if(convexAlreadyComputed(mesh))
        return convexMeshes[mesh];
    
    vector<glm::vec3> nonDupVertex = mesh->getNonDuplicateMeshVertex();
    
	PxSimpleTriangleMesh triangleMesh;
    
	triangleMesh.points.count = nonDupVertex.size();
	triangleMesh.points.stride = sizeof(glm::vec3);
	triangleMesh.points.data = &nonDupVertex[0];
    
	bool ok = triangleMesh.isValid();
    
    
	PxCooking *cooking = PxCreateCooking(PX_PHYSICS_VERSION, PxGetFoundation(), PxCookingParams(PxTolerancesScale()));
    
    PxConvexMeshDesc convexDesc;
	convexDesc.points.count = nonDupVertex.size();
	convexDesc.points.stride = sizeof(glm::vec3);
	convexDesc.points.data = &nonDupVertex[0];
    
    
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
    
}

/** Create a mesh collider
 @param[in] actor The Actor. Tries to find a MeshFilter and use the Mesh to create the collider
 @return The created shape*/
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



/** Cast a ray looking for colliders that intersect with it
 @param[in] scene The PhysX scene
 @param[in] r The ray
 @param[in] distance Max distance of the ray
 @param[out] hitCallback Holds intersection data
 @return true if any collision was found, false otherwise
 */
bool Physics::rayCast(PxScene* scene, const Ray& r, const float distance, PxRaycastBuffer& hitCallback)
{
	return scene->raycast(glmVec3ToPhysXVec3(r.origin), glmVec3ToPhysXVec3(r.direction), distance, hitCallback);
}

/** Ticks a physics scene
 @param[in,out] scene The scene to tick
 */
void Physics::tickScene(float deltaSeconds, PxScene* scene)
{
    timeAccumulator += deltaSeconds;
    
    if(timeAccumulator < timeStep)
        return;
    
    timeAccumulator -= timeStep;

 
    
	scene->simulate(timeStep);
	scene->fetchResults(true);

    Physics::updateActorsTransform(scene);   
}

/** Shut down and release allocated memory */
void Physics::shutdown()
{
    convexMeshes.clear();
    
	gPhysicsSDK->release();
	gFoundation->release();
	
}

