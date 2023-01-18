#pragma once

#include <vector>

#include "implementation/Object/Object.hpp"
#include "BasicTypes.hpp"
#include "Texture.hpp"
#include "Program.hpp"

namespace engine
{
    /**
    * @brief Vertex specified for mesh. Attribute texture coordinates.
    */
    using MeshVertex = Vertex<TextureCoordinate>;

    /**
    * @brief Protype mesh class.
    */
    class Mesh : public implementation::Object
    {
        /**
        * @brief Vector of vertices.
        */
        using VertexVector = std::vector<MeshVertex>;

        /**
        * @brief Vector of indicies.
        */
        using IndexVector = std::vector<Index>;

        /**
        * @brief Texture reference vector.
        */
        using TextureVector = std::vector<TextureReference>;
    public:
        /**
        * @brief Mesh constructor
        */
        Mesh();

        /**
        * @brief Mesh destructor
        */
        virtual ~Mesh();

        /**
        * @brief Drawing primitives.
        */
        virtual void draw() override;

        /**
        * @brief Load OBJ file.
        * @param path Path to the file location.
        */
        bool loadObj(const std::string& path);

        /**
        * @brief Vertices container.
        */
        VertexVector vertices;
        
        /**
        * @brief Indices container.
        */
        IndexVector indices;

        /**
        * @brief Textures references container.
        */
        TextureVector textures;

    protected:

        /**
        * @brief Setup textures.
        */
        virtual void setupTextures();

        /**
        * @brief Setup buffers.
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

        /**
        * @brief Element buffer object.
        */
        GLuint elementBufferObject;

    };

}