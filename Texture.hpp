#pragma once

#include <glm/glm.hpp> 
#include <GL/glew.h> 
#include <iostream>
#define STB_IMAGE_IMPLEMENTATION
#include <stb_image.h>

namespace engine
{
    /**
    * @brief Texture class.
    */
    class Texture final
    {
        /**
        * @brief Texture ID type.
        */
        using TextureId = GLuint;
    public:
        /**
        * @brief Texture constructor.
        */
        Texture();

        /**
        * @brief Texture constructor.
        * @param path Path to the texture location
        */
        Texture(const std::string& path);

        /**
        * @brief Textire can't be copied, because it's creating problem with assignment.
        */
        Texture(const Texture&) = delete;

        /**
        * @brief Swaping texture IDs.
        */
        Texture(Texture&&) noexcept;

        /**
        * @brief Texture destructor.
        */
        ~Texture();

        /**
        * @brief Bind texture.
        * @param index Index.
        */
        void bind(int index);

        /**
        * @brief Load texture.
        * @param path Path to the texture location
        */
        void load(const std::string& path);
        
    private:
        /**
        * @brief Texture ID.
        */
        TextureId id;
    };

    /**
    * @brief TextureReference class. Used to not copy textures.
    */
    class TextureReference final
    {
    public:
        /**
        * @brief TextureReference constructor.
        */
        TextureReference() = delete;

        /**
        * @brief TextureReference constructor.
        * @param texture Reference to the texture object.
        */
        TextureReference(Texture& texture);

        /**
        * @brief TextureReference destructor.
        */
        ~TextureReference() = default;

        /**
        * @brief Bind texture.
        * @param index Index.
        */
        void bind(int);

    private:
        /**
        * @brief Texture reference.
        */
        Texture& texture;
    };



}