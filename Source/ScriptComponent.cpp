#include "ScriptComponent.hpp"

    /** Default Constructor */
ScriptComponent::ScriptComponent()
{
#ifdef GUINITY_DEBUG
	nCount++;
#endif
}

    /** Default Destructor */
ScriptComponent::~ScriptComponent()
{
#ifdef GUINITY_DEBUG
	nCount--;
	cout << " <- Base ScriptComponent destroyed (" << nCount << " remaining)" << endl;
#endif
}


/** Clones current component (Prototype Design Pattern)
 @return shared_ptr to cloned ScriptComponent Component
 */
shared_ptr<Component> ScriptComponent::clone()
{
    shared_ptr<ScriptComponent> compClone = make_shared<ScriptComponent>();

    return compClone;
}
