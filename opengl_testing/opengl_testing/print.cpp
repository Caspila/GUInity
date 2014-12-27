#include "print.hpp"
#include "Transform.hpp"
#include "Math.hpp"

ostream& operator<<(ostream& os, const glm::vec4& vec3)
{
	os << '(' << vec3.x << ',' << vec3.y << ',' << vec3.z << ',' << vec3.w << ')';
	return os;
}

ostream& operator<<(ostream& os, const glm::vec3& vec3)
{
	os << '(' << vec3.x << ',' << vec3.y << ',' << vec3.z << ')';
	return os;
}

ostream& operator<<(ostream& os, const glm::vec2& vec2)
{
	os << '(' << vec2.x << ',' << vec2.y <<')';
	return os;
}


ostream& operator<<(ostream& os, const PxVec3& vec3)
{
	os << '(' << vec3.x << ',' << vec3.y << ',' << vec3.z << ')';
	return os;
}

ostream& operator<<(ostream& os, const Ray& ray)
{
	os << "Origin: " << ray.origin << " Direction: " << ray.direction << endl;
	return os;
}

ostream& operator<<(ostream& os, const PxQuat& quat)
{
	os << '(' << quat.x << ',' << quat.y << ',' << quat.z << ',' << quat.w << ')';
	return os;
}

ostream& operator<<(ostream& os, const glm::quat& quat)
{
	os << '(' << quat.x << ',' << quat.y << ',' << quat.z << ',' << quat.w << ')';
	return os;
}

//PxVec3 glmVec3ToPhysXVec3(const glm::vec3& vec3)
//{
//	return PxVec3(vec3.x, vec3.y, vec3.z);
//}
//
//PxQuat glmQuatToPhysXQuat(const glm::quat& quat)
//{
//	return PxQuat(quat.x, quat.y, quat.z, quat.w);
//}
//
//glm::vec3 PhysXVec3ToglmVec3(const PxVec3& vec3)
//{
//	return glm::vec3(vec3.x, vec3.y, vec3.z);
//}
//
//glm::quat PhysXQuatToglmQuat(const PxQuat& quat)
//{
//	//cout << quat.x << "." << quat.y << "." << quat.z << "." << quat.w << "." << endl;
//
//	return glm::quat(quat.x,quat.y,quat.z,quat.w);
//}


//PxTransform physXTransformToTransform(PxTransform& transform)
//{
//	return PxTransform(glmVec3ToPhysXVec3(actor->transform->position), glmQuatToPhysXQuat(actor->transform->rotationQuat));
//}