#include "Chunk.hpp"

namespace engine
{
    Chunk::Chunk()
        : areBuffersSetup(false), verticesSize(0u), indicesSize(0u), RENDER_SIZE(.01f), color({0.0f, 0.0f, 1.0f, 1.0f})
    {
        glGenVertexArrays(1, &this->vertexArrayObject);
        glGenBuffers(1, &this->vertexBufferObject);
        glGenBuffers(1, &this->elementBufferObject);
        this->voxels.resize(this->CHUNK_SIZE);
        for (auto& i : this->voxels)
        {
            i.resize(this->CHUNK_SIZE);
            for (auto& j : i)
            {
                j.resize(this->CHUNK_SIZE);
                for (unsigned k = 0; k < this->CHUNK_SIZE; k++)
                        j[k] = true;

            }

        }
    }

    Chunk::~Chunk()
    {
        glDeleteBuffers(1, &this->vertexBufferObject);
        glDeleteBuffers(1, &this->elementBufferObject);
        glDeleteVertexArrays(1, &this->vertexArrayObject);
        this->voxels.clear();
    }

    void Chunk::createCube(const Position pos)
    {
        this->position = pos;

        Voxel voxel;
        Position position;
        for (size_t x = 0; x < this->CHUNK_SIZE; x++)
        {
            for (size_t y = 0; y < this->CHUNK_SIZE; y++)
            {
                for (size_t z = 0; z < this->CHUNK_SIZE; z++)
                {
                    voxel = this->voxels[x][y][z];
                    if (voxel)
                    {
                        position = this->position + Position(static_cast<float>(x) * this->RENDER_SIZE,
                            static_cast<float>(y) * this->RENDER_SIZE,
                            static_cast<float>(z) * this->RENDER_SIZE);
                        this->generateVertices(position);
                    }
                }
            }
        }
    }

    void Chunk::generateVertices(const Position& position)
    {
        float x = position.x, y = position.y, z = position.z;
        glm::vec3 v1(x - this->RENDER_SIZE, y - this->RENDER_SIZE, z + this->RENDER_SIZE);
        glm::vec3 v2(x + this->RENDER_SIZE, y - this->RENDER_SIZE, z + this->RENDER_SIZE);
        glm::vec3 v3(x + this->RENDER_SIZE, y + this->RENDER_SIZE, z + this->RENDER_SIZE);
        glm::vec3 v4(x - this->RENDER_SIZE, y + this->RENDER_SIZE, z + this->RENDER_SIZE);
        glm::vec3 v5(x + this->RENDER_SIZE, y - this->RENDER_SIZE, z - this->RENDER_SIZE);
        glm::vec3 v6(x - this->RENDER_SIZE, y - this->RENDER_SIZE, z - this->RENDER_SIZE);
        glm::vec3 v7(x - this->RENDER_SIZE, y + this->RENDER_SIZE, z - this->RENDER_SIZE);
        glm::vec3 v8(x + this->RENDER_SIZE, y + this->RENDER_SIZE, z - this->RENDER_SIZE);

        glm::vec3 normal(0.0f, 0.0f, 1.0f);
        this->addCubeFace(v1, v2, v3, v4, normal);

        normal = glm::vec3(0.0f, 0.0f, -1.0f);
        this->addCubeFace(v5, v6, v7, v8, normal);

        normal = glm::vec3(1.0f, 0.0f, 0.0f);
        this->addCubeFace(v2, v5, v8, v3, normal);

        normal = glm::vec3(-1.0f, 0.0f, 0.0f);
        this->addCubeFace(v6, v1, v4, v7, normal);

        normal = glm::vec3(0.0f, 1.0f, 0.0f);
        this->addCubeFace(v4, v3, v8, v7, normal);

        normal = glm::vec3(0.0f, -1.0f, 0.0f);
        this->addCubeFace(v6, v5, v2, v1, normal);
    }

    void Chunk::addCubeFace(const glm::vec3& v1, const glm::vec3& v2, const glm::vec3& v3, const glm::vec3& v4, const glm::vec3& normal)
    {
        VertexColor vertex;
        vertex.color = this->color;
        vertex.normal = normal;

        size_t index_start = this->vertices.size();
        vertex.position = v1;
        this->vertices.push_back(vertex);
        vertex.position = v2;
        this->vertices.push_back(vertex);
        vertex.position = v3;
        this->vertices.push_back(vertex);
        vertex.position = v4;
        this->vertices.push_back(vertex);
        
        this->indices.push_back(index_start);
        this->indices.push_back(index_start + 1);
        this->indices.push_back(index_start + 2);

        this->indices.push_back(index_start);
        this->indices.push_back(index_start + 2);
        this->indices.push_back(index_start + 3);
    }

    void Chunk::draw()
    {
        bool areBuffersSetup = this->setupBuffers();
        if (areBuffersSetup)
        {

            // Draw mesh
            glBindVertexArray(this->vertexArrayObject);
            glDrawElements(GL_TRIANGLES, this->indices.size(), GL_UNSIGNED_INT, 0);
            //glDrawArrays(GL_TRIANGLES, 0, this->vertices.size());
            glBindVertexArray(0);
        }
    }


    bool Chunk::setupBuffers()
    {
        if (this->vertices.empty()
            && this->indices.empty()
            )
            return false;

        // VAO
        glBindVertexArray(this->vertexArrayObject);

        // VBO
        glBindBuffer(GL_ARRAY_BUFFER, this->vertexBufferObject);
        glBufferData(GL_ARRAY_BUFFER, this->vertices.size() * sizeof(VertexColor),
            vertices.data(), GL_STATIC_DRAW);

        // EBO
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, this->elementBufferObject);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, this->indices.size() * sizeof(Index),
            this->indices.data(), GL_STATIC_DRAW);

        // Vertex positions
        glEnableVertexAttribArray(0);
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(VertexColor), (void*)0);
        // Vertex normals
        glEnableVertexAttribArray(1);
        glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(VertexColor), (void*)offsetof(VertexColor, normal));
        // Vertex texture coordinates
        glEnableVertexAttribArray(2);
        glVertexAttribPointer(2, 4, GL_FLOAT, GL_FALSE, sizeof(VertexColor), (void*)offsetof(VertexColor, color));

        glBindVertexArray(0);

        return true;
    }
}