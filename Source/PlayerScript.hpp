#pragma once

#include "Module.hpp"
#include "ScriptComponent.hpp"
#include "Input.hpp"
#include "Transform.hpp"
//#include "Script.hpp"


class Material;
class Mesh;

/*!
 * Your documentation comment will go here
 */
class PlayerScript : public ScriptComponent
{
public:

	virtual void awake() override;
	virtual void tick(float deltaSecods) override;

    float dragFactor;
	float moveSpeed;
    float rotateSpeed;
    glm::vec3 velocity;
    
	PlayerScript();
	virtual ~PlayerScript();

	weak_ptr <Actor> actor;
    
    void applyDrag(float deltaSeconds);
    
    shared_ptr<Material> defaultMaterialRef;
    shared_ptr<Mesh> objMeshRef;
    weak_ptr<Actor> bulletSpawnPoint;
	
	virtual void onCollision(Actor* actor) override;
	virtual void onTrigger(Actor* actor) override;
    
    virtual shared_ptr<Component> clone() override;

private:
	
	
};

