#pragma once
#include "ScriptComponent.hpp"
#include "RotateHandle.hpp"
class RotateTool :
	public ScriptComponent
{
public:
	RotateTool();
	~RotateTool();

	virtual void awake() override;

	weak_ptr<RotateHandle> x, y, z;
};
