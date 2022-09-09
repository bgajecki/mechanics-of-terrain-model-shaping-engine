#pragma once

#include <vector>

#include "BasicTypes.hpp"

namespace Engine
{
    class Mesh
    {
    public:
        Mesh();
        ~Mesh();

        /**
        * 
        */
        Mesh(const std::vector<Vertex>&, const std::vector<unsigned int>&, const std::vector<Texture>&);

        /**
        * Draw mesh
        */
        void Draw();



        /**
        *
        */
        

    private:

        virtual void setupBuffers();

        std::vector<Vertex> vertices;
        std::vector<unsigned int> indices;
        std::vector<TextureType> textures;

        GLuint vbo, ebo;
    };

}