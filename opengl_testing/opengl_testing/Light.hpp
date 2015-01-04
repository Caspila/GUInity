#pragma once

#include "Transform.hpp"
#include "Subject.hpp"
#include "Component.hpp"

class Light : public Component, public Subject<Light>
#ifdef GUINITY_DEBUG
	, public StaticCounter<Light>
#endif
{
public:
	Light();
	//Light(glm::vec3 color);
	~Light();

	//Transform transform;
	glm::vec3 color;

	virtual void init() override;

};

