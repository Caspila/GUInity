#pragma once

#include "Module.hpp"
#include <glm/glm.hpp>

#ifndef __HOLDER__
#define __HOLDER__

enum ShaderParamType {
	VEC3,
	FLOAT,
	// Other types you want to store into vector.
};

class Holder {
public:


	//template<typename T>
	//Holder(ShaderParamType type, T val);

	Holder();
	Holder(ShaderParamType type, float val);
	Holder(ShaderParamType type, glm::vec3 val);
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
	operator float() const {
		if (type_ != FLOAT) {
			//throw SomeException();
		}
		return impl_.float_;
	}
	operator glm::vec3() const {
		if (type_ != VEC3) {
			//throw SomeException();
		}
		return impl_.vec3_;
	}


	// Do the same for other operators
	// Or maybe use templates?

private:
	union Impl {
		float float_;
		struct{
			glm::vec3 vec3_;
		};


		Impl() { new(&vec3_) glm::vec3; }
	} impl_;

	ShaderParamType type_;

	// Other stuff.
};

#endif