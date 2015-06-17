#ifndef __GUInity_MacOS__KillOnCollision__
#define __GUInity_MacOS__KillOnCollision__

#include <iostream>
#include "Module.hpp"
#include "ScriptComponent.hpp"
#include "Input.hpp"
#include "Transform.hpp"


class Material;
class Mesh;


using namespace std;
class KillOnCollision : public ScriptComponent
{
public:
    
	virtual void awake() override;
    
    std::string colliderName;
    
	virtual void onTrigger(shared_ptr<Actor> actor) override;
    
    
    virtual shared_ptr<Component> clone() override;
};

#endif /* defined(__GUInity_MacOS__KillOnCollision__) */
