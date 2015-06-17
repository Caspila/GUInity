#pragma once

#include "Module.hpp"
#include "ScriptComponent.hpp"
#include "Input.hpp"
#include "Transform.hpp"


class Material;
class Mesh;


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
    shared_ptr<Material> missileMaterial;
    shared_ptr<Mesh> missileMeshRef;
    weak_ptr<Actor> bulletSpawnPoint;
	void checkBounds();
    
    
	virtual void onCollision(shared_ptr<Actor> actor) override;
	virtual void onTrigger(shared_ptr<Actor> actor) override;
    
    virtual shared_ptr<Component> clone() override;

    
private:
	
	
};

