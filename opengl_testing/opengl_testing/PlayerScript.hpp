#pragma once

#include "Module.hpp"
#include "ScriptComponent.hpp"
#include "Input.hpp"
#include "Transform.hpp"
#include "Script.hpp"

class PlayerScript : public ScriptComponent
{
public:

	virtual void awake() override;
	virtual void tick(float deltaSecods) override;

	float moveSpeed;

	~PlayerScript();

	weak_ptr <Actor> sphereReference;

	void setSphereRef(weak_ptr<Actor> actor);


private:
	//PlayerScript();
	
};

