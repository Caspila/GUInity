#include "PlayerScript.hpp"

#include "Actor.hpp"
#include "World.hpp"
#include "Factory.hpp"
#include "AssetDatabase.hpp"
#include "MeshFilter.hpp"
#include "MeshRenderer.hpp"
#include "RigidBody.hpp"
#include "Game.hpp"

PlayerScript::PlayerScript()
{

}


PlayerScript::~PlayerScript()
{
	cout << "PlayerScript Destroyed";
}

void PlayerScript::awake()
{
	moveSpeed = 1;
    rotateSpeed = 2;
    
    cout << "Move speed set to 10!" << endl;
    
    actor = getActor();
    
    objMeshRef = AssetDatabase::getAsset<Mesh>("sphere.obj");
    defaultMaterialRef = AssetDatabase::getAsset<Material>("DefaultMaterial");
    
    
    
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
        
		glm::quat rot = transform->getRotationQuat();
//
        glm::quat left = glm::angleAxis(deltaSeconds * rotateSpeed, transform->getForward());
        //
        //
        
        //		transform->setRotationQuat(glm::slerp(rot, right, deltaSeconds));
        transform->setRotationQuat(left * rot);
	}
	if (Input::getKey(GLFW_KEY_RIGHT))
	{
//        velocity.x -= moveSpeed;
		glm::quat rot = transform->getRotationQuat();
//
//		glm::quat right(-transform->getRight());
//        glm::quat newRot;
        glm::quat right = glm::angleAxis(deltaSeconds * rotateSpeed, -transform->getForward());
//
//
        
//		transform->setRotationQuat(glm::slerp(rot, right, deltaSeconds));
        transform->setRotationQuat(right * rot);
//                transform->setRotationQuat(right);
	}
    
    if (Input::getKeyPressed(GLFW_KEY_SPACE))
	{
        shared_ptr<Actor> actor = Game::world->findActor("Light");
        Factory::DestroyActor(actor);
//        shared_ptr<Actor> bulletActor = lock->clone();
//        
////        bulletActor->transform->setScale(glm::vec3(0.2f,0.2f,0.2f));
//        
//		bulletActor->transform->setPosition(transform->getPosition() + transform->getUp() * (1.0f ));
        
        /*
        shared_ptr<Actor> bulletActor = Factory::CreateActor("bullet");
		shared_ptr<MeshFilter> meshFilter = bulletActor->AddComponent<MeshFilter>();
		meshFilter->setMesh(objMeshRef);
		shared_ptr<MeshRenderer> meshRenderer = bulletActor->AddComponent<MeshRenderer>();

        bulletActor->transform->setScale(glm::vec3(0.2f,0.2f,0.2f));
        
		meshRenderer->material = defaultMaterialRef;
        
        bulletActor->transform->setPosition(transform->getPosition() + transform->getUp() * (1.0f ));
        
        shared_ptr<RigidBody> rb = bulletActor->AddComponent<RigidBody>();
        rb->addForce(transform->getUp() * 500.0f);
        rb->setGravity(false);
        */
	}
    
    glm::vec3 position = transform->getPosition();
	
    position += velocity * deltaSeconds;
	
    transform->setPosition(position);
    
    applyDrag();


}

void PlayerScript::applyDrag()
{
    velocity -= velocity * 0.1f;
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

