#pragma once

#include "Module.hpp"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/transform.hpp>
#include <glm/gtx/quaternion.hpp>
#include <vector>
#include <PxPhysics.h>


using namespace physx;

class Actor;

class Transform : public enable_shared_from_this<Transform>
#ifdef GUINITY_DEBUG
	,public StaticCounter<Transform>
#endif
{
    
public:
    
    
    /** Default Constructor */
	Transform();
    /** Default Destructor */
	~Transform();

    
    
    /** The local position */
    glm::vec3 position;
    /** The local scale */
	glm::vec3 scale;
    /** The local rotation */
	glm::quat rotation;
    
    /** The actor that owns this Transform */
	weak_ptr<Actor> actor;

    
    /** Set the local position 
     @param[in] position The position
     */
	void setPosition(glm::vec3 position);
    /** Set the local rotation
     @param[in] rotation The rotation
     */
	void setRotation(glm::quat rotation);
    /** Set the local scale
     @param[in] scale The scale
     */
	void setScale(glm::vec3 scale);


    /** Get the local position
     @return The local position
     */
	glm::vec3 getPosition();

    /** Get the local scale
     @return The local scale
     */
	glm::vec3 getScale();
    /** Get the local rotation
     @return The local rotation
     */
	glm::quat getRotation();

    
    /** Get the world position
     @return The world position
     */
	glm::vec3 getWorldPosition();
    /** Get the world rotation
     @return The world rotation
     */
    glm::quat getWorldRotation();
    
    /** Get the full model matrix
     @return The model matrix
     */
	glm::mat4 getModelMatrix();
    /** Get the model matrix without the scale
     @return The model matrix without the scale
     */
	glm::mat4 getPosRotMatrix();


    /** actor Setter
     @param[in] actor Reference to the Actor
     */
	void setActor(shared_ptr<Actor> actor);

    /** Updates the Transform based on changes from the PhysX scene
     @param[in] transform The PhysX transform
     */
	void updateTransform(const PxTransform& transform);

    /** Get the Up vector for this Transform
     @return The Up vector */
	glm::vec3 getUp();
    /** Get the Forward vector for this Transform
     @return The Forward vector */
	glm::vec3 getForward();
    /** Get the Right vector for this Transform
     @return The Right vector */
	glm::vec3 getRight();
};

