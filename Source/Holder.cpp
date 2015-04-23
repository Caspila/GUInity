#include "Holder.hpp"




/** Constructor for a float*/
Holder::Holder(ShaderParamType type,float val)
{
	this->type = type;
	floatValue = val;
}
/** Constructor for a vec4*/
Holder::Holder(ShaderParamType type,const glm::vec4& val)
{
	this->type = type;
	vec4Value = glm::vec4(val);

}

/** Constructor for a Texture*/
Holder::Holder(ShaderParamType type,shared_ptr<Texture> val)
{
	this->type = type;
	texValue = val;
}

/** returns true if it is a float value */
bool Holder::isFloat() const
{
	return this->type == FLOAT;
}
/** returns true if it is a vec3 value */
bool Holder::isVec4() const
{
	return this->type == VEC4;
}
/** returns true if it is a Texture value */
bool Holder::isTexture() const
{
	return this->type == TEXTURE;
}

/** returns the float value */
float Holder::getFloat() const {
	if (this->type != FLOAT) {
		//throw SomeException();
		cerr << "Trying to convert type to float but it is not" << endl;
	}
	return floatValue;
}
/** returns the vec3 value */
glm::vec4 Holder::getVec4() const {
	if (this->type != VEC4) {
		//throw SomeException();
		cerr << "Trying to convert type to vec4 but it is not" << endl;
	}
	return vec4Value;
}
/** returns the Texture value */
shared_ptr<Texture> Holder::getTexture() const {
	if (this->type != TEXTURE) {
		//throw SomeException();
		cerr << "Trying to convert type to texture but it is not" << endl;
	}
	return texValue.lock();
}