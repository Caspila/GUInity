#include "RotateTool.hpp"
#include "SphereCollider.hpp"
#include "Factory.hpp"
#include "RotateHandle.hpp"
#include "CapsuleCollider.hpp"


RotateTool::RotateTool()
{
}


RotateTool::~RotateTool()
{
}

void RotateTool::awake()
{

	shared_ptr<Actor> rightHandle = Factory::CreateEditorActor("RotateZAxisHandle");
	shared_ptr<CapsuleCollider> collider = rightHandle->AddComponent<CapsuleCollider>();
	collider->setQueryOnly(true);
	//collider->setOrientation(RotateAxis::x);
	collider->setHeight(0.01f);
	rightHandle->transform->setPosition(glm::vec3(0, 0, 0));
	shared_ptr<RotateHandle> handleScript = rightHandle->AddComponent<RotateHandle>();
	handleScript->setAxis(RotateAxis::z);

	//shared_ptr<Actor> forwardHandle = Factory::CreateEditorActor("RotateXAxisHandle");
	//collider = forwardHandle->AddComponent<CapsuleCollider>();
	//collider->setQueryOnly(true);
	//forwardHandle->transform->setPosition(glm::vec3(0, 0, 2));
	//handleScript = forwardHandle->AddComponent<RotateHandle>();
	//handleScript->setAxis(RotateAxis::x);
	//
	//shared_ptr<Actor> upHandle = Factory::CreateEditorActor("RotateYAxisHandle");
	//collider = upHandle->AddComponent<CapsuleCollider>();
	//collider->setQueryOnly(true);
	//upHandle->transform->setPosition(glm::vec3(0, 2, 0));
	//handleScript = upHandle->AddComponent<RotateHandle>();
	//handleScript->setAxis(RotateAxis::y);
	//
	//getActor()->addChildren(rightHandle);
	//getActor()->addChildren(forwardHandle);
	//getActor()->addChildren(upHandle);
}