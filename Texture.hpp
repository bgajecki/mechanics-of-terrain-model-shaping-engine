#pragma once

#include <glm/glm.hpp> 
#include <GL/glew.h> 
#include <iostream>
#define STB_IMAGE_IMPLEMENTATION
#include <stb_image.h>

namespace engine
{
    using TextureId = GLuint;
    class Texture
    {
        
    public:
        Texture();
        ~Texture();

        void bind(int);

        void load(const std::string&);
        TextureId id;
    protected:
        
    };

}