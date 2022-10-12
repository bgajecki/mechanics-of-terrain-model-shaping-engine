#include "Mesh.hpp"

namespace engine
{
    Mesh::Mesh() :
        areBuffersSetup(false), verticesSize(0u), indicesSize(0u), texturesSize(0u)
    {
        glGenVertexArrays(1, &this->vertexArrayObject);
        glGenBuffers(1, &this->vertexBufferObject);
        glGenBuffers(1, &this->elementBufferObject);
    }

	Mesh::Mesh(const std::vector<Vertex>& vertices, const std::vector<unsigned int>& indices, const std::vector<Texture>& textures)
        : areBuffersSetup(false), verticesSize(0u), indicesSize(0u), texturesSize(0u), vertices(vertices), indices(indices), textures(textures)
    {
        glGenVertexArrays(1, &this->vertexArrayObject);
        glGenBuffers(1, &this->vertexBufferObject);
        glGenBuffers(1, &this->elementBufferObject);
	}

    Mesh::~Mesh()
    {
        glDeleteBuffers(1, &this->vertexBufferObject);
        glDeleteBuffers(1, &this->elementBufferObject);
        glDeleteVertexArrays(1, &this->vertexArrayObject);
    }

    void Mesh::draw()
    {
        bool areDataNotCorrect = this->checkData();
        if (areDataNotCorrect)
            return;

        //unsigned int diffuseNr = 1;
        //unsigned int specularNr = 1;
        for (size_t i = 0; i < this->textures.size(); i++)
        {
            glActiveTexture(GL_TEXTURE0 + i); // activate proper texture unit before binding
            // retrieve texture number (the N in diffuse_textureN)
            /*
            string number;
            string name = textures[i].type;
            if (name == "texture_diffuse")
                number = std::to_string(diffuseNr++);
            else if (name == "texture_specular")
                number = std::to_string(specularNr++);

            shader.setInt(("material." + name + number).c_str(), i);
            */
            glBindTexture(GL_TEXTURE_2D, this->textures[i]);
        }
        glActiveTexture(GL_TEXTURE0);

        // Draw mesh
        glBindVertexArray(this->vertexArrayObject);
        glDrawElements(GL_TRIANGLES, this->indices.size(), GL_UNSIGNED_INT, 0);
        glBindVertexArray(0);
    }

    bool inline Mesh::checkData()
    {
        bool areDataNotCorrect = this->verticesSize != this->vertices.size() ||
            this->indicesSize != this->indices.size() ||
            this->texturesSize != this->textures.size() ||
            this->areBuffersSetup == false;
        if (areDataNotCorrect)
        {
            this->areBuffersSetup = this->setupBuffers();
            areDataNotCorrect = this->areBuffersSetup ? true : false;
        }
        return areDataNotCorrect;
    }

    inline void Mesh::resetDataProtection()
    {
        this->verticesSize = this->vertices.size();
        this->indicesSize = this->indices.size();
        this->texturesSize = this->textures.size();
    }

    bool Mesh::setupBuffers()
    {
        if (this->vertices.empty()
            && this->indices.empty()
            && this->textures.empty())
            return false;

        this->resetDataProtection();

        // VAO
        glBindVertexArray(this->vertexArrayObject);

        // VBO
        glBindBuffer(GL_ARRAY_BUFFER, this->vertexBufferObject);
        glBufferData(GL_ARRAY_BUFFER, this->vertices.size() * sizeof(Vertex),
            vertices.data(), GL_STATIC_DRAW);

        // EBO
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, this->elementBufferObject);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, this->indices.size() * sizeof(this->indices[0]),
            this->indices.data(), GL_STATIC_DRAW);

        // Vertex positions
        glEnableVertexAttribArray(0);
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)0);
        // Vertex normals
        glEnableVertexAttribArray(1);
        glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, normal));
        // Vertex texture coordinates
        glEnableVertexAttribArray(2);
        glVertexAttribPointer(2, 1, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, textureCoordinates));

        glBindVertexArray(0);

        return true;
    }

}