#pragma once
#include "ScriptComponent.hpp"
#include "Enums.hpp"
#include <glm/common.hpp>

class RotateHandle :
	public ScriptComponent
{
public:
	RotateHandle();
	~RotateHandle();

	RotateAxis axis;

	void setAxis(RotateAxis axis);

	virtual void awake() override;
	virtual void tick(float deltaSeconds) override;

private:

	glm::vec3 rotationAxis;
	bool isPressed;
	float lastDot;
};

