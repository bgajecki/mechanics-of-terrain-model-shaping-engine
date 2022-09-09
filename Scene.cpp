#include "Scene.hpp"

namespace Engine
{
    Scene::Scene()
    {
        glGenVertexArrays(1, &this->vertexArrayObject);
    }

    Scene::~Scene()
    {
        glDeleteVertexArrays(1, &this->vertexArrayObject);
    }
}