#pragma once

#include <vector>
#include "implementation/Object/Object.hpp"
#include <glm/gtc/matrix_transform.hpp>
#include "BasicTypes.hpp"
#include "Voxel.hpp"

namespace engine
{
    class Chunk : public implementation::Object
    {
        using VoxelVector = std::vector<std::vector<std::vector<Voxel>>>;
        using VertexVector = std::vector<VertexColor>;
        using IndexVector = std::vector<Index>;
    public:

        Chunk();
        ~Chunk();
        
        virtual void update(float);
        virtual void draw() override;
        void refresh();
        void resize(size_t);
        unsigned chunkSize;
        float renderSize;
        Position position;
    protected:

        void generateVertices(const Position&, const Color&);
        void addVoxelFace(const Position&, const Position&, const Position&, const Position&, const Normal&, const Color&);
        VertexVector vertices;
        VoxelVector voxels;
        IndexVector indices;

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