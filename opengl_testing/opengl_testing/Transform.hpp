#pragma once

#include "Module.hpp"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/transform.hpp>
#include <glm/gtx/quaternion.hpp>
#include <vector>
#include "Math.hpp"
#include <PxPhysics.h>


using namespace physx;

class Actor;

class Transform : public enable_shared_from_this<Transform>
#ifdef GUINITY_DEBUG
	,public StaticCounter<Transform>
#endif
{

public:
	Transform();
	~Transform();

	void setPosition(glm::vec3 position);
	void setRotationQuat(glm::quat rotationQuat);
	void setScale(glm::vec3 scale);

	glm::vec3 getGlobalPosition();
	glm::vec3 getPosition();
	glm::vec3 getScale();
	glm::quat getRotationQuat();

	glm::mat4 getModelMatrix();
	glm::mat4 getPosRotMatrix();

	glm::vec3 position;
	glm::vec3 scale;
	glm::quat rotationQuat;


	weak_ptr<Actor> actor;


	void setActor(shared_ptr<Actor> actor);
	//void setRigidBody(PxRigidBody* rigidBody);

	void updateTransform(const PxTransform& transform);

	glm::vec3 getUp();
	glm::vec3 getForward();
	glm::vec3 getRight();
};

