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

PxVec3 glmVec3ToPhysXVec3(const glm::vec3& vec3)
{
	return PxVec3(vec3.x, vec3.y, vec3.z);
}

PxQuat glmQuatToPhysXQuat(const glm::quat& quat)
{

	
	//glm::vec3 rotEuler = glm::eulerAngles(quat);
	//float aux = rotEuler.x;
	//rotEuler.x = rotEuler.z;
	//rotEuler.z = aux;
	//
	//quat = glm::quat(rotEuler);

	return PxQuat(quat.x, quat.y, quat.z, quat.w);
}

glm::vec3 PhysXVec3ToglmVec3(const PxVec3& vec3)
{
	return glm::vec3(vec3.x, vec3.y, vec3.z);
}

glm::quat PhysXQuatToglmQuat(const PxQuat& quat)
{
	
	//glm::quat rotationQuat(quat.x, quat.y, quat.z, quat.w);
	//
	//glm::vec3 rotEuler = glm::eulerAngles(rotationQuat);
	//float aux = rotEuler.x;
	//rotEuler.x = rotEuler.z;
	//rotEuler.z = aux;
	//
	//rotationQuat = glm::quat(rotEuler);

	//cout << "angle1: "<< quat.getAngle() << endl;
	//
	//glm::quat result(quat.w, quat.x, quat.y, quat.z);
	//
	//cout << "angle2: " << glm::angle(result)<< endl;
	//glm::quat result(quat.w, quat.z, quat.x, quat.y);

	return glm::quat(quat.w, quat.x, quat.y, quat.z);
}

PxMat44 glmMat4ToPhysXMat4(const glm::mat4&  mat)
{
	PxMat44 result;
	result[0][0] = mat[0][0];
	result[0][1] = mat[0][1];
	result[0][2] = mat[0][2];
	result[0][3] = mat[0][3];

	result[1][0] = mat[1][0];
	result[1][1] = mat[1][1];
	result[1][2] = mat[1][2];
	result[1][3] = mat[1][3];

	result[2][0] = mat[2][0];
	result[2][1] = mat[2][1];
	result[2][2] = mat[2][2];
	result[2][3] = mat[2][3];

	result[3][0] = mat[3][0];
	result[3][1] = mat[3][1];
	result[3][2] = mat[3][2];
	result[3][3] = mat[3][3];

	return result;
}

PxTransform transformToPhysXTransform(const shared_ptr<Transform>& transform)
{
	return PxTransform(glmVec3ToPhysXVec3(transform->position), glmQuatToPhysXQuat(transform->rotationQuat));
}

//PxTransform physXTransformToTransform(PxTransform& transform)
//{
//	return PxTransform(glmVec3ToPhysXVec3(actor->transform->position), glmQuatToPhysXQuat(actor->transform->rotationQuat));
//}