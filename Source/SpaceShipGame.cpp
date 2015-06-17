//
//  SpaceShipGame.cpp
//  GUInity_MacOS
//
//  Created by Guilherme Cunha on 2015-06-17.
//  Copyright (c) 2015 Guilherme Cunha. All rights reserved.
//

#include "SpaceShipGame.hpp"

// ASSETS
#include "AssetDatabase.hpp"
#include "Material.hpp"
#include "Font.hpp"
#include "Mesh.hpp"
#include "Shader.hpp"
#include "Sound.hpp"
#include "Texture.hpp"
#include "PhysicsMaterial.hpp"
#include "Factory.hpp"

// ACTOR / COMPONENTS
#include "Actor.hpp"
#include "Camera.hpp"
#include "MeshRenderer.hpp"
#include "FontMesh.hpp"
#include "Light.hpp"
#include "RigidBody.hpp"
#include "BoxCollider.hpp"
#include "MeshFilter.hpp"
#include "SphereCollider.hpp"
#include "MeshCollider.hpp"
#include "MeshImporter.hpp"

// SCRIPTS
#include "EditorCameraControl.hpp"
#include "PlayerScript.hpp"
#include "KillOnCollision.hpp"
#include "AsteroidSpawner.hpp"
#include "PointsTracker.hpp"

#include "Math.hpp"

 void SpaceShipGame::setupInitialScene()
{
    shared_ptr<Font> font = AssetDatabase::createFont("space age.ttf",76);
    
    shared_ptr<Mesh> cubeMesh = AssetDatabase::createMeshFromFBX("box.fbx");
    shared_ptr<Mesh> sphereMesh =  AssetDatabase::getAsset<Mesh>("sphere.obj");
    shared_ptr<Mesh> spaceShipMesh =  AssetDatabase::getAsset<Mesh>("spaceShip.fbx");
    shared_ptr<Mesh> asteroidMesh =  AssetDatabase::getAsset<Mesh>("asteroid.fbx");
    
    
    shared_ptr<Texture> spaceShipTexture = AssetDatabase::getAsset<Texture>("spaceShipTexture.png");
    shared_ptr<Texture> spaceBKGTexture = AssetDatabase::getAsset<Texture>("spaceBKG.png");
    shared_ptr<Texture> asteroidTexture = AssetDatabase::getAsset<Texture>("asteroidTexture.png");
    
    
    shared_ptr<Shader> diffuseShader = AssetDatabase::createShader("LightShader", CommonData("vsLight.vs"), CommonData("fsLight.fragmentshader"));
    shared_ptr<Shader> unlitShader = AssetDatabase::createShader("UnlitShader", CommonData("vsUnlit.vs"), CommonData("fsUnlit.fragmentshader"));
    
    shared_ptr<Material> defaultMaterial = AssetDatabase::createMaterial("DefaultMaterial", diffuseShader);
    defaultMaterial->setParamVec2
    ("_tiling", glm::vec2(1,1));
    
    shared_ptr<Material> spaceShipMaterial = AssetDatabase::createMaterial("SpaceShipMaterial", diffuseShader);
    spaceShipMaterial->setParamTexture("_textureSampler", spaceShipTexture);
    spaceShipMaterial->setParamVec2
    ("_tiling", glm::vec2(1,1));
    
    shared_ptr<Material> spaceBKGMaterial = AssetDatabase::createMaterial("SpaceBKGMaterial", diffuseShader);
    spaceBKGMaterial->setParamTexture("_textureSampler", spaceBKGTexture);
    spaceBKGMaterial->setParamVec2
    ("_tiling", glm::vec2(3,3));
    
    shared_ptr<Material> asteroidMaterial = AssetDatabase::createMaterial("AsteroidMaterial", diffuseShader);
    asteroidMaterial->setParamTexture("_textureSampler", asteroidTexture);
    asteroidMaterial->setParamVec2
    ("_tiling", glm::vec2(1,1));
    
    shared_ptr<Material> fontMaterial = AssetDatabase::createMaterial("FontMaterial", unlitShader);
    fontMaterial->setParamTexture("_textureSampler", font->getFontTexture());
    fontMaterial->setParamVec4("_difuseColor", glm::vec4(0.8f,0.1,0.1f,1));
    
    
   
        shared_ptr<Actor> spaceShipRoot = Factory::CreateActor("SpaceShip");
        
        shared_ptr<MeshFilter> meshFilter = spaceShipRoot->AddComponent<MeshFilter>();
        meshFilter->setMesh(spaceShipMesh);
        shared_ptr<MeshRenderer> meshRenderer = spaceShipRoot->AddComponent<MeshRenderer>();
        meshRenderer->setMaterial(spaceShipMaterial);
        spaceShipRoot->transform->setScale(glm::vec3(1.2,1.2,1.2));
        shared_ptr<MeshCollider> spaceShipCollider = spaceShipRoot->AddComponent<MeshCollider>();
        spaceShipCollider->setIsTrigger(true);
        spaceShipRoot->AddComponent<PlayerScript>();
        
        
        shared_ptr<Actor> asteroidSpawner = Factory::CreateActor("AsteroidSpawner");
        asteroidSpawner->AddComponent<AsteroidSpawner>();
        
        
        shared_ptr<Actor> bkg = Factory::CreateActor("BKG");
        shared_ptr<MeshFilter> bkgMeshFilter = bkg->AddComponent<MeshFilter>();
        bkgMeshFilter->setMesh(cubeMesh);
        shared_ptr<MeshRenderer> bkgMeshRenderer = bkg->AddComponent<MeshRenderer>();
        bkgMeshRenderer->setMaterial(spaceBKGMaterial);
        
        bkg->transform->setPosition(glm::vec3(0,0,-5));
        bkg->transform->setScale(glm::vec3(3,3,0.1));
        
        shared_ptr<Actor> fontTest = Factory::CreateActor("Points");
        shared_ptr<FontMesh> fontMesh = fontTest->AddComponent<FontMesh>();
        fontMesh->setFont(font);
        fontMesh->setText("a");
        shared_ptr<MeshRenderer> fontMeshRenderer = fontTest->AddComponent<MeshRenderer>();
        fontMeshRenderer->setMaterial(fontMaterial);
        
        fontTest->AddComponent<PointsTracker>();
        fontTest->transform->setPosition(glm::vec3(0,5,0));
        
        
		shared_ptr<Actor> myLight = Factory::CreateActor("Light");
		myLight->transform->setPosition(glm::vec3(0, 10, 10));
		myLight->AddComponent<Light>();
        
		shared_ptr<Actor> myCamera = Factory::CreateActor("Camera");
		myCamera->transform->setPosition(glm::vec3(0, 0, 10));
		myCamera->transform->setRotation(glm::quat(glm::vec3(0, 180 * Deg2Radian, 0)));
		myCamera->AddComponent<Camera>();

}