#include "Transform.hpp"
#include "Math.hpp"
#include "Actor.hpp"
#include "Converter.hpp"
#include "RigidBody.hpp"

Transform::Transform() : position(0.0f), rotation(), scale(1.0f)
{
#ifdef GUINITY_DEBUG
	nCount++;
#endif
}


Transform::~Transform()
{

#ifdef GUINITY_DEBUG
	nCount--;
	cout << "Transform destroyed (" << nCount << " remaining)" << endl;
#endif

}

/** actor Setter
 @param[in] actor Reference to the Actor
 */
void Transform::setActor(shared_ptr<Actor> actor)
{
	this->actor = actor;
}

/** Get the local position
 @return The local position
 */
void Transform::setPosition(glm::vec3 position)
{
	this->position = position;

}

/** Set the local scale
 @param[in] scale The scale
 */
void Transform::setScale(glm::vec3 scale)
{
	this->scale = scale;
}

/** Get the local position
 @return The local position
 */
glm::vec3 Transform::getPosition()
{
	return position;
}

/** Get the local rotation
 @return The local rotation
 */
glm::quat Transform::getRotation()
{
	return rotation;
}
/** Set the local rotation
 @param[in] rotation The rotation
 */
void Transform::setRotation(glm::quat rotation)
{
	this->rotation = rotation;
}
/** Get the local scale
 @return The local scale
 */
glm::vec3 Transform::getScale()
{
	return scale;
}

/** Get the full model matrix
 @return The model matrix
 */
glm::mat4 Transform::getModelMatrix()
{
	shared_ptr<Actor> actorLock = actor.lock();
	shared_ptr<Actor> parentLock = actorLock->parent.lock();
    
    if (parentLock == nullptr)
		return glm::translate(position) * (glm::mat4)(rotation) * glm::scale(scale) ;
    
	else return  parentLock->transform->getModelMatrix() * glm::translate(position) *  (glm::mat4)(rotation) * glm::scale(scale);


}

/** Get the model matrix without the scale
 @return The model matrix without the scale
 */
glm::mat4 Transform::getPosRotMatrix()
{
	shared_ptr<Actor> actorLock = actor.lock();
	shared_ptr<Actor> parentLock = actorLock->parent.lock();
	if (parentLock == nullptr)
		return glm::translate(position) * (glm::mat4)(rotation);
    
	else return  parentLock->transform->getPosRotMatrix() * glm::translate(position) * (glm::mat4)(rotation);
}

/** Updates the Transform based on changes from the PhysX scene
 @param[in] transform The PhysX transform
 */
void Transform::updateTransform(const PxTransform& transform)
{
	
    shared_ptr<RigidBody> rigidBody = actor.lock()->GetComponent<RigidBody>();
    if(!rigidBody)
    {
        cerr << "Physics System is trying to update a body that has no RigidBody" << endl;
    }
    
    rigidBody->updateTransform(transform);

}

/** Get the Up vector for this Transform
 @return The Up vector */
glm::vec3 Transform::getUp()
{
	glm::vec4 v = getModelMatrix() * glm::vec4(0, 1, 0, 0);
	return glm::normalize(glm::vec3(v.x, v.y, v.z));

}
/** Get the Forward vector for this Transform
 @return The Forward vector */
glm::vec3 Transform::getForward()
{
	glm::vec4 v = getModelMatrix() * glm::vec4(0, 0, 1, 0);
	return glm::normalize(glm::vec3(v.x, v.y, v.z));
}
/** Get the Right vector for this Transform
 @return The Right vector */
glm::vec3 Transform::getRight()
{
	glm::vec4 v = getModelMatrix() * glm::vec4(1, 0, 0, 0);
	return glm::normalize(glm::vec3(v.x, v.y, v.z));
}

/** Get the world rotation
 @return The world rotation
 */
glm::vec3 Transform::getWorldPosition()
{
	shared_ptr<Actor> actorLock = actor.lock();
	shared_ptr<Actor> parentLock = actorLock->parent.lock();
	if (parentLock == nullptr)
		return position;

	else return glm::vec3(parentLock->transform->getModelMatrix() * glm::vec4(position.x, position.y, position.z, 1));
}

/** Get the world rotation
 @return The world rotation
 */
glm::quat Transform::getWorldRotation()
{
	shared_ptr<Actor> actorLock = actor.lock();
	shared_ptr<Actor> parentLock = actorLock->parent.lock();
	if (parentLock == nullptr)
		return rotation;
    
	else return parentLock->transform->getWorldRotation() * rotation;
}