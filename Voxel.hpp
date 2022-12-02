#pragma once

#include "BasicTypes.hpp"

namespace engine
{
    class Voxel final
    {
    public:
        /**
        * @brief Unique pointer to scene object.
        */
        Voxel();
        
        /**
        * @brief Unique pointer to scene object.
        */
        ~Voxel() = default;

        /**
        * @brief Unique pointer to scene object.
        */
        void setType(unsigned);

        /**
        * @brief Unique pointer to scene object.
        */
        unsigned getType() const;
        
        /**
        * @brief A shader manager class that manages shaders in the stage.
        */
        void setActive(bool);

        /**
        * @brief Unique pointer to scene object.
        */
        bool isActive() const;

        /**
        * @brief A shader manager class that manages shaders in the stage.
        */
        void setLifespan(float);

        /**
        * @brief A shader manager class that manages shaders in the stage.
        */
        float getLifespan() const;

        /**
        * @brief A shader manager class that manages shaders in the stage.
        */
        void decreaseLifespan(float);


    private:
        /**
        * @brief Unique pointer to scene object.
        */
        unsigned type;
        /**
        * @brief Unique pointer to scene object.
        */
        bool active;
        /**
        * @brief Unique pointer to scene object.
        */
        Lifespan lifespan;
    };
}