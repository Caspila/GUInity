#pragma once

#include "Actor.h"
#include "Input.h"

class Player : public Actor
{
public:
	Player(string name, shared_ptr<MeshRenderer> mesh);
	~Player();

	void tick(float deltaSeconds) override;

	float moveSpeed;

};