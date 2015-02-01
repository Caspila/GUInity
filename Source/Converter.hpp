#pragma once

#include "Module.hpp"
#include <glm/common.hpp>
#include <glm/gtx/quaternion.hpp>
#include <PxPhysicsAPI.h>

/** Helper class that converts GLM mathematical structures to PhysX structures */

class Transform;
using namespace physx;

/** Convert glm::vec3 to Physx::PxVec3 */
PxVec3 glmVec3ToPhysXVec3(const glm::vec3& vec3);

/** Convert glm::quat to Physx::PxQuat */
PxQuat glmQuatToPhysXQuat(const glm::quat& quat);

/** Convert Physx::PxVec3 to glm::vec3*/
glm::vec3 PhysXVec3ToglmVec3(const PxVec3& vec3);

/** Convert Physx::PxQuat to glm::quat*/
glm::quat PhysXQuatToglmQuat(const PxQuat& quat);

/** Convert Transform (position and rotation) to Physx::PxTransform*/
PxTransform transformToPhysXTransform(const shared_ptr<Transform>& transform);

/** Convert glm::mat4 to PhysX::PxMat44*/
PxMat44 glmMat4ToPhysxMat4(const glm::mat4& mat4);

/** Convert PhysX::PxMat44 to glm::mat4*/
glm::mat4& mat4PhysXMat4ToglmMat4(const PxMat44& mat4);