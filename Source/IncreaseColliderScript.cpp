#include "IncreaseColliderScript.hpp"
#include "Actor.hpp"
#include "Transform.hpp"
#include "Input.hpp"
#include "SphereCollider.hpp"


IncreaseColliderScript::IncreaseColliderScript()
{
}


IncreaseColliderScript::~IncreaseColliderScript()
{
}


void IncreaseColliderScript::awake()
{

}



void IncreaseColliderScript::tick(float deltaSeconds)
{
	shared_ptr<Transform> transform = getActor()->transform;

	//	shared_ptr<Actor> lock = sphereReference.lock();
	//	
	//	if (!lock)
	//		return;

	//	shared_ptr<Transform> transform = lock->transform;

	//shared_ptr<Transform> transform = sphereReference->transform;

	if (Input::getKey(GLFW_KEY_UP))
	{
		shared_ptr<SphereCollider> sphereCollider = getActor()->GetComponent<SphereCollider>();

		if (sphereCollider)
			sphereCollider->setRadius(sphereCollider->getRadius() + 1 * deltaSeconds);
		

	}
	if (Input::getKey(GLFW_KEY_DOWN))
	{
		shared_ptr<SphereCollider> sphereCollider = getActor()->GetComponent<SphereCollider>();

		if (sphereCollider)
		{
			sphereCollider->setRadius(sphereCollider->getRadius() - 1 * deltaSeconds);
		}
	}



}