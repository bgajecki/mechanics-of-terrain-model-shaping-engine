#pragma once

#include <vector>

#include "implementation/Object/Object.hpp"
#include "BasicTypes.hpp"
#include "Texture.hpp"
#include "Program.hpp"

namespace engine
{
    /**
    *
    */
    using MeshVertex = Vertex<TextureCoordinate>;

    class Mesh : public implementation::Object
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
        Mesh(const std::vector<MeshVertex>&, const std::vector<unsigned int>&);

        /**
        * Draw mesh
        */
        virtual void draw() override;

        /**
        * Draw mesh
        */
        bool loadObj(const std::string&);

        /**
        * Draw mesh
        */
        std::vector<MeshVertex> vertices;
        
        /**
        * Draw mesh
        */
        std::vector<Index> indices;

        /**
        * Draw mesh
        */
        std::vector<TextureReference> textures;

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
        GLuint elementBufferObject;

    };

}