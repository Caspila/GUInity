#include "Converter.hpp"
#include "Transform.hpp"


/** Convert glm::vec3 to Physx::PxVec3 */
PxVec3 glmVec3ToPhysXVec3(const glm::vec3& vec3)
{
	return PxVec3(vec3.x, vec3.y, vec3.z);
}
/** Convert glm::quat to Physx::PxQuat */
PxQuat glmQuatToPhysXQuat(const glm::quat& quat)
{
	return PxQuat(quat.x, quat.y, quat.z, quat.w);
}
/** Convert Physx::PxVec3 to glm::vec3*/
glm::vec3 PhysXVec3ToglmVec3(const PxVec3& vec3)
{
	return glm::vec3(vec3.x, vec3.y, vec3.z);
}
/** Convert Physx::PxQuat to glm::quat*/
glm::quat PhysXQuatToglmQuat(const PxQuat& quat)
{
	return glm::quat(quat.w, quat.x, quat.y, quat.z);
}

/** Convert Transform (position and rotation) to Physx::PxTransform*/
PxTransform transformToPhysXTransform(const shared_ptr<Transform>& transform)
{
	return PxTransform(glmVec3ToPhysXVec3(transform->getWorldPosition()), glmQuatToPhysXQuat(transform->rotation));
}

/** Convert glm::mat4 to PhysX::PxMat44*/
PxMat44 glmMat4ToPhysxMat4(const glm::mat4& mat4)
{
    PxMat44 newMat;
    
    newMat[0][0] = mat4[0][0];
    newMat[0][1] = mat4[0][1];
    newMat[0][2] = mat4[0][2];
    newMat[0][3] = mat4[0][3];
    
    newMat[1][0] = mat4[1][0];
    newMat[1][1] = mat4[1][1];
    newMat[1][2] = mat4[1][2];
    newMat[1][3] = mat4[1][3];
    
    newMat[2][0] = mat4[2][0];
    newMat[2][1] = mat4[2][1];
    newMat[2][2] = mat4[2][2];
    newMat[2][3] = mat4[2][3];
    
    newMat[3][0] = mat4[3][0];
    newMat[3][1] = mat4[3][1];
    newMat[3][2] = mat4[3][2];
    newMat[3][3] = mat4[3][3];

    
    return newMat;
}

/** Convert PhysX::PxMat44 to glm::mat4*/
void PhysXMat4ToglmMat4(const PxMat44& mat4,glm::mat4& newMat)
{

	newMat[0][0] = mat4[0][0];
	newMat[0][1] = mat4[0][1];
	newMat[0][2] = mat4[0][2];
	newMat[0][3] = mat4[0][3];

	newMat[1][0] = mat4[1][0];
	newMat[1][1] = mat4[1][1];
	newMat[1][2] = mat4[1][2];
	newMat[1][3] = mat4[1][3];

	newMat[2][0] = mat4[2][0];
	newMat[2][1] = mat4[2][1];
	newMat[2][2] = mat4[2][2];
	newMat[2][3] = mat4[2][3];

	newMat[3][0] = mat4[3][0];
	newMat[3][1] = mat4[3][1];
	newMat[3][2] = mat4[3][2];
	newMat[3][3] = mat4[3][3];

}

/** Convert FBX Matrix to glm::mat4*/
void fbxMat4ToglmMat4(const FbxAMatrix& mat4, glm::mat4& newMat)
{
    newMat[0][0] = mat4[0][0];
	newMat[0][1] = mat4[0][1];
	newMat[0][2] = mat4[0][2];
	newMat[0][3] = mat4[0][3];
    
	newMat[1][0] = mat4[1][0];
	newMat[1][1] = mat4[1][1];
	newMat[1][2] = mat4[1][2];
	newMat[1][3] = mat4[1][3];
    
	newMat[2][0] = mat4[2][0];
	newMat[2][1] = mat4[2][1];
	newMat[2][2] = mat4[2][2];
	newMat[2][3] = mat4[2][3];
    
	newMat[3][0] = mat4[3][0];
	newMat[3][1] = mat4[3][1];
	newMat[3][2] = mat4[3][2];
	newMat[3][3] = mat4[3][3];
}