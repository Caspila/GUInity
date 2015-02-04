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
#include "Mesh.hpp"
#include "UIButton.hpp"
#include "print.hpp"
#include "Math.hpp"
#include "ScaleTool.hpp"

//PxScene* Editor::physicsScene;
shared_ptr<Actor> Editor::cameraActor;
shared_ptr<Camera> Editor::cameraComponent;
shared_ptr<Actor> Editor::currentSelectedActor;
shared_ptr<Actor> Editor::moveHandles;
shared_ptr<Actor> Editor::rotateHandles;
shared_ptr<Actor> Editor::scaleHandles;
shared_ptr<World> Editor::world;
shared_ptr<UIWidget> Editor::uiWidgetTest;
TransformMode Editor::transformMode;
//vector<shared_ptr<Actor>>  Editor::editorActors;

Editor::Editor()
{
}

Editor::~Editor()
{
}

void callBack()
{
    cout << "Button1 pressed!"<< endl;
}

void callBack2()
{
    cout << "Button2 pressed!"<< endl;
}

void Editor::init()
{
    transformMode = TransformMode::none;
    
	world = make_shared<World>();

	world->init();
	world->registerObserverAsEditor();

	cameraActor = Factory::CreateEditorActor("CameraEditor");
	cameraActor->transform->setPosition(glm::vec3(0, 0, 10));
	cameraActor->transform->setRotationQuat(glm::quat(glm::vec3(0, 180 * Deg2Radian, 0)));
	cameraComponent = cameraActor->AddComponent<Camera>();
	cameraActor->AddComponent<EditorCameraControl>();

	moveHandles = Factory::CreateEditorActor("MoveHandles");
	moveHandles->AddComponent<MoveTool>();
    
    moveHandles->setActive(false);
    
    rotateHandles = Factory::CreateEditorActor("RotateHandles");
	rotateHandles->AddComponent<RotateTool>();
    
    rotateHandles->setActive(false);
    
    scaleHandles = Factory::CreateEditorActor("ScaleHandles");
	scaleHandles->AddComponent<ScaleTool>();
    
    scaleHandles->setActive(false);
    
    //shared_ptr<UIWidget> baseContainer = make_shared<UIWidget>();
    //baseContainer->mesh = dynamic_pointer_cast<Mesh>(AssetDatabase::idToAsset[0]);
    ////baseContainer->color = glm::vec4(0.5,0,0,1);
    //baseContainer->setBounds(0, 0, 0, 0);
    //UIWidget::depthToWidgetVector[0].push_back(baseContainer);
    //
    //
    //shared_ptr<UIButton> button = make_shared<UIButton>();
    //button->clickFunction = callBack;
    //uiWidgetTest = dynamic_pointer_cast<UIWidget>(button);//make_shared<UIButton>();
    //uiWidgetTest->mesh = dynamic_pointer_cast<Mesh>(AssetDatabase::idToAsset[0]);
    //uiWidgetTest->setBounds(0, 0, 100, 100);
    //uiWidgetTest->color = glm::vec4(0.5,0,0,0.5);
    //baseContainer->addWidget(button);

    //
    //button = make_shared<UIButton>();
    //button->clickFunction = callBack2;
    //uiWidgetTest = dynamic_pointer_cast<UIWidget>(button);//make_shared<UIButton>();
    //uiWidgetTest->mesh = dynamic_pointer_cast<Mesh>(AssetDatabase::idToAsset[0]);
    //uiWidgetTest->setBounds(0, 0, 100, 100);
    ////uiWidgetTest->color = glm::vec4(0.5,0,0,1);
    //baseContainer->addWidget(button);
    //
    //uiWidgetTest = baseContainer;
    

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

	scaleHandles = nullptr;

	rotateHandles = nullptr;
    
    

	world->shutdown();

	//for (auto& x : editorActors)
	//	x = nullptr;
//	moveHandles.reset();
}
//
//bool isInside(glm::vec2 mousePos, glm::vec4 bounds)
//{
//    if(mousePos.x > bounds.x && mousePos.x < bounds.z && mousePos.y > bounds.y && mousePos.y < bounds.w)
//        return true;
//    return false;
//}
//
//// Gets the most inner widget based on a pos, usually mouse position
//shared_ptr<UIWidget> findMostInner(glm::vec2 pos, shared_ptr<UIWidget> currentWidget)
//{
//    if(isInside(pos, currentWidget->bounds))
//    {
//        if(currentWidget->children.size()==0)
//            return currentWidget;
//        else
//        {
//        for(auto&x : currentWidget->children)
//        {
//            shared_ptr<UIWidget> childrenLock = x.lock();
//            if (childrenLock)
//            {
//                shared_ptr<UIWidget> mostInner = findMostInner(pos, childrenLock);
//                //if(!mostInner)
//                //    return currentWidget;
//                //else
//                if(mostInner)
//                    return findMostInner(pos, mostInner);
//            }
//            
//            else
//            {
//                cerr << "Could not lock UIWidget children weak_ptr. It was probably deleted before but not removed from the list." << endl;
//                
//                return nullptr;
//            }
//
//        }
//            return currentWidget;
//        }
//    }
//    return nullptr;
//}
//
//shared_ptr<UIWidget> lastWidget;

