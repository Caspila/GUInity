//
//  AsteroidSpawner.cpp
//  GUInity_MacOS
//
//  Created by Guilherme Cunha on 2015-06-16.
//  Copyright (c) 2015 Guilherme Cunha. All rights reserved.
//

#include "AsteroidSpawner.hpp"
#include "Math.hpp"
#include "MeshFilter.hpp"
#include "MeshRenderer.hpp"
#include "BoxCollider.hpp"
#include "Material.hpp"
#include "Shader.hpp"
#include "Mesh.hpp"
#include "Factory.hpp"
#include "RigidBody.hpp"
#include "KillOnCollision.hpp"
#include "KillDistanceBased.hpp"
#include "MeshCollider.hpp"

void AsteroidSpawner::awake()
{
    minWaitTime = 5;
    maxWaitTime = 10;
    elapsedTime = 0;
    
    waitTime = randRange(minWaitTime, maxWaitTime);
    
    createAsteroidPrefab();
    asteroidPrefab->setActive(false);
}

void AsteroidSpawner::tick(float deltaSeconds)
{
    if(elapsedTime > waitTime)
    {
        spawnAsteroid();
        waitTime = randRange(minWaitTime, maxWaitTime);
        elapsedTime = 0.0f;
    }
    elapsedTime += deltaSeconds;
}

void AsteroidSpawner::createAsteroidPrefab()
{
    
    shared_ptr<Mesh> asteroidMesh =  AssetDatabase::getAsset<Mesh>("asteroid.fbx");
    
    shared_ptr<Material> asteroidMaterial = AssetDatabase::getAsset<Material>("AsteroidMaterial");
    
    asteroidPrefab = Factory::CreateActor("AsteroidPrefab");
    
    shared_ptr<MeshFilter> asteroidMeshFilter = asteroidPrefab->AddComponent<MeshFilter>();
    asteroidMeshFilter->setMesh(asteroidMesh);
    shared_ptr<MeshRenderer> asteroidMeshRenderer = asteroidPrefab->AddComponent<MeshRenderer>();
    asteroidMeshRenderer->setMaterial(asteroidMaterial);
    
    asteroidPrefab->transform->setPosition(glm::vec3(3,0,0));
    
    shared_ptr<RigidBody> asteroidRigidbody = asteroidPrefab->AddComponent<RigidBody>();
    asteroidRigidbody->setGravity(false);
    asteroidRigidbody->addTorque(glm::vec3(100,100,100));
    
//    shared_ptr<BoxCollider> asteroidCollider = asteroidPrefab->AddComponent<BoxCollider>();
    shared_ptr<MeshCollider> asteroidCollider = asteroidPrefab->AddComponent<MeshCollider>();
    asteroidCollider->setIsTrigger(true);
    asteroidPrefab->AddComponent<KillOnCollision>();
    asteroidPrefab->AddComponent<KillDistanceBased>();
}

void AsteroidSpawner::spawnAsteroid()
{
    cout<< "Create asteroid!" << endl;
    
    shared_ptr<Actor> ac = asteroidPrefab->clone();
    ac->setActive(true);
    
    float angle = randRange(0.0f, PI);
    
    float angleSin = sin(angle);
    float angleCos = cos(angle);
    
    glm::vec3 pos = glm::vec3(angleSin,angleCos,0) *spawnRadius;
    
    cout << "Pos: "<<pos<< "\n";
    

    
    float forceScale = 50;
    
    shared_ptr<RigidBody> ridigBody =    ac->GetComponent<RigidBody>();

    ac->transform->setPosition(pos);
    ridigBody->resetPosition();
    
    ridigBody->addForce(-normalize(pos)*forceScale);
    
    ridigBody->addTorque(randUnitVectorXYZ()*forceScale);
    
    ac->name = "Asteroid";
    
    
}

