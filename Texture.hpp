#pragma once

#include <glm/glm.hpp> 
#include <GL/glew.h> 
#include <iostream>
#define STB_IMAGE_IMPLEMENTATION
#include <stb_image.h>

namespace engine
{
    class Texture
    {
        /**
        * @brief A shader manager class that manages shaders in the stage.
        */
        using TextureId = GLuint;
    public:
        /**
        * @brief A shader manager class that manages shaders in the stage.
        */
        Texture();

        /**
        * @brief A shader manager class that manages shaders in the stage.
        */
        Texture(const std::string&);

        /**
        * Shader can't be copied, because it's creating problem with assignment.
        */
        Texture(const Texture&) = delete;

        /**
        * Swaping shader IDs.
        */
        Texture(Texture&&) noexcept;

        /**
        * @brief A shader manager class that manages shaders in the stage.
        */
        ~Texture();

        /**
        * @brief A shader manager class that manages shaders in the stage.
        */
        void bind(int);

        /**
        * @brief A shader manager class that manages shaders in the stage.
        */
        void load(const std::string&);
        
    protected:
        /**
        * @brief A shader manager class that manages shaders in the stage.
        */
        TextureId id;
    };

    class TextureReference
    {
    public:
        /**
        * @brief A shader manager class that manages shaders in the stage.
        */
        TextureReference() = delete;

        /**
        * @brief A shader manager class that manages shaders in the stage.
        */
        TextureReference(Texture&);

        /**
        * @brief A shader manager class that manages shaders in the stage.
        */
        ~TextureReference() = default;

        /**
        * @brief A shader manager class that manages shaders in the stage.
        */
        void bind(int);

    protected:
        Texture& texture;
    };



}