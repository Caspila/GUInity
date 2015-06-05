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

	/** Prototype design pattern*/
	virtual shared_ptr<Component> clone() override;


	/** Serialization region*/
	/** Get a description for the current component*/
    virtual shared_ptr<ComponentDescription> getComponentDescription();
	/** Deserialize a description into this instance*/
	virtual void deserialize(shared_ptr<ComponentDescription> desc);

};

