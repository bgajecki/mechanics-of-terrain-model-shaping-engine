#pragma once

#include <memory>
#include "implementation/Object/Object.hpp"
#include "BasicTypes.hpp"
#include "Camera.hpp"
#include "SceneManager.hpp"

namespace engine
{
    class Scene : public implementation::Scene
    {
        /**
        * @brief Unique pointer to mesh object.
        */
        using ObjectPointer = std::unique_ptr<implementation::Object>;

        /**
        * @brief Vector of unique pointers to meshes objects.
        */
        using ObjectVector = std::vector<ObjectPointer>;
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
            this->objects.push_back(std::make_unique<T>(restOfParameters...));
            return dynamic_cast<T*>(this->objects.back().get());
        }
        
        /**
        * Draw mesh
        */
        virtual void draw(const Program& program);

    protected:
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
        ObjectVector objects;

        /**
        * Draw mesh
        */
        SceneManager& sceneManager;
    };

}