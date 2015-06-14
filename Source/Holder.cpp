#include "Holder.hpp"




/** Constructor for a float
 @param[in] type The type of this container
 @param[in] val The float value
 */Holder::Holder(ShaderParamType type,float val)
{
	this->type = type;
	floatValue = val;
}
/** Constructor for a vec4
 @param[in] type The type of this container
 @param[in] val The vec4 value
 */
Holder::Holder(ShaderParamType type,const glm::vec4& val)
{
	this->type = type;
	vec4Value = glm::vec4(val);

}
/** Constructor for a vec2
 @param[in] type The type of this container
 @param[in] val The vec2 value
 */
Holder::Holder(ShaderParamType type,const glm::vec2& val)
{
	this->type = type;
	vec2Value = glm::vec2(val);
}

/** Constructor for a Texture
 @param[in] type The type of this container
 @param[in] val The Texture value
 */
Holder::Holder(ShaderParamType type,shared_ptr<Texture> val)
{
	this->type = type;
	texValue = val;
}

/** returns true if it is a float value
 @return true if this contains a float value
 */
bool Holder::isFloat() const
{
	return this->type == FLOAT;
}
/** returns true if it is a vec4 value
 @return true if this contains a vec4 value
 */
bool Holder::isVec4() const
{
	return this->type == VEC4;
}
/** returns true if it is a vec2 value
 @return true if this contains a vec2 value
 */
bool Holder::isVec2() const
{
	return this->type == VEC2;
}

/** returns true if it is a Texture value
 @return true if this contains a Texture value
 */
bool Holder::isTexture() const
{
	return this->type == TEXTURE;
}

/** returns the float value
 @return The float value*/
float Holder::getFloat() const {
	if (this->type != FLOAT) {
		//throw SomeException();
		cerr << "Trying to convert type to float but it is not" << endl;
	}
	return floatValue;
}
/** returns the vec4 value
 @return The vec4 value*/
glm::vec4 Holder::getVec4() const {
	if (this->type != VEC4) {
		//throw SomeException();
		cerr << "Trying to convert type to vec4 but it is not" << endl;
	}
	return vec4Value;
}

/** returns the vec4 value
 @return The vec4 value*/
glm::vec2 Holder::getVec2() const {
	if (this->type != VEC2) {
		//throw SomeException();
		cerr << "Trying to convert type to vec2 but it is not" << endl;
	}
	return vec2Value;
}
/** returns the Texture value
 @return The Texture value*/
shared_ptr<Texture> Holder::getTexture() const {
	if (this->type != TEXTURE) {
		//throw SomeException();
		cerr << "Trying to convert type to texture but it is not" << endl;
	}
	return texValue.lock();
}