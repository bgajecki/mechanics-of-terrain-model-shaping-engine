#pragma once

#include <vector>
#include <array>
#include "implementation/Object/Object.hpp"
#include <glm/gtc/matrix_transform.hpp>
#include "BasicTypes.hpp"
#include "Voxel.hpp"
#include <functional>

namespace engine
{
    /**
    * @brief Type of function called on singular voxels.
    */
    using VoxelFunction = std::function<void(size_t, size_t, size_t)>;

    /**
    * @brief Protype chunk class.
    * @tparam T Type of voxel attribute.
    * @tparam NumberOfVoxelTypes Number of voxel types.
    */
    template<typename T, size_t NumberOfVoxelTypes>
    class Chunk : public implementation::Object
    {
        /**
        * @brief 3D matrix of voxels.
        */
        using VoxelVector = std::vector<std::vector<std::vector<Voxel>>>;

        /**
        * @brief Vector of vertices.
        */
        using VertexVector = std::vector<Vertex<T>>;

        /**
        * @brief Vector of indicies.
        */
        using IndexVector = std::vector<Index>;

        /**
        * @brief Array of voxel types.
        */
        using VoxelTypeArray = std::array<T, NumberOfVoxelTypes>;
        
    public:

        /**
        * @brief Chunk constructor.
        */
        Chunk();

        /**
        * @brief Chunk destructor.
        */
        virtual ~Chunk();

        /**
        * @brief Drawing primitives.
        */
        virtual void draw() override;

        /**
        * @brief Refresh chunk. Calculate which voxels faces draw.
        */
        void refresh();

        /**
        * @brief Resize chunk.
        * @param size New size of the chunk.
        */
        void resize(size_t size);

        /**
        * @brief Set voxel size.
        * @param size New size of the voxel.
        */
        void setVoxelSize(float voxelSize);

        /**
        * @brief Set attribute for voxel type.
        * @param index Index of voxel type.
        * @param attribute Attribute of voxel type.
        */
        void setVoxelTypeAttribute(size_t index, T attribute);

    protected:

        /**
        * @brief Setup buffers.
        */
        virtual bool setupBuffers();

        /**
        * @brief Generate veritces of the voxel.
        * @param xNegative Whether to draw the face from the x-negative side.
        * @param xPositive Whether to draw the face from the x-positive side.
        * @param yNegative Whether to draw the face from the y-negative side.
        * @param yPositive Whether to draw the face from the y-positive side.
        * @param zNegative Whether to draw the face from the z-negative side.
        * @param zPositive Whether to draw the face from the z-positive side.
        * @param position Position of the voxel.
        * @param type Type of the voxel.
        */
        void generateVertices(bool xNegative, bool xPositive, bool yNegative, bool yPositive, bool zNegative, bool zPositive, const Position& position, unsigned type);

        /**
        * @brief Add voxel face.
        * @param v1 First vertex position.
        * @param v2 Second vertex position.
        * @param v3 Third vertex position.
        * @param v4 Fourth vertex position.
        * @param normal Normal of the voxel face.
        * @param attribute Attribute of voxel type.
        */
        void addVoxelFace(const Position& v1, const Position& v2, const Position& v3, const Position& v4, const Normal& normal, const T& attribute);

        /**
        * @brief Execute function on each voxels.
        * @param function Function which will be executed on each voxels.
        */
        void executeOnEachVoxels(VoxelFunction function);

        /**
        * @brief Execute function on selected voxels.
        * @param xMin X minimum range.
        * @param xMax X maximum range.
        * @param yMin Y minimum range.
        * @param yMax Y maximum range.
        * @param zMin Z minimum range.
        * @param zMax Z maximum range.
        * @param function Function which will be executed on selected voxels.
        */
        void executeOnSelectedVoxels(size_t xMin, size_t xMax, size_t yMin, size_t yMax, size_t zMin, size_t zMax, VoxelFunction function);

        /**
        * @brief Size of the chunk.
        */
        size_t chunkSize;

        /**
        * @brief Size of singular voxel.
        */
        float voxelSize;

        /**
        * @brief Vertices container.
        */
        VertexVector vertices;

        /**
        * @brief Voxels container.
        */
        VoxelVector voxels;

        /**
        * @brief Indices container.
        */
        IndexVector indices;

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

