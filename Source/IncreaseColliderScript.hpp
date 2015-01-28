#pragma once
#include "ScriptComponent.hpp"
class IncreaseColliderScript :
	public ScriptComponent
{
public:
	IncreaseColliderScript();
	~IncreaseColliderScript();

	virtual void awake() override;
	virtual void tick(float deltaSecods) override;

};



