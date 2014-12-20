#include "Transform.h"
#include "Math.h"
#include "Actor.h"

int Transform::nCount=0;

Transform::Transform() : position(0.0f), rotationQuat(), scale(1.0f)
{
	nCount++;
}


Transform::~Transform()
{
	nCount--;
	shared_ptr<Actor> ac = actor.lock();
	if (ac!=nullptr)
		cout << "Transform destroyed: "<< ac->name << endl;
	else
		cout << "Transform destroyed (" <<nCount << " remaining)" << endl;

}

void Transform::setActor(shared_ptr<Actor> actor)
{
	this->actor = actor;
}


void Transform::setPosition(glm::vec3 position)
{
	this->position = position;

}
//void Transform::setRotation(glm::vec3 rotation)
//{
//	this->rotation = rotation;
//}
void Transform::setScale(glm::vec3 scale)
{
	this->scale = scale;
}

glm::vec3 Transform::getPosition()
{
	return position;
}
//glm::vec3 Transform::getRotation()
//{
//	return rotation;
//}

glm::quat Transform::getRotationQuat()
{
	return rotationQuat;
}

void Transform::setRotationQuat(glm::quat rotationQuat)
{
	this->rotationQuat = rotationQuat;
}
glm::vec3 Transform::getScale()
{
	return scale;
}

glm::mat4 Transform::getModelMatrix()
{
	if (parent == nullptr)
		return glm::translate(position) * glm::scale(scale) * (glm::mat4)(rotationQuat);// *glm::quat(glm::vec3(0, 180 * Math::Deg2Radian, 0)));

	else return  parent->getModelMatrix() * glm::translate(position) * glm::scale(scale) * (glm::mat4)(rotationQuat);
}

glm::mat4 Transform::getPosRotMatrix()
{
	if (parent == nullptr)
		return glm::translate(position) * (glm::mat4)(rotationQuat);// *glm::quat(glm::vec3(0, 180 * Math::Deg2Radian, 0)));

	else return  parent->getPosRotMatrix() * glm::translate(position)  * (glm::mat4)(rotationQuat);
}

void Transform::setParent(shared_ptr<Transform> parent)
{
	this->parent = parent;
}
void Transform::addChildren(shared_ptr<Transform> children)
{
	this->children.push_back(children);
}

void Transform::updateTransform(const PxTransform& transform)
{
	


	position = PhysXVec3ToglmVec3(transform.p);
	rotationQuat = PhysXQuatToglmQuat(transform.q);

	//cout << "-Physx: " << transform.q << endl;
	//cout << "-glm: " << rotationQuat << endl;

	//glm::vec3 rotEuler = glm::eulerAngles(rotationQuat);
	//float aux = rotEuler.x;
	//rotEuler.x = rotEuler.z;
	//rotEuler.z = aux;
	//
	//rotationQuat = glm::quat(rotEuler);

	//rotationQuat = glm::quat(glm::vec3(0, 0, 90 * Math::Deg2Radian)) * rotationQuat;
	
	//glm::normalize(rotationQuat);
}

glm::vec3 Transform::getUp()
{
	glm::vec4 v = getModelMatrix() * glm::vec4(0, 1, 0, 0);
	return glm::vec3(v.x, v.y, v.z);

}
glm::vec3 Transform::getForward()
{
	glm::vec4 v = getModelMatrix() * glm::vec4(0, 0, 1, 0);
	return glm::vec3(v.x, v.y, v.z);
}
glm::vec3 Transform::getRight()
{
	glm::vec4 v = getModelMatrix() * glm::vec4(1, 0, 0, 0);
	return glm::vec3(v.x, v.y, v.z);
}