#pragma once

#include "Module.hpp"
#include <glm/common.hpp>
#include <glm/gtx/quaternion.hpp>
#include <PxPhysicsAPI.h>

class Transform;
using namespace physx;

PxVec3 glmVec3ToPhysXVec3(const glm::vec3& vec3);

PxQuat glmQuatToPhysXQuat(const glm::quat& quat);

glm::vec3 PhysXVec3ToglmVec3(const PxVec3& vec3);

glm::quat PhysXQuatToglmQuat(const PxQuat& quat);

PxTransform transformToPhysXTransform(const shared_ptr<Transform>& transform);

PxMat44 glmMat4ToPhysxMat4(const glm::mat4& mat4);
