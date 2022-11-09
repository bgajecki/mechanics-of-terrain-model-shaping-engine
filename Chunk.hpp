#pragma once

#include <vector>
#include "implementation/Object/Object.hpp"
#include <glm/gtc/matrix_transform.hpp>
#include "BasicTypes.hpp"

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
        void createCube(const Position);
        virtual void draw() override;
        static const unsigned CHUNK_SIZE = 16;
        float RENDER_SIZE;
        Color color;
    private:
        void generateVertices(const Position&);
        void addCubeFace(const glm::vec3&, const glm::vec3&, const glm::vec3&, const glm::vec3&, const glm::vec3&);
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
        
        Position position;

    };
}