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
shared_ptr<Mesh> MeshComponent::getMesh()
{
	return mesh;
}


/** Gets the center and the AABB size for the Actor that this component is attached to */
void MeshComponent::getBoxSize(shared_ptr<Actor> actor, PxVec3& boxSize, PxVec3& center)
{
	glm::vec3 boundsMax = mesh->getBoundsMax();
	glm::vec3 boundsMin = mesh->getBoundsMin();

	boxSize.x = boundsMax.x - boundsMin.x;
	boxSize.y = boundsMax.y - boundsMin.y;
	boxSize.z=boundsMax.z - boundsMin.z;

	boxSize = boxSize / 2;

	boxSize.x = std::fmaxf(boxSize.x, 0.001f);
	boxSize.y = std::fmaxf(boxSize.y, 0.001f);
	boxSize.z = std::fmaxf(boxSize.z, 0.001f);

	boxSize.x *= actor->transform->scale.x;
	boxSize.y *= actor->transform->scale.y;
	boxSize.z *= actor->transform->scale.z;


	center = glmVec3ToPhysXVec3(mesh->getAverageCenter());
}

/** Gets the center and the radius for the Actor that this component is attached to*/

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


	center = glmVec3ToPhysXVec3(mesh->getAverageCenter());
}

/** Gets the center and the capsule description for the Actor that this component is attached to*/
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
	center = glmVec3ToPhysXVec3(mesh->getAverageCenter());

}