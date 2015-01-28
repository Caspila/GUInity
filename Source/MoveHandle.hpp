#pragma once

#include <glm/common.hpp>
#include "ScriptComponent.hpp"
#include "Enums.hpp"

class MoveHandle : public ScriptComponent
{


public:

	MoveHandle();
	~MoveHandle();

	MoveAxis axis;
	
	void setAxis(MoveAxis axis);

	virtual void tick(float deltaSeconds) override;

private:
	bool isPressed;
};

