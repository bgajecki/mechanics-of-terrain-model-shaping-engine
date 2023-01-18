#pragma once

#include "BasicTypes.hpp"

namespace engine
{
    /**
    * @brief Voxel class.
    */
    class Voxel final
    {
    public:
        /**
        * @brief Voxel constructor.
        */
        Voxel();
        
        /**
        * @brief Voxel destructor.
        */
        ~Voxel() = default;

        /**
        * @brief Set type of the voxel.
        * @param type Type of the voxel.
        */
        void setType(unsigned type);

        /**
        * @brief Get type of the voxel.
        * @return Type of the voxel.
        */
        unsigned getType() const;
        
        /**
        * @brief Set voxel in active state.
        * @param active State of voxel.
        */
        void setActive(bool active);

        /**
        * @brief Is voxel in active state.
        * @return State of the voxel.
        */
        bool isActive() const;

        /**
        * @brief Set lifespan of the voxel.
        * @param Lifespan of the voxel.
        */
        void setLifespan(float lifespan);

        /**
        * @brief Get lifespan of the voxel.
        * @return Lifespan of the voxel.
        */
        float getLifespan() const;

        /**
        * @brief Decrease lifespan of the voxel.
        * @param How much decrase voxel lifespan.
        */
        void decreaseLifespan(float);


    private:
        /**
        * @brief Voxel type.
        */
        unsigned type;
        /**
        * @brief State of the voxel.
        */
        bool active;
        /**
        * @brief Lifespan of the voxel.
        */
        Lifespan lifespan;
    };
}