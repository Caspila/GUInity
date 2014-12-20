#pragma once

#include "Module.h"
#include "ScriptComponent.h"
#include "Input.h"
#include "Transform.h"
#include "Script.h"

class PlayerScript : public Script
{
public:
	PlayerScript ();
	~PlayerScript();

	virtual void tick(float deltaSecods);

	float moveSpeed;
};

