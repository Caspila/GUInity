#include "PlayerScript.hpp"

#include "Actor.hpp"
#include "World.hpp"


//PlayerScript::PlayerScript()
//{
//
//}


PlayerScript::~PlayerScript()
{
	cout << "PlayerScript Destroyed";
}

void PlayerScript::awake()
{
	moveSpeed = 1;

	//sphereReference = World::findActor("Sphere");
}


void PlayerScript::setSphereRef(weak_ptr<Actor> actor)
{
	sphereReference = actor;
}

void PlayerScript::tick(float deltaSeconds)
{
	//shared_ptr<Transform> transform = getActor()->transform;

	shared_ptr<Actor> lock = sphereReference.lock();
	
	if (!lock)
		return;
	
	shared_ptr<Transform> transform = lock->transform;

	//shared_ptr<Transform> transform = sphereReference->transform;

	if (Input::getKey(GLFW_KEY_UP))
	{
		glm::vec3 position = transform->getPosition();
	
		position += transform->getForward() * deltaSeconds * moveSpeed;
	
		transform->setPosition(position);
	}
	if (Input::getKey(GLFW_KEY_DOWN))
	{
		glm::vec3 position = transform->getPosition();
	
		position -= transform->getForward() * deltaSeconds * moveSpeed;
	
		transform->setPosition(position);
	}
	
	
	if (Input::getKey(GLFW_KEY_LEFT))
	{
		glm::quat rot = transform->getRotationQuat();
	
		glm::quat right(glm::vec3(1, 1, 1), glm::vec3(1, 1, 1));// (transform->getRight());
	
	
		transform->setRotationQuat(glm::slerp(rot, right, deltaSeconds));
	}
	if (Input::getKey(GLFW_KEY_RIGHT))
	{
		glm::quat rot = transform->getRotationQuat();
	
		glm::quat right(-transform->getRight());
	
	
		transform->setRotationQuat(glm::slerp(rot, right, deltaSeconds));
	}

}