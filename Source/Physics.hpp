#pragma once
#include <PxPhysicsAPI.h>
#include "Ray.hpp"
#include "PhysXEventCallback.hpp"
#include "Enums.hpp"
#include <map>


class Actor;
class PhysicsMaterial;
class Mesh;
class MeshFilter;
class Transform;

using namespace physx;


class Physics
{
private:
    /** Reference to the default Physics Material */
	static shared_ptr<PhysicsMaterial> defaultPhysicsMaterial;
    
    /** Map that holds all the PxConvexMeshes that have been computed already */
    static map<shared_ptr<Mesh>,PxConvexMesh*> convexMeshes;
    
    /** Physics timeStep */
    static PxReal timeStep;
    /** Time Accumulator to run on fixed timeStep */
    static float timeAccumulator;
    
   
    
public:
    
    /** Initialize the PhysX scene */
	int init();
    
    /** Reference to the PhysX System */
	static PxPhysics* gPhysicsSDK;
    /** PhysX Error Callback */
	static PxDefaultErrorCallback gDefaultErrorCallback;
    /** PhysX Allocator */
	static PxDefaultAllocator gDefaultAllocatorCallback;
    /** PhysX Foundation */
	static PxFoundation* gFoundation;
    /** PhysX EventCallback */
	static PhysXEventCallback* physxEventCallback;
    

    /** debugRenderEnabled Setter
     @param[in]scene The scene
     @param[in]debugRenderEnabled true to enable render debug, false otherwise */
    static void setDebugRendererMode(PxScene* scene, bool debugRenderEnabled);
    
    /** debugRenderEnabled Setter
     @param[in]scene The scene
     @return true if render debug is enabled, false otherwise */
    static bool getDebugRendererMode(PxScene* scene);
    
    /** Toggles between render or not render debug
     @param[in]scene The scene*/
    static void toggleDebugVisualization(PxScene* scene);
    
    /** Create a PhysX scene
     @return The created scene
     */
	static PxScene* createPhysicsScene();
    
    /** Cast a ray looking for colliders that intersect with it
     @param[in] scene The PhysX scene
     @param[in] r The ray
     @param[in] distance Max distance of the ray
     @param[out] hitCallback Holds intersection data
     @return true if any collision was found, false otherwise
     */
	static bool rayCast(PxScene* scene, const Ray& r, const float distance, PxRaycastBuffer& hitCallback);
    
    /** Create a physics material
     @param[in] friction The friction of the material
     @param[in] dynamicFriction The dynamic friction of the material
     @param[in] restitution The restitution of the material
     @return The created Material */
    static PxMaterial* createMaterial(float friction, float dynamicFriction, float restitution);
    
    /** Create a rigid dynamic
     @param[in] actor Actor which Transform will be copied to create the rigid dynamic
     @return Created rigid dynamic */
	static PxRigidDynamic* createRigidDynamic(shared_ptr<Actor> actor);
    /** Create a d6 joint (fully configurable joint)
     @param[in] actor Actor which Transform will be copied to create the rigid dynamic
     @return Created d6 joint */
    static PxD6Joint* createD6Joint(shared_ptr<Actor> actor,PxRigidBody* rigidBody);
    
    /** Update Actors transform based on Physics simulation
     @param[in] scene The physics scene
     */
    static void updateActorsTransform(PxScene* scene);

    
    /** Create a box collider
     @param[in] halfExtent Half extent of the AABB
     @param[in] center The position of the center of the collider
     @param[in] actor The Actor. The actor is needed because if it does not contain a RigidBody or a RigidStatic one must be added first.
     @return The created shape */
	static PxShape* createBoxCollider(glm::vec3 halfExtent,glm::vec3 center, shared_ptr<Actor> actor);
    /** Create a box collider
     @param[in] halfExtent Half extent of the AABB
     @param[in] center The position of the center of the collider
     @param[in] actor The Actor. The actor is needed because if it does not contain a RigidBody or a RigidStatic one must be added first.
     @return The created shape*/
	static PxShape* createBoxCollider(PxVec3 halfExtent,PxVec3 center, shared_ptr<Actor> actor);

    
    
    /** Create a sphere collider
     @param[in] radius The radius of the sphere
     @param[in] center The position of the center of the collider
     @param[in] actor The Actor. The actor is needed because if it does not contain a RigidBody or a RigidStatic one must be added first.
     @return The created shape*/
    static PxShape* createSphereCollider(float radius, glm::vec3 center, shared_ptr<Actor> actor);
    /** Create a sphere collider
     @param[in] radius The radius of the sphere
     @param[in] center The position of the center of the collider
     @param[in] actor The Actor. The actor is needed because if it does not contain a RigidBody or a RigidStatic one must be added first.
     @return The created shape*/
    static PxShape* createSphereCollider(float radius, PxVec3 center, shared_ptr<Actor> actor);

    
    
    /** Set the orientation of the capsule
     @param[in,out] shape The shape that will be oriented
     @param[in] orientation The orientation of the capsule
     */
    static void setCapsuleOrientation(PxShape* shape,RotateAxis orientation);
    
    /** Create a capsule collider
     @param[in] radius The radius of the sphere
     @param[in] height Half height of the capsule
     @param[in] orientation The orientation of the capsule
     @param[in] center The position of the center of the collider
     @param[in] actor The Actor. The actor is needed because if it does not contain a RigidBody or a RigidStatic one must be added first.
     @return The created shape*/
    static PxShape* createCapsuleCollider(float radius, float halfHeight, RotateAxis orientation, glm::vec3 center, shared_ptr<Actor> actor);
    /** Create a capsule collider
     @param[in] radius The radius of the sphere
     @param[in] height Half height of the capsule
     @param[in] center The position of the center of the collider
     @param[in] actor The Actor. The actor is needed because if it does not contain a RigidBody or a RigidStatic one must be added first.
     @return The created shape*/
    static PxShape* createCapsuleCollider(float radius, float halfHeight, RotateAxis orientation, PxVec3 center, shared_ptr<Actor> actor);

    
    /** Create a mesh collider
     @param[in] actor The Actor. Tries to find a MeshFilter and use the Mesh to create the collider
     @return The created shape*/
    static PxShape* createMeshCollider(shared_ptr<Actor> actor);
    /** Get the convex shape of a Mesh
     @param[in] mesh The mesh to extract the convex shape from
     @return The convex shape
     */
	static PxConvexMesh* getPxConvexMesh(shared_ptr<Mesh> mesh);
    
    
    /** defaultPhysicsMaterial Getter
     @return Reference to the default Physics Material
     */
	static shared_ptr<PhysicsMaterial> getDefaultMaterial();
    
    /** Ticks a physics scene
     @param[in,out] scene The scene to tick
     */
	static void tickScene(float deltaSeconds, PxScene* scene);
    
    /** Shut down and release allocated memory */
	static void shutdown();
    
    
    
    /** Checks the map to see if the ConvexMesh has already been computed for the Mesh
     @param[in] mesh The Mesh to be checked
     */
    static bool convexAlreadyComputed(shared_ptr<Mesh> mesh);
};

