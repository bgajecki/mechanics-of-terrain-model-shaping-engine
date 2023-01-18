#include "Scene.hpp"

namespace engine
{
    Scene::Scene(SceneManager& sceneManager)
        : sceneManager(sceneManager), projection(1), view(1), model(1), camera()
    {
    }

    void Scene::draw(const Program& program)
    {
        for (auto& object : this->objects)
        {
            if (object->getProgram() == program)
            {
                this->model = object->getModelMatrix();
                //object->callPreDrawSettings();
                program->loadUniforms();
                object->draw();
                //object->callPostDrawSettings();
            }
        }
    }
  
}