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

//    newMat[0][0] = mat4[0][0];
//    newMat[0][1] = mat4[1][0];
//    newMat[0][2] = mat4[2][0];
//    newMat[0][3] = mat4[3][0];
//    
//    newMat[1][0] = mat4[0][0];
//    newMat[1][1] = mat4[1][0];
//    newMat[1][2] = mat4[2][0];
//    newMat[1][3] = mat4[3][0];
//    
//    newMat[2][0] = mat4[0][0];
//    newMat[2][1] = mat4[1][0];
//    newMat[2][2] = mat4[2][0];
//    newMat[2][3] = mat4[3][0];
//    
//    newMat[3][0] = mat4[0][0];
//    newMat[3][1] = mat4[1][0];
//    newMat[3][2] = mat4[2][0];
//    newMat[3][3] = mat4[3][0];
    
    return newMat;
}