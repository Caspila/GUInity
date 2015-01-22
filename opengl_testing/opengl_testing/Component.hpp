#pragma once

#include "Module.hpp"
#include "SerializationStructs.hpp"

class Actor;

class Component : public enable_shared_from_this<Component>
//#ifdef GUINITY_DEBUG
//	:public StaticCounter<Component>
//#endif
{
public:
	Component();
	virtual ~Component();

	virtual void setActive(bool isActive) {};

	virtual void awake() {};
	virtual void tick(float deltaSecods) {};
	virtual void init() {};

	weak_ptr<Actor> actor;

	shared_ptr<Actor> getActor();
	void setActor(weak_ptr<Actor> actor);

    virtual shared_ptr<ComponentDescription> getComponentDescription() { return make_shared<ComponentDescription>();};
    virtual shared_ptr<Component> clone() { shared_ptr<Component> compClone = make_shared<Component>();return compClone;};
    
    virtual void deserialize(shared_ptr<ComponentDescription> desc) {};
    
#ifdef GUINITY_DEBUG
	static int count;
#endif
};

