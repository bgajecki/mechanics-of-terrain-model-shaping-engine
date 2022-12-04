#pragma once

#include <memory>
#include "implementation/Object/Object.hpp"
#include "BasicTypes.hpp"
#include "Camera.hpp"
#include "SceneManager.hpp"

namespace engine
{
    /**
    * @brief Class representing scene. Has objects to draw.
    */
    class Scene : public implementation::Scene
    {
        /**
        * @brief Unique pointer to the object.
        */
        using ObjectPointer = std::unique_ptr<implementation::Object>;

        /**
        * @brief Vector of unique pointers to the objects.
        */
        using ObjectVector = std::vector<ObjectPointer>;

    public:

        /**
        * @brief Scene need scene manager reference.
        */
        Scene() = delete;

        /**
        * @brief Scene constructor.
        * @param sceneManager Reference to the scene manager.
        */
        Scene(SceneManager& sceneManager);

        /**
        * @brief Scene destructor.
        */
        ~Scene() = default;

        /**
        * @brief Create a new object.
        * @tparam T Type of the object.
        * @tparam RestOfParameters Types of the rest of parameters.
        * @param restOfParameters Rest of parameters passed to the object constructor.
        * @return Pointer to the created object.
        */
        template<typename T, typename... RestOfParameters>
        T* createObject(RestOfParameters... restOfParameters)
        {
            this->objects.push_back(std::make_unique<T>(restOfParameters...));
            return dynamic_cast<T*>(this->objects.back().get());
        }
        
        /**
        * @brief Drawing objects assigned to the scene and passed program by parameter.
        * @param program Program of shaders.
        */
        virtual void draw(const Program& program);

    protected:
        /**
        * @brief Scene camera.
        */
        Camera camera;

        /**
        * @brief Projection matrix.
        */
        Matrix projection;

        /**
        * @brief View matrix.
        */
        Matrix view;

        /**
        * @brief Model matrix.
        */
        Matrix model;

        /**
        * @brief Container of the pointers to the objects.
        */
        ObjectVector objects;

        /**
        * @brief Reference to the scene manager.
        */
        SceneManager& sceneManager;
    };

}