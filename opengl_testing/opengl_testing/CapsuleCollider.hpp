#pragma once
#include "Collider.hpp"
#include "Enums.hpp"

class CapsuleCollider :
	public Collider
{
public:
	CapsuleCollider();
	~CapsuleCollider();

	virtual void init();

	RotateAxis orientation;

	void setOrientation(RotateAxis orientation);

	void setHeight(float height);

	void setRadius(float radius);
};