        /**
        * @brief Voxel types array.
        */
        VoxelTypeArray voxelTypes;

    };
    
    template<typename T, size_t NumberOfVoxelTypes>
    Chunk<T, NumberOfVoxelTypes>::Chunk()
        : voxelSize(0.01f), chunkSize(16u)
    {
        glGenVertexArrays(1, &this->vertexArrayObject);
        glGenBuffers(1, &this->vertexBufferObject);
        glGenBuffers(1, &this->elementBufferObject);
    }

    template<typename T, size_t NumberOfVoxelTypes>
    Chunk<T, NumberOfVoxelTypes>::~Chunk()
    {
        glDeleteBuffers(1, &this->vertexBufferObject);
        glDeleteBuffers(1, &this->elementBufferObject);
        glDeleteVertexArrays(1, &this->vertexArrayObject);
    }

    template<typename T, size_t NumberOfVoxelTypes>
    void Chunk<T, NumberOfVoxelTypes>::refresh()
    {
        this->vertices.clear();
        this->indices.clear();
        this->executeOnEachVoxels([this](size_t x, size_t y, size_t z) {
            if (this->voxels[x][y][z].isActive())
            {
                bool xNegative = true;
                if (x > 0)
                    xNegative = this->voxels[x - 1][y][z].isActive() == false;

                bool xPositive = true;
                if (x < this->chunkSize - 1u)
                    xPositive = this->voxels[x + 1][y][z].isActive() == false;

                bool yNegative = true;
                if (y > 0)
                    yNegative = this->voxels[x][y - 1][z].isActive() == false;

                bool yPositive = true;
                if (y < this->chunkSize - 1u)
                    yPositive = this->voxels[x][y + 1][z].isActive() == false;

                bool zNegative = true;
                if (z > 0)
                    zNegative = this->voxels[x][y][z - 1].isActive() == false;

                bool zPositive = true;
                if (z < this->chunkSize - 1u)
                    zPositive = this->voxels[x][y][z + 1].isActive() == false;

                Position position = Position(static_cast<float>(x) * this->voxelSize, static_cast<float>(y) * this->voxelSize, static_cast<float>(z) * this->voxelSize);
                this->generateVertices(xNegative, xPositive, yNegative, yPositive, zNegative, zPositive, position, this->voxels[x][y][z].getType());
            }
        });
    }

    template<typename T, size_t NumberOfVoxelTypes>
    void Chunk<T, NumberOfVoxelTypes>::generateVertices(bool xNegative, bool xPositive, bool yNegative, bool yPositive, bool zNegative, bool zPositive, const Position& position, unsigned type)
    {
        float x = position.x, y = position.y, z = position.z;
        Position v1(x - this->voxelSize, y - this->voxelSize, z + this->voxelSize);
        Position v2(x + this->voxelSize, y - this->voxelSize, z + this->voxelSize);
        Position v3(x + this->voxelSize, y + this->voxelSize, z + this->voxelSize);
        Position v4(x - this->voxelSize, y + this->voxelSize, z + this->voxelSize);
        Position v5(x + this->voxelSize, y - this->voxelSize, z - this->voxelSize);
        Position v6(x - this->voxelSize, y - this->voxelSize, z - this->voxelSize);
        Position v7(x - this->voxelSize, y + this->voxelSize, z - this->voxelSize);
        Position v8(x + this->voxelSize, y + this->voxelSize, z - this->voxelSize);
        T attribute = this->voxelTypes[type];

        Normal normal;
        if (zPositive)
        {
            normal = Normal(0.0f, 0.0f, 1.0f);
            this->addVoxelFace(v1, v2, v3, v4, normal, attribute);
        }

        if (zNegative)
        {
            normal = Normal(0.0f, 0.0f, -1.0f);
            this->addVoxelFace(v5, v6, v7, v8, normal, attribute);
        }

        if (xPositive)
        {
            normal = Normal(1.0f, 0.0f, 0.0f);
            this->addVoxelFace(v2, v5, v8, v3, normal, attribute);
        }

        if (xNegative)
        {
            normal = Normal(-1.0f, 0.0f, 0.0f);
            this->addVoxelFace(v6, v1, v4, v7, normal, attribute);
        }

        if (yPositive)
        {
            normal = Normal(0.0f, 1.0f, 0.0f);
            this->addVoxelFace(v4, v3, v8, v7, normal, attribute);
        }

        if (yNegative)
        {
            normal = Normal(0.0f, -1.0f, 0.0f);
            this->addVoxelFace(v6, v5, v2, v1, normal, attribute);
        }
    }