void Editor::update(float deltaSeconds, shared_ptr<World> gameWorld)
{
    //rotateHandles->setActive(false);
    
    //shared_ptr<UIButton> button = dynamic_pointer_cast<UIButton>(uiWidgetTest);
    
//    shared_ptr<UIWidget> mostInner = findMostInner(Input::mousePos,uiWidgetTest);
////    cout << Input::mousePos << endl;
////    if(isInside(Input::mousePos,mostInner->bounds))
//    if(mostInner)
//    {
//        if(lastWidget!=mostInner)
//        {
//            if(lastWidget!=nullptr)
//                lastWidget->hoverOffFunction();
//            
//            mostInner->hoverOnFunction();
//            
//            lastWidget = mostInner;
//        }
//        //shared_ptr<UIButton> button = dynamic_pointer_cast<UIButton>(mostInner);
//        //if(button)
//            //button->callBackFunction();
//        //    button->hoverOnFunction();
//    }
    
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
					currentSelectedActor = editorCollider->getGameActor();

			}
			
			
		}
        else
            currentSelectedActor = nullptr;
    
    
    if(Input::getKeyPressed(GLFW_KEY_Q))
    {
        transformMode = TransformMode::move;
    } else
        if(Input::getKeyPressed(GLFW_KEY_W))
        {
            transformMode = TransformMode::rotate;
        }
        else
            if(Input::getKeyPressed(GLFW_KEY_E))
            {
                transformMode = TransformMode::scale;
            }


    
    if(currentSelectedActor!=nullptr)
    {
        switch (transformMode) {
            case TransformMode::none:
                rotateHandles->setActive(false);
                moveHandles->setActive(false);
                scaleHandles->setActive(false);
                break;
            case TransformMode::move:
                rotateHandles->setActive(false);
                moveHandles->setActive(true);
                scaleHandles->setActive(false);
                break;
            case TransformMode::rotate:
                rotateHandles->setActive(true);
                moveHandles->setActive(false);
                scaleHandles->setActive(false);
                break;
            case TransformMode::scale:
                rotateHandles->setActive(false);
                moveHandles->setActive(false);
                scaleHandles->setActive(true);
                break;
                
            default:
                break;
        }
    }
    else
    {
        moveHandles->setActive(false);
        rotateHandles->setActive(false);
        scaleHandles->setActive(false);
    }

	//moveHandles->setActive(currentSelectedActor != nullptr);
	

	world->tick(deltaSeconds);

	Physics::tickScene(world->physicsScene);
	Physics::updateActorsTransform(world->physicsScene);

	cameraComponent->computeModelViewMatrix();

	GraphicsSystem::getInstance()->clear();

	//GraphicsSystem::getInstance().render(cameraComponent, world->meshRenderers, world->lights);

	GraphicsSystem::getInstance()->render(cameraComponent, gameWorld->meshRenderers, gameWorld->lights);

	GraphicsSystem::getInstance()->render(cameraComponent, world->physicsScene->getRenderBuffer(), glm::vec4(1, 1, 1,1));
    
    //GraphicsSystem::getInstance()->renderGUI(uiWidgetTest,1);
//    GraphicsSystem::getInstance()->renderGUI(UIWidget::depthToWidgetVector[1]);

	GraphicsSystem::getInstance()->swap();

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