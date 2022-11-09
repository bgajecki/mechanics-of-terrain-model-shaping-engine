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
            //glActiveTexture(GL_TEXTURE0 + i); // activate proper texture unit before binding
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
            //glBindTexture(GL_TEXTURE_2D, this->textures[i]);
            this->textures[i].bind(i);
        }
        glActiveTexture(GL_TEXTURE0);
        
        // Draw mesh
        glBindVertexArray(this->vertexArrayObject);
        glDrawElements(GL_TRIANGLES, this->indices.size(), GL_UNSIGNED_INT, 0);
        //glDrawArrays(GL_TRIANGLES, 0, this->vertices.size());
        glBindVertexArray(0);
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
            if (type == "v")
            {
                Position position;
                stream >> position.x >> position.y >> position.z;
                positions.push_back(position);
            }
            else if (type == "vn")
            {
                Normal normal;
                stream >> normal.x >> normal.y >> normal.z;
                normals.push_back(normal);
            }
            else if (type == "vt")
            {
                TextureCoordinate texture_coordinate;
                stream >> texture_coordinate.x >> texture_coordinate.y;
                texture_coordinates.push_back(texture_coordinate);
            }
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

        this->vertices.resize(this->indices.size(), Vertex());

        for (size_t i = 0; i < this->vertices.size(); i++)
        {
            this->vertices[i].position = positions[positions_indices[i]];
            this->vertices[i].normal = normals[normals_indices[i]];
            this->vertices[i].textureCoordinate = texture_coordinates[texture_coordinates_indices[i]];
        }
    }

    bool inline Mesh::checkData()
    {
        bool areDataNotCorrect = this->verticesSize != this->vertices.size() ||
            this->indicesSize != this->indices.size() ||
            //this->texturesSize != this->textures.size() ||
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
            //&& this->textures.empty()
            )
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
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, this->indices.size() * sizeof(Index),
        this->indices.data(), GL_STATIC_DRAW);

        // Vertex positions
        glEnableVertexAttribArray(0);
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)0);
        // Vertex normals
        glEnableVertexAttribArray(1);
        glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, normal));
        // Vertex texture coordinates
        glEnableVertexAttribArray(2);
        glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*)offsetof(Vertex, textureCoordinate));

        glBindVertexArray(0);

        return true;
    }

}