#pragma once

#include "Module.hpp"
#include <glm/common.hpp>
#include <glm/gtx/quaternion.hpp>
#include <PxPhysicsAPI.h>
#include <fbxsdk.h>

/** Helper class that converts mathematical structures */

class Transform;
using namespace physx;

/** Convert glm::vec3 to Physx::PxVec3 
 @param[in] vec3 The glm::vec3
 @return Converted Physx::PxVec3 */
PxVec3 glmVec3ToPhysXVec3(const glm::vec3& vec3);

/** Convert glm::quat to Physx::PxQuat
@param[in] quat The glm::quat
@return Converted Physx::PxQuat */

PxQuat glmQuatToPhysXQuat(const glm::quat& quat);

/** Convert Physx::PxVec3 to glm::vec3
 @param[in] vec3 The Physx::PxVec3
 @return Converted glm::vec3 */
glm::vec3 PhysXVec3ToglmVec3(const PxVec3& vec3);

/** Convert Physx::PxQuat to glm::quat
 @param[in] quat The Physx::PxQuat
 @return Converted glm::quat */
glm::quat PhysXQuatToglmQuat(const PxQuat& quat);

/** Convert Transform (position and rotation) to Physx::PxTransform
 @param[in] transform The transform that will be converted
 @return Converted Physx::PxTransform */
PxTransform transformToPhysXTransform(const shared_ptr<Transform>& transform);

/** Convert glm::mat4 to PhysX::PxMat44
 @param[in] mat4 The glm::mat4
 @return Converted PhysX::PxMat44 */
PxMat44 glmMat4ToPhysxMat4(const glm::mat4& mat4);

/** Convert PhysX::PxMat44 to glm::mat4
 @param[in] mat4 The PhysX::PxMat44
  @param[ou] Converted glm::mat4
*/
void PhysXMat4ToglmMat4(const PxMat44& mat4,glm::mat4& newMat);

/** Convert FBX Matrix to glm::mat4
 @param[in] mat4 The FbxAMatrix
 @param[ou] Converted glm::mat4
 */
void fbxMat4ToglmMat4(const FbxAMatrix& mat4, glm::mat4& newMat);
