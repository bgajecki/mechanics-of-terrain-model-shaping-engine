#pragma once

#include <memory>
#include "implementation/Object/Object.hpp"
#include "BasicTypes.hpp"
#include "SceneManager.hpp"

namespace engine
{
    class Scene : public implementation::Scene
    {
        /**
        * @brief Unique pointer to mesh object.
        */
        using MeshPointer = std::unique_ptr<implementation::Object>;

        /**
        * @brief Vector of unique pointers to meshes objects.
        */
        using MeshVector = std::vector<MeshPointer>;
    public:
        /**
        * Draw mesh
        */
        Scene(SceneManager&);

        ~Scene() = default;

        /**
        * Draw mesh
        */
        template<typename T, typename... RestOfParameters>
        T* createObject(RestOfParameters... restOfParameters)
        {
            this->meshes.push_back(std::make_unique<T>(restOfParameters...));
            return dynamic_cast<T*>(this->meshes.back().get());
        }
        
        /**
        * Draw mesh
        */
        virtual void draw(const Program& program);

    protected:

        void updateMvpMatrix();

        /**
        * Draw mesh
        */
        Camera camera;

        /**
        * Draw mesh
        */
        Matrix projection;

        /**
        * Draw mesh
        */
        Matrix view;

        /**
        * Draw mesh
        */
        Matrix model;

        /**
        * Draw mesh
        */
        Matrix mvp;

        /**
        * Draw mesh
        */
        MeshVector meshes;

        /**
        * Draw mesh
        */
        SceneManager& sceneManager;
    };

}