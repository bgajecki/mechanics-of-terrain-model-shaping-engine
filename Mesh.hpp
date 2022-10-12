#pragma once

#include <vector>

#include "BasicTypes.hpp"
#include "Texture.hpp"
#include "Program.hpp"

namespace engine
{
    class Mesh
    {
    public:
        /**
        *
        */
        Mesh();

        /**
        *
        */
        ~Mesh();

        /**
        * 
        */
        Mesh(const std::vector<Vertex>&, const std::vector<unsigned int>&, const std::vector<Texture>&);

        /**
        * Draw mesh
        */
        virtual void draw();

        /**
        * Draw mesh
        */
        std::vector<Vertex> vertices;
        /**
        * Draw mesh
        */
        std::vector<unsigned int> indices;

        /**
        * Draw mesh
        */
        std::vector<Texture> textures;

        /**
        * Draw mesh
        */
        Program program;

    protected:

        /**
        * Draw mesh
        */
        virtual bool setupBuffers();

        /**
        * Draw mesh
        */
        virtual bool inline checkData();

        /**
        * Draw mesh
        */
        virtual void inline resetDataProtection();

        /**
        * Draw mesh
        */
        bool areBuffersSetup;


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
        GLuint elementBufferObject;

        /**
        * Draw mesh
        */
        size_t verticesSize;

        /**
        * Draw mesh
        */
        size_t indicesSize;

        /**
        * Draw mesh
        */
        size_t texturesSize;
    };

}