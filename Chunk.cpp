#include "Chunk.hpp"
#include "Chunk.hpp"
#include "Chunk.hpp"

namespace engine
{
    Chunk::Chunk()
        : renderSize(0.01f), position({0.0f, 0.0f, 0.0f}), chunkSize(16u)
    {
        glGenVertexArrays(1, &this->vertexArrayObject);
        glGenBuffers(1, &this->vertexBufferObject);
        glGenBuffers(1, &this->elementBufferObject);
    }

    Chunk::~Chunk()
    {
        glDeleteBuffers(1, &this->vertexBufferObject);
        glDeleteBuffers(1, &this->elementBufferObject);
        glDeleteVertexArrays(1, &this->vertexArrayObject);
    }

    void Chunk::refresh()
    {
        this->vertices.clear();
        this->indices.clear();
        for (size_t x = 0; x < this->chunkSize; x++)
        {
            for (size_t y = 0; y < this->chunkSize; y++)
            {
                for (size_t z = 0; z < this->chunkSize; z++)
                {
                    Voxel voxel = this->voxels[x][y][z];
                    if (voxel.active)
                    {
                        if (x != 0 && x != this->chunkSize - 1u
                            && y != 0 && y != this->chunkSize - 1u
                            && z != 0 && z != this->chunkSize - 1u
                            && this->voxels[x - 1][y][z].active == true
                            && this->voxels[x + 1][y][z].active == true
                            && this->voxels[x][y - 1][z].active == true
                            && this->voxels[x][y + 1][z].active == true
                            && this->voxels[x][y][z - 1].active == true
                            && this->voxels[x][y][z + 1].active == true
                            )
                        {

                        }
                        else
                        {
                            Position position = this->position + Position(static_cast<float>(x) * this->renderSize,
                                static_cast<float>(y) * this->renderSize,
                                static_cast<float>(z) * this->renderSize);
                            this->generateVertices(position, voxel.color);
                        }
                    }
                }
            }
        }
    }

    void Chunk::update(float dt)
    {
        this->refresh();
    }

    void Chunk::generateVertices(const Position& position, const Color& color)
    {
        float x = position.x, y = position.y, z = position.z;
        glm::vec3 v1(x - this->renderSize, y - this->renderSize, z + this->renderSize);
        glm::vec3 v2(x + this->renderSize, y - this->renderSize, z + this->renderSize);
        glm::vec3 v3(x + this->renderSize, y + this->renderSize, z + this->renderSize);
        glm::vec3 v4(x - this->renderSize, y + this->renderSize, z + this->renderSize);
        glm::vec3 v5(x + this->renderSize, y - this->renderSize, z - this->renderSize);
        glm::vec3 v6(x - this->renderSize, y - this->renderSize, z - this->renderSize);
        glm::vec3 v7(x - this->renderSize, y + this->renderSize, z - this->renderSize);
        glm::vec3 v8(x + this->renderSize, y + this->renderSize, z - this->renderSize);

        glm::vec3 normal(0.0f, 0.0f, 1.0f);
        this->addVoxelFace(v1, v2, v3, v4, normal, color);

        normal = glm::vec3(0.0f, 0.0f, -1.0f);
        this->addVoxelFace(v5, v6, v7, v8, normal, color);

        normal = glm::vec3(1.0f, 0.0f, 0.0f);
        this->addVoxelFace(v2, v5, v8, v3, normal, color);

        normal = glm::vec3(-1.0f, 0.0f, 0.0f);
        this->addVoxelFace(v6, v1, v4, v7, normal, color);

        normal = glm::vec3(0.0f, 1.0f, 0.0f);
        this->addVoxelFace(v4, v3, v8, v7, normal, color);

        normal = glm::vec3(0.0f, -1.0f, 0.0f);
        this->addVoxelFace(v6, v5, v2, v1, normal, color);
    }

    void Chunk::resize(size_t size)
    {
        this->chunkSize = size;
        this->voxels.resize(this->chunkSize);
        for (auto& i : this->voxels)
        {
            i.resize(this->chunkSize);
            for (auto& j : i)
            {
                j.resize(this->chunkSize);
            }

        }
    }

    void Chunk::addVoxelFace(const Position& v1, const Position& v2, const Position& v3, const Position& v4, const Normal& normal, const Color& color)
    {
        VertexColor vertex;
        vertex.color = color;
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