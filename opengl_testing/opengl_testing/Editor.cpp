#include "Editor.hpp"
#include "Time.hpp"
#include "Physics.hpp"
#include "GraphicsSystem.hpp"
#include "Camera.hpp"
#include "Factory.hpp"
#include "EditorCameraControl.h"
#include "Input.hpp"
#include "SphereCollider.hpp"
#include "MoveHandle.h"


PxScene* Editor::physicsScene;
shared_ptr<Actor> Editor::cameraActor;
shared_ptr<Camera> Editor::cameraComponent;
shared_ptr<Actor> Editor::currentSelectedActor;
shared_ptr<Actor> Editor::moveHandles;
vector<shared_ptr<Actor>>  Editor::editorActors;

Editor::Editor()
{
}

Editor::~Editor()
{
}

void Editor::init()
{
	cameraActor = Factory::CreateActor("CameraEditor");
	cameraActor->transform->setPosition(glm::vec3(0, 0, 10));
	cameraActor->transform->setRotationQuat(glm::quat(glm::vec3(0, 180 * Math::Deg2Radian, 0)));
	cameraComponent = cameraActor->AddComponent<Camera>();
	cameraActor->AddComponent<EditorCameraControl>();

	moveHandles = Factory::CreateActor("MoveHandles");

	shared_ptr<Actor> rightHandle = Factory::CreateActor("MoveRightHandle");
	shared_ptr<SphereCollider> collider = rightHandle->AddComponent<SphereCollider>();
	collider->setQueryOnly(true);
	rightHandle->transform->setPosition(glm::vec3(2, 0, 0));
	shared_ptr<MoveHandle> handleScript = rightHandle->AddComponent<MoveHandle>();
	handleScript->setAxis(glm::vec3(1, 0, 0));

	shared_ptr<Actor> forwardHandle = Factory::CreateActor("MoveForwardHandle");
	collider = forwardHandle->AddComponent<SphereCollider>();
	collider->setQueryOnly(true);
	forwardHandle->transform->setPosition(glm::vec3(0, 0, 2));
	handleScript = forwardHandle->AddComponent<MoveHandle>();
	handleScript->setAxis(glm::vec3(0, 0, 1));

	shared_ptr<Actor> upHandle = Factory::CreateActor("MoveUpHandle");
	collider = upHandle->AddComponent<SphereCollider>();
	collider->setQueryOnly(true);
	upHandle->transform->setPosition(glm::vec3(0, 2, 0));
	handleScript = upHandle->AddComponent<MoveHandle>();
	handleScript->setAxis(glm::vec3(0, 1, 0));

	moveHandles->addChildren(rightHandle);
	moveHandles->addChildren(forwardHandle);
	moveHandles->addChildren(upHandle);

	editorActors.push_back(moveHandles);
	editorActors.push_back(rightHandle);
	editorActors.push_back(forwardHandle);
	editorActors.push_back(upHandle);

	//World::addActor(moveHandles);
	//World::addActor(rightHandle);
	//World::addActor(forwardHandle);
	//World::addActor(upHandle);
}

void Editor::shutdown()
{
	cameraActor = nullptr;

	cameraComponent = nullptr;
	
	currentSelectedActor = nullptr;
	
	moveHandles = nullptr;

	for (auto& x : editorActors)
		x = nullptr;
//	moveHandles.reset();
}

void Editor::update(shared_ptr<World> world, float deltaSeconds)
{
	Ray r = cameraComponent->screenPointToRay(Input::mousePos);

	PxRaycastBuffer hitCallback;
	if (Input::getMouseButton(GLFW_MOUSE_BUTTON_1))
		if (Physics::rayCast(r, 300, hitCallback))
		{
			Actor *a = (Actor*)hitCallback.block.actor->userData;

			shared_ptr<Actor> clickedActor = world->getSharedPtrActor(a);

			if (clickedActor)
				currentSelectedActor = clickedActor;
		
			//if (!currentSelectedActor)
			//	currentSelectedActor = getEditorSharedPtrActor(a);
			//cout << "Mouse click: " << a->name << endl;
		}
		//else
		//	currentSelectedActor = nullptr;

	//	if (Input::getKeyPressed(GLFW_KEY_RIGHT))
	//		cout << "Right pressed" << endl;
	if (currentSelectedActor)
		cout << currentSelectedActor->name << endl;
		moveHandles->setActive(currentSelectedActor != nullptr);
	
	tickEditorActors(deltaSeconds);

	cameraComponent->computeModelViewMatrix();

	GraphicsSystem::getInstance().clear();

	GraphicsSystem::getInstance().render(cameraComponent, world->meshRenderers, world->lights);

	GraphicsSystem::getInstance().render(cameraComponent, Physics::scene->getRenderBuffer(), glm::vec3(1, 1, 1));

	GraphicsSystem::getInstance().swap();

	cameraActor->tick(deltaSeconds);
}

void Editor::tickEditorActors(float deltaSeconds)
{
	for (auto& x : editorActors)
		x->tick(deltaSeconds);
}

void Editor::onNotify(EventType type, shared_ptr<Component> component)
{

}

shared_ptr<Actor> Editor::getEditorSharedPtrActor(Actor* actor)
{
	for (auto& a : editorActors)
	{
		if (a.get() == actor)
			return a;
	}
	cerr << "There's a pointer to an actor that does not live in the world!" << endl;

	return nullptr;
}