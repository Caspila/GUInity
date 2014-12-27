#pragma once

#include <glm/common.hpp>
#include "ScriptComponent.hpp"

class MoveHandle : public ScriptComponent
{
public:
	MoveHandle();
	~MoveHandle();

	glm::vec3 axis;
	
	void setAxis(glm::vec3 axis);

	virtual void tick(float deltaSeconds) override;

private:
	bool isPressed;
};

