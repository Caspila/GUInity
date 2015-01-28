#pragma once

#include "ScriptComponent.hpp"
#include "MoveHandle.hpp"

class MoveTool : public ScriptComponent
{
	

public:
	
	MoveTool();
	~MoveTool();

	MoveMode moveMode;

	virtual void awake() override;
    virtual void tick(float deltaSeconds) override;
    
	weak_ptr<MoveHandle> forward, up, right;
};

