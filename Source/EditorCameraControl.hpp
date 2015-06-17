#pragma once

#include "ScriptComponent.hpp"

class EditorCameraControl : public ScriptComponent
{
public:
	EditorCameraControl();
	~EditorCameraControl();

	float moveSpeed;
	float rotationSpeed;


	virtual void init();
	virtual void tick(float deltaSeconds);
    
};

