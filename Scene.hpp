#pragma once

#include "Mesh.hpp"

namespace Engine
{
    class Scene
    {
    public:
        Scene();
        ~Scene();

        

    private:

        void setupArray()

        std::vector<Mesh> meshes;

        GLuint vertexArrayObject;
    };

}