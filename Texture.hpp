#pragma once

#include <glm/glm.hpp> 
#include <GL/glew.h> 

namespace engine
{
    class Texture
    {
        using TextureId = GLuint;
    public:

    protected:
        TextureId id;
    };

}