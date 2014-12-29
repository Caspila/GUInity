#include "Editor.hpp"
#include "Time.hpp"
#include "Physics.hpp"
#include "GraphicsSystem.hpp"
#include "Camera.hpp"
#include "Factory.hpp"
#include "EditorCameraControl.hpp"
#include "Input.hpp"
#include "SphereCollider.hpp"
#include "MoveHandle.hpp"
#include "EditorCollider.hpp"
#include "MoveTool.hpp"
#include "RotateTool.hpp"


//PxScene* Editor::physicsScene;
shared_ptr<Actor> Editor::cameraActor;
shared_ptr<Camera> Editor::cameraComponent;
shared_ptr<Actor> Editor::currentSelectedActor;
shared_ptr<Actor> Editor::moveHandles;
shared_ptr<Actor> Editor::rotateHandles;
shared_ptr<World> Editor::world;
//vector<shared_ptr<Actor>>  Editor::editorActors;

Editor::Editor()
{
}

Editor::~Editor()
{
}

void Editor::init()
{
	world = make_shared<World>();

	world->init();
	world->registerObserverAsEditor();

	cameraActor = Factory::CreateEditorActor("CameraEditor");
	cameraActor->transform->setPosition(glm::vec3(0, 0, 10));
	cameraActor->transform->setRotationQuat(glm::quat(glm::vec3(0, 180 * Math::Deg2Radian, 0)));
	cameraComponent = cameraActor->AddComponent<Camera>();
	cameraActor->AddComponent<EditorCameraControl>();

	//moveHandles = Factory::CreateEditorActor("MoveHandles");
	//moveHandles->AddComponent<MoveTool>();
	rotateHandles = Factory::CreateEditorActor("RotateHandles");
	rotateHandles->AddComponent<RotateTool>();
/*
	shared_ptr<Actor> rightHandle = Factory::CreateEditorActor("MoveRightHandle");
	shared_ptr<SphereCollider> collider = rightHandle->AddComponent<SphereCollider>();
	collider->setQueryOnly(true);
	rightHandle->transform->setPosition(glm::vec3(2, 0, 0));
	shared_ptr<MoveHandle> handleScript = rightHandle->AddComponent<MoveHandle>();
	handleScript->setAxis(MoveHandle::MoveAxis::right);

	shared_ptr<Actor> forwardHandle = Factory::CreateEditorActor("MoveForwardHandle");
	collider = forwardHandle->AddComponent<SphereCollider>();
	collider->setQueryOnly(true);
	forwardHandle->transform->setPosition(glm::vec3(0, 0, 2));
	handleScript = forwardHandle->AddComponent<MoveHandle>();
	handleScript->setAxis(MoveHandle::MoveAxis::forward);

	shared_ptr<Actor> upHandle = Factory::CreateEditorActor("MoveUpHandle");
	collider = upHandle->AddComponent<SphereCollider>();
	collider->setQueryOnly(true);
	upHandle->transform->setPosition(glm::vec3(0, 2, 0));
	handleScript = upHandle->AddComponent<MoveHandle>();
	handleScript->setAxis(MoveHandle::MoveAxis::up);

	moveHandles->addChildren(rightHandle);
	moveHandles->addChildren(forwardHandle);
	moveHandles->addChildren(upHandle);
*/
	//world->addActor(moveHandles);
	//world->addActor(rightHandle);
	//world->addActor(forwardHandle);
	//world->addActor(upHandle);


	//editorActors.push_back(moveHandles);
	//editorActors.push_back(rightHandle);
	//editorActors.push_back(forwardHandle);
	//editorActors.push_back(upHandle);

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

	world->shutdown();

	//for (auto& x : editorActors)
	//	x = nullptr;
//	moveHandles.reset();
}

void Editor::update(float deltaSeconds, shared_ptr<World> gameWorld)
{
	Ray r = cameraComponent->screenPointToRay(Input::mousePos);

	PxRaycastBuffer hitCallback;
	if (Input::getMouseButtonPressed(GLFW_MOUSE_BUTTON_1))
		if (Physics::rayCast(world->physicsScene, r, 300, hitCallback))
		{
			Actor *a = (Actor*)hitCallback.block.actor->userData;

			shared_ptr<Actor> clickedActor = world->getSharedPtrActor(a);

			if (clickedActor)
			{
				shared_ptr<EditorCollider> editorCollider = clickedActor->GetComponent<EditorCollider>();
				if (editorCollider)
					currentSelectedActor = editorCollider->gameActor.lock();
				//else
				//	currentSelectedActor = nullptr;
			}
			
			
		}

	//moveHandles->setActive(currentSelectedActor != nullptr);
	

	world->tick(deltaSeconds);

	Physics::tickScene(world->physicsScene);
	Physics::updateActorsTransform(world->physicsScene);

	cameraComponent->computeModelViewMatrix();

	GraphicsSystem::getInstance().clear();

	//GraphicsSystem::getInstance().render(cameraComponent, world->meshRenderers, world->lights);

	GraphicsSystem::getInstance().render(cameraComponent, gameWorld->meshRenderers, gameWorld->lights);

	GraphicsSystem::getInstance().render(cameraComponent, world->physicsScene->getRenderBuffer(), glm::vec3(1, 1, 1));

	GraphicsSystem::getInstance().swap();

	//cameraActor->tick(deltaSeconds);
}

//void Editor::tickEditorActors(float deltaSeconds)
//{
//	for (auto& x : editorActors)
//		x->tick(deltaSeconds);
//}

//void Editor::onNotify(EventType type, shared_ptr<Component> component, bool isEditor)
//{
//
//}

//shared_ptr<Actor> Editor::getEditorSharedPtrActor(Actor* actor)
//{
//	for (auto& a : editorActors)
//	{
//		if (a.get() == actor)
//			return a;
//	}
//	cerr << "There's a pointer to an actor that does not live in the world!" << endl;
//
//	return nullptr;
//}