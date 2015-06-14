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
    
    shared_ptr<Mesh> cylinderMesh = AssetDatabase::getAsset<Mesh>("rotateHandle.fbx");


    shared_ptr<Material> redMaterial = AssetDatabase::getAsset<Material>("RedDefaultMaterial");
    redMaterial->setParamVec4("_difuseColor",glm::vec4(1,0,0,1));
    shared_ptr<Material> blueMaterial = AssetDatabase::getAsset<Material>("BlueDefaultMaterial");
    blueMaterial->setParamVec4("_difuseColor",glm::vec4(0,0,1,1));
    shared_ptr<Material> greenMaterial = AssetDatabase::getAsset<Material>("GreenDefaultMaterial");
    greenMaterial->setParamVec4("_difuseColor",glm::vec4(0,1,0,1));
    
    
	shared_ptr<Actor> xHandle = Factory::CreateEditorActor("RotateXAxisHandle");
    xHandle->transform->setRotation(glm::quat(glm::vec3(0,0,90*Deg2Radian)));
    shared_ptr<MeshFilter> meshFilter = xHandle->AddComponent<MeshFilter>();
	meshFilter->setMesh(cylinderMesh);
    shared_ptr<MeshRenderer> meshRenderer = xHandle->AddComponent<MeshRenderer>();
    meshRenderer->setMaterial( redMaterial);
    shared_ptr<MeshCollider> collider = xHandle->AddComponent<MeshCollider>();
	collider->setQueryOnly(true);
	shared_ptr<RotateHandle> handleScript = xHandle->AddComponent<RotateHandle>();
	handleScript->setAxis(RotateAxis::x);

    
	shared_ptr<Actor> yHandle = Factory::CreateEditorActor("RotateYAxisHandle");
    yHandle->transform->setScale(glm::vec3(1,1,1)*0.9);
    meshFilter = yHandle->AddComponent<MeshFilter>();
    meshFilter->setMesh(cylinderMesh);
    meshRenderer = yHandle->AddComponent<MeshRenderer>();
    meshRenderer->setMaterial( greenMaterial);
	collider = yHandle->AddComponent<MeshCollider>();
	collider->setQueryOnly(true);
	handleScript = yHandle->AddComponent<RotateHandle>();
	handleScript->setAxis(RotateAxis::y);

	shared_ptr<Actor> zHandle = Factory::CreateEditorActor("RotateZAxisHandle");
    zHandle->transform->setRotation(glm::quat(glm::vec3(90*Deg2Radian,0,0)));
        zHandle->transform->setScale(glm::vec3(1,1,1)*0.8);
    shared_ptr<MeshFilter>  meshFilterZ = zHandle->AddComponent<MeshFilter>();
	meshFilterZ->setMesh(cylinderMesh);
    shared_ptr<MeshRenderer>   meshRendererZ = zHandle->AddComponent<MeshRenderer>();
    meshRendererZ->setMaterial( blueMaterial);
   	shared_ptr<MeshCollider> colliderZ = zHandle->AddComponent<MeshCollider>();
	colliderZ->setQueryOnly(true);
	shared_ptr<RotateHandle> handleScriptZ = zHandle->AddComponent<RotateHandle>();
	handleScriptZ->setAxis(RotateAxis::z);

	getActor()->addChild(xHandle);
	getActor()->addChild(yHandle);
	getActor()->addChild(zHandle);
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