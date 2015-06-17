#include "PlayerScript.hpp"

#include "Actor.hpp"
#include "World.hpp"
#include "Factory.hpp"
#include "AssetDatabase.hpp"
#include "MeshFilter.hpp"
#include "MeshRenderer.hpp"
#include "RigidBody.hpp"
#include "Game.hpp"
#include "PointsTracker.hpp"
#include "AsteroidSpawner.hpp"
#include "KillDistanceBased.hpp"

/*!
 * Your documentation comment will go here
 */
PlayerScript::PlayerScript()
{

}


PlayerScript::~PlayerScript()
{
	cout << "PlayerScript Destroyed";
}

void PlayerScript::awake()
{
  	dragFactor = 0.01f;
	moveSpeed = 0.1f;
    rotateSpeed = 5;
    
    cout << "Move speed set to 10!" << endl;
    
    actor = getActor();
    
    missileMeshRef = AssetDatabase::getAsset<Mesh>("missileLQ.fbx");
    defaultMaterialRef = AssetDatabase::getAsset<Material>("SpaceBKGMaterial");

    shared_ptr<Texture> missileTexture =AssetDatabase::getAsset<Texture>("missileTexture.png");
    
    shared_ptr<Shader> litShader = AssetDatabase::getAsset<Shader>("LightShader");
    
    missileMaterial = AssetDatabase::createMaterial("MissileMaterial", litShader);
    missileMaterial->setParamTexture("_textureSampler", missileTexture);
    
    shared_ptr<Actor> actorLock = actor.lock();
    
    shared_ptr<Actor> bulletSpawnPoint = Factory::CreateActor("BulletSpawnPoint");

    bulletSpawnPoint->transform->setPosition(actorLock->transform->getUp() * 0.75f + actorLock->transform->getPosition());
    
    actorLock->addChild(bulletSpawnPoint);
    
    this->bulletSpawnPoint = bulletSpawnPoint;
}


void PlayerScript::tick(float deltaSeconds)
{
	shared_ptr<Actor> lock = actor.lock();
	
	if (!lock)
		return;

    
	shared_ptr<Transform> transform = lock->transform;

	if (Input::getKey(GLFW_KEY_UP))
	{

        velocity += transform->getUp() * moveSpeed;
		
	}
	
	
	if (Input::getKey(GLFW_KEY_LEFT))
	{
		glm::quat rot = transform->getRotation();
        glm::quat left = glm::angleAxis(deltaSeconds * rotateSpeed, transform->getForward());

        transform->setRotation(left * rot);
	}
	if (Input::getKey(GLFW_KEY_RIGHT))
	{
		glm::quat rot = transform->getRotation();

        glm::quat right = glm::angleAxis(deltaSeconds * rotateSpeed, -transform->getForward());

        transform->setRotation(right * rot);
	}
    
    if (Input::getKeyPressed(GLFW_KEY_SPACE))
	{
        shared_ptr<Actor> bulletActor = Factory::CreateActor("Missile");
		shared_ptr<MeshFilter> meshFilter = bulletActor->AddComponent<MeshFilter>();
		meshFilter->setMesh(missileMeshRef);
		shared_ptr<MeshRenderer> meshRenderer = bulletActor->AddComponent<MeshRenderer>();


        bulletActor->transform->setScale(glm::vec3(0.06f,0.06f,0.06f));

		meshRenderer->setMaterial(missileMaterial);
        
        shared_ptr<Actor> bulletSpawnLock = bulletSpawnPoint.lock();
        

        bulletActor->transform->setPosition(bulletSpawnLock->transform->getWorldPosition());
        
        bulletActor->transform->setRotation(transform->getRotation());
        
        shared_ptr<RigidBody> rb = bulletActor->AddComponent<RigidBody>();

        
        
        shared_ptr<Collider> collider = bulletActor->AddComponent<BoxCollider>();

        collider->setIsTrigger(true);
        

        
        
        glm::vec3 forceVec = transform->getUp() * 600.0f;
        rb->addForce(forceVec);
        rb->setGravity(false);
        
        bulletActor->AddComponent<KillDistanceBased>();

        
	}
    
    glm::vec3 position = transform->getPosition();
	
    position += velocity * deltaSeconds;
	
    transform->setPosition(position);
    
    checkBounds();
    
    
//    glm::vec2 offset = defaultMaterialRef->getParamVec2("_offset");
//    offset += glm::vec2(velocity.x,velocity.y) * deltaSeconds * moveSpeed * 0.1f;
//    defaultMaterialRef->setParamVec2("_offset", offset);
    
    applyDrag(deltaSeconds);


}

void PlayerScript::checkBounds()
{
    int width = 7.7;
    int height = 5.7;

    shared_ptr<Actor> lock = actor.lock();
	
	if (!lock)
		return;
    
    glm::vec3 newPos = lock->transform->getPosition();
    if(newPos.x < -width)
        newPos.x = width;
    if(newPos.x > width)
        newPos.x = -width;
    
    if(newPos.y < -height)
        newPos.y = height;
    if(newPos.y > height)
        newPos.y = -height;
    
    lock->transform->setPosition(newPos);
}

void PlayerScript::applyDrag(float deltaSeconds)
{
    velocity -= velocity * dragFactor;
}

void PlayerScript::onCollision(shared_ptr<Actor> actor)
{

}

void PlayerScript::onTrigger(shared_ptr<Actor> actor)
{
    if(actor->name.compare("Asteroid")==0)
    {
       PointsTracker::setGameOver();
    
        shared_ptr<Actor> asteroidSpawnerRef =
        Game::world->findActor("AsteroidSpawner");
        if(asteroidSpawnerRef)
            asteroidSpawnerRef->setActive(false);
        
        setActive(false);
    }
}


shared_ptr<Component> PlayerScript::clone()
{
    shared_ptr<PlayerScript> compClone = make_shared<PlayerScript>();
    
    
    return compClone;
}