    template<typename T, size_t NumberOfVoxelTypes>
    void Chunk<T, NumberOfVoxelTypes>::resize(size_t size)
    {
        this->chunkSize = size;
        //this->vertices.reserve(size*size*size*6*4);
        //this->indices.reserve(size*size*size*6*4);
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

    template<typename T, size_t NumberOfVoxelTypes>
    void Chunk<T, NumberOfVoxelTypes>::setVoxelSize(float size)
    {
        this->voxelSize = size;
    }

    template<typename T, size_t NumberOfVoxelTypes>
    void Chunk<T, NumberOfVoxelTypes>::setVoxelTypeAttribute(const size_t index, const T attribute)
    {
        if (index <= NumberOfVoxelTypes - 1u)
        {
            this->voxelTypes[index] = attribute;
        }
    }

    template<typename T, size_t NumberOfVoxelTypes>
    void Chunk<T, NumberOfVoxelTypes>::addVoxelFace(const Position& v1, const Position& v2, const Position& v3, const Position& v4, const Normal& normal, const T& attribute)
    {
        Vertex<T> vertex;
        vertex.attribute = attribute;
        vertex.normal = normal;

        Index index_start = this->vertices.size();
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



    template<typename T, size_t NumberOfVoxelTypes>
    void Chunk<T, NumberOfVoxelTypes>::executeOnEachVoxels(VoxelFunction function)
    {
        for (size_t x = 0; x < this->chunkSize; x++)
            for (size_t y = 0; y < this->chunkSize; y++)
                for (size_t z = 0; z < this->chunkSize; z++)
                    function(x, y, z);
    }

    template<typename T, size_t NumberOfVoxelTypes>
    void Chunk<T, NumberOfVoxelTypes>::executeOnSelectedVoxels(size_t xMin, size_t xMax, size_t yMin, size_t yMax, size_t zMin, size_t zMax, VoxelFunction function)
    {
        if (xMax <= this->chunkSize
            && yMax <= this->chunkSize
            && zMax <= this->chunkSize)
            for (size_t x = xMin; x < xMax; x++)
                for (size_t y = yMin; y < yMax; y++)
                    for (size_t z = zMin; z < zMax; z++)
                        function(x, y, z);
    }

    template<typename T, size_t NumberOfVoxelTypes>
    void Chunk<T, NumberOfVoxelTypes>::draw()
    {
        bool areBuffersSetup = this->setupBuffers();
        if (areBuffersSetup)
        {
            // Draw mesh
            glBindVertexArray(this->vertexArrayObject);
            glDrawElements(this->primitivesType, this->indices.size(), GL_UNSIGNED_INT, 0);
            //glDrawArrays(GL_TRIANGLES, 0, this->vertices.size());
            glBindVertexArray(0);
        }
    }

    template<typename T, size_t NumberOfVoxelTypes>
    bool Chunk<T, NumberOfVoxelTypes>::setupBuffers()
    {
        if (this->vertices.empty()
            && this->indices.empty()
            )
            return false;

        // VAO
        glBindVertexArray(this->vertexArrayObject);

        // VBO
        glBindBuffer(GL_ARRAY_BUFFER, this->vertexBufferObject);
        glBufferData(GL_ARRAY_BUFFER, this->vertices.size() * sizeof(Vertex<T>),
            vertices.data(), GL_DYNAMIC_DRAW);

        // EBO
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, this->elementBufferObject);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, this->indices.size() * sizeof(Index),
            this->indices.data(), GL_DYNAMIC_DRAW);

        // Vertex positions
        glEnableVertexAttribArray(0);
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex<T>), (void*)0);
        // Vertex normals
        glEnableVertexAttribArray(1);
        glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex<T>), (void*)offsetof(Vertex<T>, normal));
        // Vertex texture coordinates
        glEnableVertexAttribArray(2);
        glVertexAttribPointer(2, sizeof(T) / 4u, GL_FLOAT, GL_FALSE, sizeof(Vertex<T>), (void*)offsetof(Vertex<T>, attribute));

        glBindVertexArray(0);

        return true;
    }
}