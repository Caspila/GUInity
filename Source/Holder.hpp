#pragma once

#include "Module.hpp"
#include <glm/glm.hpp>

#ifndef __HOLDER__
#define __HOLDER__

#include "Enums.hpp"

class Texture;

/** Holder is a class that can hold multiple values. It's used by Materials and Shaders because
each shader can contain several input parameters such as float values and Textures. */
class Holder {

	// Right now it's REALLY not optmizied because every instance of Holder holds all the
	// possible types
	// TODO CREATE UNION THAT USES ONLY ONE TYPE
	// http://www.informit.com/guides/content.aspx?g=cplusplus&seqNum=556

private:
	/** The float value*/
	float floatValue;
	/** The vec3 value*/
	glm::vec3 vec3Value;
	/** The Texture pointer value*/
	weak_ptr<Texture> texValue;

	/** The type of the instance*/
	ShaderParamType type;
public:

	Holder() {};
	/** The explicit is very important here because we don't want any implicit conversions among types*/
	/** Constructor for a float*/
	explicit Holder(ShaderParamType type, float val);
	/** Constructor for a vec3*/
	explicit Holder(ShaderParamType type,glm::vec3 val);
	/** Constructor for a Texture*/
	explicit Holder(ShaderParamType type,shared_ptr<Texture> val);
	~Holder() {
		// Destroy members that have non-trivial constructors
	}

	/** returns true if it is a float value */
	bool isFloat() const;
	/** returns true if it is a vec3 value */
	bool isVec3() const;
	/** returns true if it is a Texture value */
	bool isTexture() const;
	/** returns the float value */
	operator float() const;
	/** returns the vec3 value */
	operator glm::vec3() const;
	/** returns the Texture value */
	operator weak_ptr<Texture>() const;

	

};

#endif