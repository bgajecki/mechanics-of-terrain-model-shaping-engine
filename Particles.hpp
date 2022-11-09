#pragma once

#include <vector>
#include <list>

#include "implementation/Object/Object.hpp"
#include "BasicTypes.hpp"
#include "Texture.hpp"
#include "Program.hpp"

namespace engine
{
    class Particles : public implementation::Object
    {
    public:
        /**
        *
        */
        Particles();

        /**
        *
        */
        ~Particles();

        /**
        * Draw mesh
        */
        virtual void draw() override;

        /**
        * Draw mesh
        */
        std::vector<Particle> particles;



    protected:

        /**
        * Draw mesh
        */
        virtual bool setupBuffers();


        /**
        * Draw mesh
        */
        GLuint vertexArrayObject;

        /**
        * Draw mesh
        */
        GLuint vertexBufferObject;

        /**
        * Draw mesh
        */
        //GLuint elementBufferObject;

        /**
        * Draw mesh
        */
        std::vector<Position> vertices;

    };

}