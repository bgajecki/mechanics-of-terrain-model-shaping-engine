#include "Scene.hpp"
#include "Scene.hpp"

namespace engine
{
    Scene::Scene(SceneManager& sceneManager)
        : sceneManager(sceneManager), projection(1), view(1), model(1), camera({ { 0,0,0 }, { 0,0,0 }, { 0,0,0 } })
    {
    }

    void Scene::draw(const Program& program)
    {
        for (auto& mesh : this->meshes)
            if (mesh->program == program)
                mesh->draw();
    }
    
    void Scene::updateMvpMatrix()
    {
        this->mvp = this->projection * this->view * this->model;
    }
}