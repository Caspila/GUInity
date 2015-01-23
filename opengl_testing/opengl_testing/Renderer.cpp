#include "Renderer.hpp"


Renderer::Renderer()
{
}


Renderer::~Renderer()
{
}


void Renderer::setMaterial(shared_ptr<Material> material)
{
	this->material = material;
}
