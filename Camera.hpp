#pragma once

#include "BasicTypes.hpp"

namespace engine
{
    class Camera
    {
    public:
        /**
        * @brief Unique pointer to scene object.
        */
        Camera();

        ~Camera() = default;

        /**
        * @brief Unique pointer to scene object.
        */
        void move(Position);

        /**
        * @brief Unique pointer to scene object.
        */
        void moveAccordingToDirection(Position);

        /**
        * @brief Unique pointer to scene object.
        */
        void setPosition(Position);

        /**
        * @brief Unique pointer to scene object.
        */
        void setTarget(Position);

        /**
        * @brief Unique pointer to scene object.
        */
        Position getPosition() const;

        /**
        * @brief Unique pointer to scene object.
        */
        void rotate(Angle, Angle);

        /**
        * @brief Unique pointer to scene object.
        */
        Matrix getViewMatrix();
        /**
        * @brief Unique pointer to scene object.
        */
        const Position& getViewPosition() const;

    protected:
        /**
        * @brief Unique pointer to scene object.
        */
        void updateCenter();
        /**
        * @brief Unique pointer to scene object.
        */
        void updateAngle();
        /**
        * @brief Unique pointer to scene object.
        */
        Position eye;

        /**
        * @brief Unique pointer to scene object.
        */
        Position center;
        
        /**
        * @brief Unique pointer to scene object.
        */
        Position up;

        /**
        * @brief Unique pointer to scene object.
        */
        Angle yaw;

        /**
        * @brief Unique pointer to scene object.
        */
        Angle pitch;
    };
}