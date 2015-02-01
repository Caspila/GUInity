#include "Transform.hpp"
#include "Math.hpp"
#include "Actor.hpp"
#include "Converter.hpp"
#include "RigidBody.hpp"

Transform::Transform() : position(0.0f), rotationQuat(), scale(1.0f)
{
#ifdef GUINITY_DEBUG
	nCount++;
#endif

//	this->actor = actor;
}


Transform::~Transform()
{

#ifdef GUINITY_DEBUG
	nCount--;
	cout << "Transform destroyed (" << nCount << " remaining)" << endl;
#endif

}

void Transform::setActor(shared_ptr<Actor> actor)
{
	this->actor = actor;
}

//void Transform::setRigidBody(PxRigidBody* rigidBody)
//{
//	this->rigidBody = rigidBody;
//}

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
	shared_ptr<Actor> actorLock = actor.lock();
	shared_ptr<Actor> parentLock = actorLock->parent.lock();
    
    if (parentLock == nullptr)
		return glm::translate(position) * (glm::mat4)(rotationQuat) * glm::scale(scale) ;
    
	else return  parentLock->transform->getModelMatrix() * glm::translate(position) *  (glm::mat4)(rotationQuat) * glm::scale(scale);

    
    
//	if (parentLock == nullptr)
//		return glm::translate(position) * glm::scale(scale) * (glm::mat4)(rotationQuat);
//
//	else return  parentLock->transform->getModelMatrix() * glm::translate(position) * glm::scale(scale) * (glm::mat4)(rotationQuat);
}

glm::mat4 Transform::getPosRotMatrix()
{
	shared_ptr<Actor> actorLock = actor.lock();
	shared_ptr<Actor> parentLock = actorLock->parent.lock();
	if (parentLock == nullptr)
		return glm::translate(position) * (glm::mat4)(rotationQuat);// *glm::quat(glm::vec3(0, 180 * Math::Deg2Radian, 0)));

	//else return  actorLock->transform->getPosRotMatrix() * glm::translate(position) * glm::scale(scale) * (glm::mat4)(rotationQuat);
	else return  parentLock->transform->getPosRotMatrix() * glm::translate(position) * (glm::mat4)(rotationQuat);
}

void Transform::updateTransform(const PxTransform& transform)
{
	
    shared_ptr<RigidBody> rigidBody = actor.lock()->GetComponent<RigidBody>();
    if(!rigidBody)
    {
        cerr << "Physics System is trying to update a body that has no RigidBody" << endl;
    }
    
    rigidBody->updateTransform(transform);
//
////
//    glm::vec3 newPos = PhysXVec3ToglmVec3(transform.p);
//    if(rigidBody->lockMoveX)
//        newPos.x = position.x;
//    if(rigidBody->lockMoveY)
//        newPos.y = position.y;
//    if(rigidBody->lockMoveZ)
//        newPos.z = position.z;
////
////    
////    //TODO : find a better way to lock rotation on axes, dealing with quaternion directly
//    glm::vec3 oldRotEuler = glm::eulerAngles(rotationQuat);
//    glm::vec3 rotEuler = glm::eulerAngles(PhysXQuatToglmQuat(transform.q));
//    if(rigidBody->lockRotateX)
//        rotEuler.x = oldRotEuler.x;
//    if(rigidBody->lockRotateY)
//        rotEuler.y = oldRotEuler.y;
//    if(rigidBody->lockRotateZ)
//        rotEuler.z = oldRotEuler.z;
//    
////
//    
//	position = newPos;//PhysXVec3ToglmVec3(transform.p);
//	rotationQuat = glm::quat(rotEuler);//PhysXQuatToglmQuat(transform.q);
//
//        rigidBody->physxRigidBody->setGlobalPose(PxTransform(glmVec3ToPhysXVec3(position),glmQuatToPhysXQuat(rotationQuat)));
    
//    position = PhysXVec3ToglmVec3(transform.p);
//	rotationQuat = PhysXQuatToglmQuat(transform.q);
//    


    
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
	return glm::normalize(glm::vec3(v.x, v.y, v.z));

}
glm::vec3 Transform::getForward()
{
	glm::vec4 v = getModelMatrix() * glm::vec4(0, 0, 1, 0);
	return glm::normalize(glm::vec3(v.x, v.y, v.z));
}
glm::vec3 Transform::getRight()
{
	glm::vec4 v = getModelMatrix() * glm::vec4(1, 0, 0, 0);
	return glm::normalize(glm::vec3(v.x, v.y, v.z));
}

glm::vec3 Transform::getGlobalPosition()
{
	shared_ptr<Actor> actorLock = actor.lock();
	shared_ptr<Actor> parentLock = actorLock->parent.lock();
	if (parentLock == nullptr)
		return position;

	else return glm::vec3(parentLock->transform->getModelMatrix() * glm::vec4(position.x, position.y, position.z, 1));
}