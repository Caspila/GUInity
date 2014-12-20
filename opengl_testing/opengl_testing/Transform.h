#pragma once

#include "Module.h"
#include <glm\glm.hpp>
#include <glm\gtc\matrix_transform.hpp>
#include <glm\gtx\transform.hpp>
#include <glm\gtx\quaternion.hpp>
#include <vector>
#include "Math.h"
#include <PxPhysics.h>
#include "print.h"

using namespace physx;

class Actor;

class Transform
#ifdef GUINITY_DEBUG
	:public StaticCounter<Transform>
#endif
{

public:
	Transform();
	~Transform();

	void setPosition(glm::vec3 position);
	void setRotationQuat(glm::quat rotationQuat);
	void setScale(glm::vec3 scale);

	glm::vec3 getPosition();
	glm::vec3 getScale();
	glm::quat Transform::getRotationQuat();

	glm::mat4 getModelMatrix();
	glm::mat4 getPosRotMatrix();

	glm::vec3 position;
	glm::vec3 scale;
	glm::quat rotationQuat;

	shared_ptr<Transform> parent;
	vector<shared_ptr<Transform>> children;

	weak_ptr<Actor> actor;

	// HOW TO REMOVE THIS POINTER?!
	// Should never release cause this is taken care by PhysX
	PxRigidBody* rigidBody;

	void setParent(shared_ptr<Transform> parent);
	void addChildren(shared_ptr<Transform> children);

	void setActor(shared_ptr<Actor> actor);
	void setRigidBody(PxRigidBody* rigidBody);

	void updateTransform(const PxTransform& transform);

	glm::vec3 getUp();
	glm::vec3 getForward();
	glm::vec3 getRight();
};

