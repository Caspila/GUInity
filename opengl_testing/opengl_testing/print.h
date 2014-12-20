#pragma once

#include "Module.h"
#include <glm\common.hpp>
#include <glm\gtx\quaternion.hpp>
#include <PxPhysicsAPI.h>
#include "Ray.h"
#include "Math.h"

class Transform;
using namespace physx;

ostream& operator<<(ostream& os, const glm::vec4& dt);
ostream& operator<<(ostream& os, const glm::vec3& dt);
ostream& operator<<(ostream& os, const glm::vec2& dt);

ostream& operator<<(ostream& os, const PxVec3& dt);

ostream& operator<<(ostream& os, const PxQuat& dt);
ostream& operator<<(ostream& os, const glm::quat& dt);

ostream& operator<<(ostream& os, const Ray& dt);
//PxVec3& assign(PxVec3& physxvec3, glm::vec3 const &glmvec3){ return PxVec3(glmvec3.x, glmvec3.y, glmvec3.z); }

PxVec3 glmVec3ToPhysXVec3(const glm::vec3& vec3);

PxQuat glmQuatToPhysXQuat(const glm::quat& quat);

glm::vec3 PhysXVec3ToglmVec3(const PxVec3& vec3);

glm::quat PhysXQuatToglmQuat(const PxQuat& quat);

PxMat44 glmMat4ToPhysXMat4(const glm::mat4&  mat);


PxTransform transformToPhysXTransform(const shared_ptr<Transform>& transform);