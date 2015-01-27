#include "Holder.hpp"



Holder::Holder()
{
}
Holder::Holder(ShaderParamType type, float val)
{
	this->type_ = type;
	floatValue = val;
}
Holder::Holder(ShaderParamType type, glm::vec3 val)
{
	this->type_ = type;
	vec3Value = val;

}

Holder::Holder(ShaderParamType type, shared_ptr<Texture> val)
{
	this->type_ = type;
	texValue = val;
}