#pragma once

#include "Subject.hpp"
#include "Component.hpp"

/** Light Component. This component adds Light behaviour to a game actor. For now the Light component behaves like point light and is very very basic 
	There are no shadows currently.
*/

class Light : public Component, public Subject<Light>
#ifdef GUINITY_DEBUG
	, public StaticCounter<Light>
#endif
{
private:
	/** The color of the light */
	glm::vec3 color;

public:
	
	/** Default Constructor. White Light */
	Light();
	/** Default Constructor. Colored Light */
	Light(glm::vec3 color);
	/** Default Destructor */
	~Light();

	/** color setter*/
	glm::vec3 getColor();
	/** color setter*/
	void setColor(glm::vec3);


	/** Component init override. Notifies that a new light has been created*/
	virtual void init() override;
    /** Component destroy override. Notifies that this light has been destroyed*/
   	virtual void destroy() override;
    
    /** Clones current component (Prototype Design Pattern)
     @return shared_ptr to cloned Light Component
     */
	virtual shared_ptr<Component> clone() override;


    /** @defgroup serialization_functions Serialization Functions
     *  Serialization Region
     *  @{
     */
#pragma region Serialization Functions
    
	/** Creates a description for the Component*/
	virtual shared_ptr<ComponentDescription> getComponentDescription() override;
    /** Deserializes a description to a Component */
    virtual void deserialize(shared_ptr<ComponentDescription> desc) override;
    
#pragma endregion
    /** @} */ // end of serialization_functions

};

