#include "Player.h"


Player::Player(string name, shared_ptr<MeshRenderer> mesh) : Actor(name, mesh)
{
	moveSpeed = 1.0f;
}


Player::~Player()
{
}

void Player::tick(float deltaSeconds)
{

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

		

		//glm::vec3 rotEuler = glm::eulerAngles(rot);
		//
		//rotEuler.y += 1 * deltaSeconds;
		//
		//rot = glm::quat(rotEuler);

		transform->setRotationQuat(glm::slerp(rot,right,deltaSeconds));
	}
	if (Input::getKey(GLFW_KEY_RIGHT))
	{
		glm::quat rot = transform->getRotationQuat();

		glm::quat right(-transform->getRight());



		//glm::vec3 rotEuler = glm::eulerAngles(rot);
		//
		//rotEuler.y += 1 * deltaSeconds;
		//
		//rot = glm::quat(rotEuler);

		transform->setRotationQuat(glm::slerp(rot, right, deltaSeconds));
	}
}
