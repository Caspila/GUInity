#pragma once

#include "Module.hpp"
#include "ScriptComponent.hpp"
#include "Input.hpp"
#include "Transform.hpp"
//#include "Script.hpp"

class PlayerScript : public ScriptComponent
{
public:

	virtual void awake() override;
	virtual void tick(float deltaSecods) override;

	float moveSpeed;

	PlayerScript();
	~PlayerScript();

	weak_ptr <Actor> sphereReference;

	
	virtual void onCollision(Actor* actor) override;
	virtual void onTrigger(Actor* actor) override;

private:
	
	
};

