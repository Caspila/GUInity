#pragma once

#include "Module.hpp"
#include <glm/glm.hpp>

#ifndef __HOLDER__
#define __HOLDER__

class Texture;

enum ShaderParamType {
	VEC3,
	FLOAT,
	TEXTURE
	// Other types you want to store into vector.
};

class Holder {
public:


	//template<typename T>
	//Holder(ShaderParamType type, T val);

	Holder();
	Holder(ShaderParamType type, float val);
	Holder(ShaderParamType type, glm::vec3 val);
	Holder(ShaderParamType type, shared_ptr<Texture> val);
	~Holder() {
		// You want to properly destroy
		// union members below that have non-trivial constructors
	}

	bool isFloat()
	{
		return type_ == FLOAT;
	}
	bool isVec3()
	{
		return type_ == VEC3;
	}
	bool isTexture()
	{
		return type_ == TEXTURE;
	}

	operator float() const {
		if (type_ != FLOAT) {
			//throw SomeException();
		}
		return floatValue;
		//return impl_.float_;
	}
	operator glm::vec3() const {
		if (type_ != VEC3) {
			//throw SomeException();
		}
		//return impl_.vec3_;
		return vec3Value;
	}
	operator weak_ptr<Texture>() const {
		if (type_ != TEXTURE) {
			//throw SomeException();
		}
		//return impl_.vec3_;
		return texValue;
	}


	// Do the same for other operators
	// Or maybe use templates?

	//TODO CREATE UNION THAT USES ONLY ONE TYPE
private:
	//union Impl {
	//	float float_;
	//	struct{
	//		glm::vec3 vec3_;
	//	};


	//	Impl() { new(&vec3_) glm::vec3; }
	//} impl_;

	float floatValue;
	glm::vec3 vec3Value;
	weak_ptr<Texture> texValue;

	ShaderParamType type_;

	// Other stuff.
};

#endif