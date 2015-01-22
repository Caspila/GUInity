#include "ScaleTool.hpp"
#include "SphereCollider.hpp"
#include "CapsuleCollider.hpp"
#include "Factory.hpp"
#include "Editor.hpp"

ScaleTool::ScaleTool()
{
}


ScaleTool::~ScaleTool()
{
}

void ScaleTool::awake()
{
    
    //	shared_ptr<Actor> rightHandle = Factory::CreateEditorActor("MoveRightHandle");
    //	shared_ptr<SphereCollider> collider = rightHandle->AddComponent<SphereCollider>();
    ////    shared_ptr<CapsuleCollider> collider = rightHandle->AddComponent<CapsuleCollider>();
    ////    collider->setOrientation(RotateAxis::x);
    ////    collider->setHeight(2);
    ////    collider->setRadius(0.1f);
    //	collider->setQueryOnly(true);
    //	rightHandle->transform->setPosition(glm::vec3(2, 0, 0));
    //	shared_ptr<MoveHandle> handleScript = rightHandle->AddComponent<MoveHandle>();
    //	handleScript->setAxis(MoveAxis::right);
    //
    //	shared_ptr<Actor> forwardHandle = Factory::CreateEditorActor("MoveForwardHandle");
    //collider = forwardHandle->AddComponent<SphereCollider>();
    ////	collider = forwardHandle->AddComponent<CapsuleCollider>();//forwardHandle->AddComponent<SphereCollider>();
    ////    collider->setOrientation(RotateAxis::z);
    ////    collider->setHeight(2);
    ////    collider->setRadius(0.1f);
    //	collider->setQueryOnly(true);
    //	forwardHandle->transform->setPosition(glm::vec3(0, 0, 2));
    //	handleScript = forwardHandle->AddComponent<MoveHandle>();
    //	handleScript->setAxis(MoveAxis::forward);
    //
    //	shared_ptr<Actor> upHandle = Factory::CreateEditorActor("MoveUpHandle");
    //collider = upHandle->AddComponent<SphereCollider>();
    ////	collider = upHandle->AddComponent<CapsuleCollider>();//upHandle->AddComponent<SphereCollider>();
    ////    collider->setOrientation(RotateAxis::y);
    ////    collider->setHeight(2);
    ////    collider->setRadius(0.1f);
    //	collider->setQueryOnly(true);
    //	upHandle->transform->setPosition(glm::vec3(0, 2, 0));
    //	handleScript = upHandle->AddComponent<MoveHandle>();
    //	handleScript->setAxis(MoveAxis::up);
    
	shared_ptr<Actor> rightHandle = Factory::CreateEditorActor("ScaleRightHandle");
	
    shared_ptr<CapsuleCollider> collider = rightHandle->AddComponent<CapsuleCollider>();
    collider->setOrientation(RotateAxis::x);
    collider->setHeight(2);
    collider->setRadius(0.1f);
	collider->setQueryOnly(true);
    //	rightHandle->transform->setPosition(glm::vec3(2, 0, 0));
	shared_ptr<ScaleHandle> handleScript = rightHandle->AddComponent<ScaleHandle>();
	handleScript->setAxis(TransformAxis::x);
    //rightHandle->AddComponent<RotateOverTime>();
    
	shared_ptr<Actor> forwardHandle = Factory::CreateEditorActor("ScaleForwardHandle");
    collider = forwardHandle->AddComponent<CapsuleCollider>();
    collider->setOrientation(RotateAxis::z);
    collider->setHeight(2);
    collider->setRadius(0.1f);
	collider->setQueryOnly(true);
    //	forwardHandle->transform->setPosition(glm::vec3(0, 0, 2));
	handleScript = forwardHandle->AddComponent<ScaleHandle>();
	handleScript->setAxis(TransformAxis::z);
    
	shared_ptr<Actor> upHandle = Factory::CreateEditorActor("ScaleUpHandle");
    collider = upHandle->AddComponent<CapsuleCollider>();
    collider->setOrientation(RotateAxis::y);
    collider->setHeight(2);
    collider->setRadius(0.1f);
	collider->setQueryOnly(true);
    //	upHandle->transform->setPosition(glm::vec3(0, 2, 0));
	handleScript = upHandle->AddComponent<ScaleHandle>();
	handleScript->setAxis(TransformAxis::y);
    
	getActor()->addChildren(rightHandle);
	getActor()->addChildren(forwardHandle);
	getActor()->addChildren(upHandle);
}

void ScaleTool::tick(float deltaSeconds)
{
    shared_ptr<Actor> currentActor = Editor::currentSelectedActor;
	if (!currentActor)
		return;
    
    //    cout << "alsddsla" << endl;
    
	shared_ptr<Actor> actor = getActor();
	if (actor)
	{
        //        cout << "Align" << endl;
		actor->transform->position = currentActor->transform->position;
		actor->transform->rotationQuat = currentActor->transform->rotationQuat;
	}
    
    //    cout << "Rotating" << endl;
    //       getActor()->transform->rotationQuat =  glm::angleAxis(deltaSeconds, glm::vec3(0, 1, 0))* getActor()->transform->rotationQuat;
    
    
}