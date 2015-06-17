#include "MeshComponent.hpp"

#include "Mesh.hpp"
#include "AssetDatabase.hpp"
#include "Math.hpp"
#include "Converter.hpp"
#include "Actor.hpp"
#include "Transform.hpp"

/** Default Constructor*/
MeshComponent::MeshComponent()
{

#ifdef GUINITY_DEBUG
	nCount++;
#endif
}

/** Default Destructor. Virtual because this is a parent class*/
MeshComponent::~MeshComponent()
{
#ifdef GUINITY_DEBUG
	nCount--;
	cout << "MeshComponent destroyed (" << nCount << " remaining)" << endl;
#endif
}

/** mesh Setter */
void MeshComponent::setMesh(shared_ptr<Mesh> mesh)
{
	this->mesh = mesh;
}

/** mesh Getter */
shared_ptr<Mesh> MeshComponent::getMesh() const
{
	return mesh;
}


/** Get the box size of a Mesh
 @param[in] transform The Transform is used to scale up or down the extent and fit the Actor
 @param[in] actor The MeshFilter that'll be used to extract the box extent
 @return Half extent of the AABB*/
void MeshComponent::getBoxSize(shared_ptr<Actor> actor, PxVec3& boxSize, PxVec3& center)
{
	glm::vec3 boundsMax = mesh->getBoundsMax();
	glm::vec3 boundsMin = mesh->getBoundsMin();

	boxSize.x = boundsMax.x - boundsMin.x;
	boxSize.y = boundsMax.y - boundsMin.y;
	boxSize.z = boundsMax.z - boundsMin.z;

	boxSize = boxSize / 2;

	boxSize.x = std::fmaxf(boxSize.x, 0.001f);
	boxSize.y = std::fmaxf(boxSize.y, 0.001f);
	boxSize.z = std::fmaxf(boxSize.z, 0.001f);

	boxSize.x *= actor->transform->scale.x;
	boxSize.y *= actor->transform->scale.y;
	boxSize.z *= actor->transform->scale.z;


    // TODO, TRY TO USE MESH AVG CENTER TO POSITION THE COLLIDER
    //    center = glmVec3ToPhysXVec3(mesh->getAverageCenter()) ;
}

/** Get the sphere size of a Mesh
 @param[in] transform The Transform is used to scale up or down the extent and fit the Actor
 @param[in] actor The MeshFilter that'll be used to extract the box extent
 @return The radius of the sphere*/
void MeshComponent::getSphereSize(shared_ptr<Actor> actor, float& radius, PxVec3& center)
{
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

	radius = fmaxf(boxSize.x, boxSize.y);
	radius = fmaxf(radius, boxSize.z);


// TODO, TRY TO USE MESH AVG CENTER TO POSITION THE COLLIDER
//    center = glmVec3ToPhysXVec3(mesh->getAverageCenter()) ;
}

/** Get the capsule extent and orientation of a Mesh
 @param[in] transform The Transform is used to scale up or down the extent and fit the Actor
 @param[in] actor The MeshFilter that'll be used to extract the box extent
 @param[out] radius The radius of the capsule
 @param[out] halfHeight Half height of the capsule
 @param[out] orientation The orientation of the capsule
 */
void MeshComponent::getCapsuleGeometry(shared_ptr<Actor>actor, float &radius, float &halfHeight, RotateAxis&orientation, PxVec3& center)
{
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
	if (boxSize.x > boxSize.y && boxSize.x > boxSize.z)
		maxX = true;
	else if (boxSize.y > boxSize.x && boxSize.y > boxSize.z)
		maxY = true;
	else if (boxSize.z > boxSize.y && boxSize.z > boxSize.x)
		maxZ = true;

	if (maxX)
	{
		orientation = RotateAxis::x;
		halfHeight = boxSize.x / 2;
		radius = boxSize.y / 2;
	}
	else if (maxY)
	{
		orientation = RotateAxis::y;
		halfHeight = boxSize.y / 2;
		radius = boxSize.x / 2;
	}
	else if (maxZ)
	{
		orientation = RotateAxis::z;
		halfHeight = boxSize.z / 2;
		radius = boxSize.y / 2;
	}
    
    // TODO, TRY TO USE MESH AVG CENTER TO POSITION THE COLLIDER
    //    center = glmVec3ToPhysXVec3(mesh->getAverageCenter()) ;

}