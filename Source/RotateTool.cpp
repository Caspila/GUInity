#include "RotateTool.hpp"
#include "SphereCollider.hpp"
#include "Factory.hpp"
#include "RotateHandle.hpp"
#include "MeshCollider.hpp"
#include "Mesh.hpp"
#include "MeshRenderer.hpp"
#include "Editor.hpp"
#include "Math.hpp"
#include "AssetDatabase.hpp"
#include "Material.hpp"
#include "MeshFilter.hpp"

RotateTool::RotateTool()
{
}


RotateTool::~RotateTool()
{
}

void RotateTool::awake()
{
    
    shared_ptr<Mesh> cylinderMesh =dynamic_pointer_cast<Mesh>(AssetDatabase::getAsset("cylinder3.fbx"));
    shared_ptr<Material> defaultMat = dynamic_pointer_cast<Material>(AssetDatabase::getAsset("DefaultMaterial.fbx"));

	shared_ptr<Actor> rightHandle = Factory::CreateEditorActor("RotateZAxisHandle");
    //    rightHandle->transform->setRotationQuat(glm::angleAxis(90*Deg2Radian,glm::vec3(0, 1, 0)));
//    rightHandle->transform->setPosition(glm::vec3(0, 0, 0));
    rightHandle->transform->setRotationQuat(glm::angleAxis(90*Deg2Radian,glm::vec3(1, 0, 0)));
    rightHandle->transform->setScale(glm::vec3(1, 1, 0.1f));
    
	shared_ptr<MeshFilter> meshFilter = rightHandle->AddComponent<MeshFilter>();
	meshFilter->setMesh(cylinderMesh);
    shared_ptr<MeshRenderer> meshRenderer = rightHandle->AddComponent<MeshRenderer>();
    meshRenderer->material = defaultMat;
    
    
    shared_ptr<MeshCollider> collider = rightHandle->AddComponent<MeshCollider>();
    //shared_ptr<CapsuleCollider> collider = rightHandle->AddComponent<CapsuleCollider>();
	collider->setQueryOnly(true);
	//collider->setOrientation(RotateAxis::x);
	//collider->setHeight(0.01f);

	shared_ptr<RotateHandle> handleScript = rightHandle->AddComponent<RotateHandle>();
	handleScript->setAxis(RotateAxis::z);

	shared_ptr<Actor> forwardHandle = Factory::CreateEditorActor("RotateXAxisHandle");
    forwardHandle->transform->setScale(glm::vec3(1, 1, 0.1f));
    forwardHandle->transform->setRotationQuat(glm::angleAxis(90*Deg2Radian,glm::vec3(0, 1, 0)));
    meshFilter = forwardHandle->AddComponent<MeshFilter>();
    meshFilter->setMesh(cylinderMesh);
    meshRenderer = forwardHandle->AddComponent<MeshRenderer>();
    meshRenderer->material = defaultMat;
	collider = forwardHandle->AddComponent<MeshCollider>();
	collider->setQueryOnly(true);
//	forwardHandle->transform->setPosition(glm::vec3(0, 0, 2));
	handleScript = forwardHandle->AddComponent<RotateHandle>();
	handleScript->setAxis(RotateAxis::x);
	//

	shared_ptr<Actor> upHandle = Factory::CreateEditorActor("RotateYAxisHandle");
    upHandle->transform->setScale(glm::vec3(1, 1, 0.1f));
//    upHandle->transform->setRotationQuat(glm::angleAxis(90*Deg2Radian,glm::vec3(1, 0, 0)));
    meshFilter = upHandle->AddComponent<MeshFilter>();
	meshFilter->setMesh(cylinderMesh);
    meshRenderer = upHandle->AddComponent<MeshRenderer>();
    meshRenderer->material = defaultMat;
   	collider = upHandle->AddComponent<MeshCollider>();
//	collider = upHandle->AddComponent<CapsuleCollider>();

	collider->setQueryOnly(true);
//	upHandle->transform->setPosition(glm::vec3(0, 2, 0));
	handleScript = upHandle->AddComponent<RotateHandle>();
	handleScript->setAxis(RotateAxis::y);
	//
	getActor()->addChildren(rightHandle);
	getActor()->addChildren(forwardHandle);
	getActor()->addChildren(upHandle);
}

void RotateTool::tick(float deltaSeconds)
{
    shared_ptr<Actor> currentActor = Editor::currentSelectedActor;
	if (!currentActor)
		return;
    
    
	shared_ptr<Actor> actor = getActor();
	if (actor)
	{
//        cout << "Align" <<  "currentActor " << currentActor->name << endl;
		actor->transform->position = currentActor->transform->position;
		//actor->transform->rotationQuat = currentActor->transform->rotationQuat;
	}
    
    //    cout << "Rotating" << endl;
    //       getActor()->transform->rotationQuat =  glm::angleAxis(deltaSeconds, glm::vec3(0, 1, 0))* getActor()->transform->rotationQuat;
    
    
}