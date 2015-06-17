#include "GraphicsSystem.hpp"
#include "Mesh.hpp"
#include "MeshRenderer.hpp"
#include "MeshFilter.hpp"
#include "Actor.hpp"
#include "Camera.hpp"
#include "Light.hpp"
#include "Material.hpp"
#include "Shader.hpp"

#include "GLFWGraphicsSystem.hpp"

GraphicsSystem* GraphicsSystem::getInstance()
{
    static GraphicsSystem* instance; // Guaranteed to be destroyed.
    if(instance == nullptr)
        instance = new GLFWGraphicsSystem();

    // Instantiated on first use.
    return instance;
}


GraphicsSystem::~GraphicsSystem()
{
}
