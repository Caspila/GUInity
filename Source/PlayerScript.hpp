#pragma once

#include "Module.hpp"
#include "ScriptComponent.hpp"
#include "Input.hpp"
#include "Transform.hpp"
//#include "Script.hpp"


class Material;
class Mesh;

class PlayerScript : public ScriptComponent
{
public:

	virtual void awake() override;
	virtual void tick(float deltaSecods) override;

	float moveSpeed;
    float rotateSpeed;
    glm::vec3 velocity;
    
	PlayerScript();
	~PlayerScript();

	weak_ptr <Actor> actor;
    
    void applyDrag();
    
    shared_ptr<Material> defaultMaterialRef;
    shared_ptr<Mesh> objMeshRef;
    
	
	virtual void onCollision(Actor* actor) override;
	virtual void onTrigger(Actor* actor) override;
    
    virtual shared_ptr<Component> clone() override;

private:
	
	
};

