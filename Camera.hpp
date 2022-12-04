#pragma once

#include "BasicTypes.hpp"

namespace engine
{
    /**
    * @brief Camera class.
    */
    class Camera
    {
    public:
        /**
        * @brief Camera constructor.
        */
        Camera();

        /**
        * @brief Camera destructor.
        */
        ~Camera() = default;

        /**
        * @brief Move camera position
        * @param position Position which camera has to move.
        */
        void move(Position position);

        /**
        * @brief Move camera according to camera direction.
        * @param position Position which camera has to move.
        */
        void moveAccordingToDirection(Position position);

        /**
        * @brief Set camera position.
        * @param position Position of the camera.
        */
        void setPosition(Position position);

        /**
        * @brief Get camera position.
        * @return Position of the camera.
        */
        Position getPosition() const;

        /**
        * @brief Set camera target position.
        * @param position Position of the camera target.
        */
        void setTarget(Position);

        /**
        * @brief Rotate camera direction.
        * @param yaw Yaw angle.
        * @param pitch Pitch angle.
        */
        void rotate(Angle yaw, Angle pitch);

        /**
        * @brief Get view matrix.
        * @return View matrix.
        */
        Matrix getViewMatrix();

        /**
        * @brief Get view position.
        * @return View position.
        */
        const Position& getViewPosition() const;

    protected:
        /**
        * @brief Update center according to the angles and camera position.
        */
        void updateCenter();

        /**
        * @brief Update angles according to the center and camera position.
        */
        void updateAngles();

        /**
        * @brief Position of the camera eye.
        */
        Position eye;

        /**
        * @brief Position of the camera target.
        */
        Position center;
        
        /**
        * @brief Coordination system of the world.
        */
        Position up;

        /**
        * @brief Yaw angle.
        */
        Angle yaw;

        /**
        * @brief Pitch angle.
        */
        Angle pitch;
    };
}