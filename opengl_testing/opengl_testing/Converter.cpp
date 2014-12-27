#include "Converter.hpp"
#include "Transform.hpp"

PxVec3 glmVec3ToPhysXVec3(const glm::vec3& vec3)
{
	return PxVec3(vec3.x, vec3.y, vec3.z);
}

PxQuat glmQuatToPhysXQuat(const glm::quat& quat)
{
	return PxQuat(quat.x, quat.y, quat.z, quat.w);
}

glm::vec3 PhysXVec3ToglmVec3(const PxVec3& vec3)
{
	return glm::vec3(vec3.x, vec3.y, vec3.z);
}

glm::quat PhysXQuatToglmQuat(const PxQuat& quat)
{
	return glm::quat(quat.w, quat.x, quat.y, quat.z);
}

PxTransform transformToPhysXTransform(const shared_ptr<Transform>& transform)
{
	return PxTransform(glmVec3ToPhysXVec3(transform->getGlobalPosition()), glmQuatToPhysXQuat(transform->rotationQuat));
}