#include "Mesh.hpp"

namespace engine
{
    Mesh::Mesh()
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
        bool areBuffersSetup = this->setupBuffers();
        if (areBuffersSetup)
        {
            this->setupTextures();
            // Draw mesh
            glBindVertexArray(this->vertexArrayObject);
            glDrawElements(this->primitivesType, this->indices.size(), GL_UNSIGNED_INT, 0);
            //glDrawArrays(GL_TRIANGLES, 0, this->vertices.size());
            glBindVertexArray(0);
        }
    }

    bool Mesh::loadObj(const std::string& path)
    {
        std::ifstream file(path);

        if (!file.is_open())
        {
            std::cerr << "Could not read file " << path << ". File does not exist." << std::endl;
            return false;
        }

        std::vector<Position> positions;
        std::vector<Normal> normals;
        std::vector<TextureCoordinate> texture_coordinates;

        std::vector<Index> positions_indices;
        std::vector<Index> texture_coordinates_indices;
        std::vector<Index> normals_indices;

        std::istringstream stream;
        std::string line, type;
        while (std::getline(file, line))
        {
            stream.str(line);
            stream >> type;
            // Vertex.
            if (type == "v")
            {
                Position position;
                stream >> position.x >> position.y >> position.z;
                positions.push_back(position);
            }
            // Vertex normal.
            else if (type == "vn")
            {
                Normal normal;
                stream >> normal.x >> normal.y >> normal.z;
                normals.push_back(normal);
            }
            // Vertex texutre coordinate.
            else if (type == "vt")
            {
                TextureCoordinate texture_coordinate;
                stream >> texture_coordinate.x >> texture_coordinate.y;
                texture_coordinates.push_back(texture_coordinate);
            }
            // Face.
            else if (type == "f")
            {
                Index index;
                for (size_t i = 0u; stream >> index; )
                {
                    index--;
                    switch (i)
                    {
                        case 0u:
                        {
                            positions_indices.push_back(index);
                            break;
                        }
                        case 1u:
                        {
                            texture_coordinates_indices.push_back(index);
                            break;
                        }
                        case 2u:
                        {
                            normals_indices.push_back(index);
                            this->indices.push_back(this->indices.size());
                            break;
                        }
                    }

                    // Ignore format characters.
                    if (stream.peek() == '/')
                    {
                        stream.ignore(1, '/');
                        i++;
                    }
                    else if (stream.peek() == ' ')
                    {
                        stream.ignore(1, ' ');
                        i = 0u;
                    }
                }
            }
            stream.clear();
        }
        file.close();

        this->vertices.resize(this->indices.size(), MeshVertex());

        for (size_t i = 0; i < this->vertices.size(); i++)
        {
            this->vertices[i].position = positions[positions_indices[i]];
            this->vertices[i].normal = normals[normals_indices[i]];
            this->vertices[i].attribute = texture_coordinates[texture_coordinates_indices[i]];
        }
    }

    void Mesh::setupTextures()
    {

        for (size_t i = 0; i < this->textures.size(); i++)
            this->textures[i].bind(i);
        glActiveTexture(GL_TEXTURE0);
    }

    bool Mesh::setupBuffers()
    {
        if (this->vertices.empty()
            && this->indices.empty())
            return false;

        // VAO
        glBindVertexArray(this->vertexArrayObject);

        // VBO
        glBindBuffer(GL_ARRAY_BUFFER, this->vertexBufferObject);
        glBufferData(GL_ARRAY_BUFFER, this->vertices.size() * sizeof(MeshVertex),
            vertices.data(), GL_DYNAMIC_DRAW);
        //DYNAMIC_DRAW
        // EBO
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, this->elementBufferObject);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, this->indices.size() * sizeof(Index),
        this->indices.data(), GL_DYNAMIC_DRAW);

        // Vertex positions
        glEnableVertexAttribArray(0);
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(MeshVertex), (void*)0);
        // Vertex normals
        glEnableVertexAttribArray(1);
        glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(MeshVertex), (void*)offsetof(MeshVertex, normal));
        // Vertex texture coordinates
        glEnableVertexAttribArray(2);
        glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(MeshVertex), (void*)offsetof(MeshVertex, attribute));

        glBindVertexArray(0);

        return true;
    }

}