#include "MoveTool.hpp"
#include "SphereCollider.hpp"
#include "CapsuleCollider.hpp"
#include "Factory.hpp"
#include "Editor.hpp"
#include "Math.hpp"

MoveTool::MoveTool()
{
}


MoveTool::~MoveTool()
{
}

void MoveTool::awake()
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
    
    shared_ptr<Mesh> arrowMesh = AssetDatabase::getAsset<Mesh>("arrow.fbx");
    
    shared_ptr<Shader> unlitShader = AssetDatabase::getAsset<Shader>("LightShader");
    
    shared_ptr<Material> redMaterial = AssetDatabase::createMaterial("RedDefaultMaterial", unlitShader);
    redMaterial->setParamVec4("_difuseColor",glm::vec4(1,0,0,1));
    shared_ptr<Material> blueMaterial = AssetDatabase::createMaterial("BlueDefaultMaterial", unlitShader);
    blueMaterial->setParamVec4("_difuseColor",glm::vec4(0,0,1,1));
    shared_ptr<Material> greenMaterial = AssetDatabase::createMaterial("GreenDefaultMaterial", unlitShader);
    greenMaterial->setParamVec4("_difuseColor",glm::vec4(0,1,0,1));
	shared_ptr<Actor> rightHandle = Factory::CreateEditorActor("MoveRightHandle");
	
    shared_ptr<CapsuleCollider> collider = rightHandle->AddComponent<CapsuleCollider>();
    rightHandle->transform->setPosition(glm::vec3(-0.5,0,0));
    rightHandle->transform->setRotation(glm::quat(glm::vec3(0,0,90 * Deg2Radian)));
    collider->setOrientation(RotateAxis::y);
    collider->setHeight(0.5);
    collider->setRadius(0.1f);
	collider->setQueryOnly(true);
    shared_ptr<MeshFilter> meshFilter = rightHandle->AddComponent<MeshFilter>();
    shared_ptr<MeshRenderer> meshRenderer = rightHandle->AddComponent<MeshRenderer>();
    meshRenderer->setMaterial(redMaterial);
    meshFilter->setMesh(arrowMesh);
    //	rightHandle->transform->setPosition(glm::vec3(2, 0, 0));
	shared_ptr<MoveHandle> handleScript = rightHandle->AddComponent<MoveHandle>();
	handleScript->setAxis(MoveAxis::right);
    //rightHandle->AddComponent<RotateOverTime>();
    
	shared_ptr<Actor> forwardHandle = Factory::CreateEditorActor("MoveForwardHandle");
    collider = forwardHandle->AddComponent<CapsuleCollider>();
    collider->setOrientation(RotateAxis::y);
    forwardHandle->transform->setRotation(glm::quat(glm::vec3(90 * Deg2Radian,0,0)));
        forwardHandle->transform->setPosition(glm::vec3(0,0,0.5));
    collider->setHeight(0.5);
    collider->setRadius(0.1f);
	collider->setQueryOnly(true);
    meshFilter = forwardHandle->AddComponent<MeshFilter>();
    meshFilter->setMesh(arrowMesh);
    meshRenderer = forwardHandle->AddComponent<MeshRenderer>();
    meshRenderer->setMaterial(blueMaterial);
    
    //	forwardHandle->transform->setPosition(glm::vec3(0, 0, 2));
	handleScript = forwardHandle->AddComponent<MoveHandle>();
	handleScript->setAxis(MoveAxis::forward);
    //
	shared_ptr<Actor> upHandle = Factory::CreateEditorActor("MoveUpHandle");
    collider = upHandle->AddComponent<CapsuleCollider>();
        upHandle->transform->setPosition(glm::vec3(0,0.5,0));
    collider->setOrientation(RotateAxis::y);
    collider->setHeight(0.5);
    collider->setRadius(0.1f);
	collider->setQueryOnly(true);
    meshFilter = upHandle->AddComponent<MeshFilter>();
    meshFilter->setMesh(arrowMesh);
    meshRenderer = upHandle->AddComponent<MeshRenderer>();
    meshRenderer->setMaterial(greenMaterial);
    //	upHandle->transform->setPosition(glm::vec3(0, 2, 0));
	handleScript = upHandle->AddComponent<MoveHandle>();
	handleScript->setAxis(MoveAxis::up);
    
	getActor()->addChild(rightHandle);
	getActor()->addChild(forwardHandle);
	getActor()->addChild(upHandle);
}

void MoveTool::tick(float deltaSeconds)
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
		actor->transform->rotation = currentActor->transform->rotation;
	}
    
    //    cout << "Rotating" << endl;
    //       getActor()->transform->rotationQuat =  glm::angleAxis(deltaSeconds, glm::vec3(0, 1, 0))* getActor()->transform->rotationQuat;
    
    
}