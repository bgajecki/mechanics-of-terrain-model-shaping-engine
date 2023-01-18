#pragma once

#include <vector>
#include <list>

#include "implementation/Object/Object.hpp"
#include "BasicTypes.hpp"
#include "Texture.hpp"
#include "Program.hpp"

namespace engine
{
    /**
    * @brief Protype particles class representing effects.
    */
    class Particles : public implementation::Object
    {
        /**
        * @brief Vector of particles.
        */
        using ParticleVector = std::vector<Particle>;

        /**
        * @brief Vector of vertices.
        */
        using VertexVector = std::vector<Position>;

    public:
        /**
        * @brief Particles constructor.
        */
        Particles();

        /**
        * @brief Particles destructor.
        */
        virtual ~Particles();

        /**
        * @brief Drawing primitives.
        */
        virtual void draw() override;

        /**
        * @brief Particles container.
        */
        ParticleVector particles;

    protected:

        /**
        * @brief Setup buffers
        */
        virtual bool setupBuffers();

        /**
        * @brief Vertex array object.
        */
        GLuint vertexArrayObject;

        /**
        * @brief Vertex buffer object.
        */
        GLuint vertexBufferObject;

        ///**
        //* @brief Element buffer object.
        //*/
        //GLuint elementBufferObject;

        /**
        * @brief Vertices container.
        */
        VertexVector vertices;

    };

}