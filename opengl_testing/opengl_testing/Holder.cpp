#include "Holder.hpp"



Holder::Holder()
{
}
Holder::Holder(ShaderParamType type, float val)
{
	this->type_ = type;
	impl_.float_ = val;
}
Holder::Holder(ShaderParamType type, glm::vec3 val)
{
	this->type_ = type;
	impl_.vec3_ = val;
}