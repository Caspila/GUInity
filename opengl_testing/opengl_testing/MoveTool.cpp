#include "MoveTool.hpp"
#include "SphereCollider.hpp"
#include "Factory.hpp"

MoveTool::MoveTool()
{
}


MoveTool::~MoveTool()
{
}

void MoveTool::awake()
{

	shared_ptr<Actor> rightHandle = Factory::CreateEditorActor("MoveRightHandle");
	shared_ptr<SphereCollider> collider = rightHandle->AddComponent<SphereCollider>();
	collider->setQueryOnly(true);
	rightHandle->transform->setPosition(glm::vec3(2, 0, 0));
	shared_ptr<MoveHandle> handleScript = rightHandle->AddComponent<MoveHandle>();
	handleScript->setAxis(MoveAxis::right);

	shared_ptr<Actor> forwardHandle = Factory::CreateEditorActor("MoveForwardHandle");
	collider = forwardHandle->AddComponent<SphereCollider>();
	collider->setQueryOnly(true);
	forwardHandle->transform->setPosition(glm::vec3(0, 0, 2));
	handleScript = forwardHandle->AddComponent<MoveHandle>();
	handleScript->setAxis(MoveAxis::forward);

	shared_ptr<Actor> upHandle = Factory::CreateEditorActor("MoveUpHandle");
	collider = upHandle->AddComponent<SphereCollider>();
	collider->setQueryOnly(true);
	upHandle->transform->setPosition(glm::vec3(0, 2, 0));
	handleScript = upHandle->AddComponent<MoveHandle>();
	handleScript->setAxis(MoveAxis::up);

	getActor()->addChildren(rightHandle);
	getActor()->addChildren(forwardHandle);
	getActor()->addChildren(upHandle);
}