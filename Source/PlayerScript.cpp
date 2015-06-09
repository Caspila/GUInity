#include "PlayerScript.hpp"

#include "Actor.hpp"
#include "World.hpp"
#include "Factory.hpp"
#include "AssetDatabase.hpp"
#include "MeshFilter.hpp"
#include "MeshRenderer.hpp"
#include "RigidBody.hpp"
#include "Game.hpp"

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
	moveSpeed = 0.2f;
    rotateSpeed = 5;
    
    cout << "Move speed set to 10!" << endl;
    
    actor = getActor();
    
    objMeshRef = AssetDatabase::getAsset<Mesh>("sphere.obj");
    defaultMaterialRef = AssetDatabase::getAsset<Material>("DefaultMaterial");
    
    
    shared_ptr<Actor> actorLock = actor.lock();
    
    shared_ptr<Actor> bulletSpawnPoint = Factory::CreateActor("BulletSpawnPoint");

    bulletSpawnPoint->transform->setPosition(actorLock->transform->getUp() * 1.5f + actorLock->transform->getPosition());
    
    actorLock->addChildren(bulletSpawnPoint);
    
    this->bulletSpawnPoint = bulletSpawnPoint;

//    shared_ptr<Actor> bulletSpawnChild = Factory::CreateActor("BulletSpawnPointChild");
//    
//    bulletSpawnChild->transform->setPosition(bulletSpawnPoint->transform->getUp() * 1.5f + bulletSpawnPoint->transform->getPosition());
//    
//    bulletSpawnPoint->addChildren(bulletSpawnChild);
//    
//    this->bulletSpawnPoint = bulletSpawnChild;
    
    
//	sphereReference = World::findActor("Sphere");
	//sphereReference = World::findActor("Sphere");
}


void PlayerScript::tick(float deltaSeconds)
{
	//shared_ptr<Transform> transform = getActor()->transform;



	shared_ptr<Actor> lock = actor.lock();
	
	if (!lock)
		return;

    
	shared_ptr<Transform> transform = lock->transform;

	//shared_ptr<Transform> transform = sphereReference->transform;

	if (Input::getKey(GLFW_KEY_UP))
	{

        velocity += transform->getUp() * moveSpeed;
		
	}
	
	
	if (Input::getKey(GLFW_KEY_LEFT))
	{
//        velocity.x -= moveSpeed;
        
		glm::quat rot = transform->getRotation();
//
        glm::quat left = glm::angleAxis(deltaSeconds * rotateSpeed, transform->getForward());
        //
        //
        
        //		transform->setRotationQuat(glm::slerp(rot, right, deltaSeconds));
        transform->setRotation(left * rot);
	}
	if (Input::getKey(GLFW_KEY_RIGHT))
	{
//        velocity.x -= moveSpeed;
		glm::quat rot = transform->getRotation();
//
//		glm::quat right(-transform->getRight());
//        glm::quat newRot;
        glm::quat right = glm::angleAxis(deltaSeconds * rotateSpeed, -transform->getForward());
//
//
        
//		transform->setRotationQuat(glm::slerp(rot, right, deltaSeconds));
        transform->setRotation(right * rot);
//                transform->setRotationQuat(right);
	}
    
    if (Input::getKeyPressed(GLFW_KEY_SPACE))
	{
//        shared_ptr<Actor> actor = Game::world->findActor("Light");
//        Factory::DestroyActor(actor);
//        shared_ptr<Actor> bulletActor = lock->clone();
//
//        bulletActor->transform->setScale(glm::vec3(0.2f,0.2f,0.2f));
//
//		bulletActor->transform->setPosition(transform->getPosition() + transform->getUp() * (1.0f ));
        
        
        shared_ptr<Actor> bulletActor = Factory::CreateActor("bullet");
		shared_ptr<MeshFilter> meshFilter = bulletActor->AddComponent<MeshFilter>();
		meshFilter->setMesh(objMeshRef);
		shared_ptr<MeshRenderer> meshRenderer = bulletActor->AddComponent<MeshRenderer>();

        bulletActor->transform->setScale(glm::vec3(0.2f,0.2f,0.2f));
        
		meshRenderer->setMaterial(defaultMaterialRef);
        
        shared_ptr<Actor> bulletSpawnLock = bulletSpawnPoint.lock();
        
        bulletActor->transform->setPosition(bulletSpawnLock->transform->getWorldPosition());
        
        
        shared_ptr<RigidBody> rb = bulletActor->AddComponent<RigidBody>();

        cout << "transform up:" << transform->getUp()<< endl;
        glm::vec3 forceVec = transform->getUp() * 250.0f;
        rb->addForce(forceVec);
        cout << "Force added:" << forceVec<< endl;
        rb->setGravity(false);
        
	}
    
    glm::vec3 position = transform->getPosition();
	
    position += velocity * deltaSeconds;
	
    transform->setPosition(position);
    
    applyDrag(deltaSeconds);


}

void PlayerScript::applyDrag(float deltaSeconds)
{
    velocity -= velocity * dragFactor;
}

void PlayerScript::onCollision(Actor* actor)
{
	cout << "This actor (" << getActor()->name << ") collided with (" << actor->name << ")" << endl;

}

void PlayerScript::onTrigger(Actor* actor)
{
	cout << "This actor (" << getActor()->name << ") triggered with (" << actor->name << ")" << endl;

}


shared_ptr<Component> PlayerScript::clone()
{
    shared_ptr<PlayerScript> compClone = make_shared<PlayerScript>();
    
    
    return compClone;
}

