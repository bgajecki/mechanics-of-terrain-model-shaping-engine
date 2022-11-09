#include "Particles.hpp"

namespace engine
{
    Particles::Particles()
    {
        glGenVertexArrays(1, &this->vertexArrayObject);
        glGenBuffers(1, &this->vertexBufferObject);
       // glGenBuffers(1, &this->elementBufferObject);
    }

    Particles::~Particles()
    {
        glDeleteBuffers(1, &this->vertexBufferObject);
        //glDeleteBuffers(1, &this->elementBufferObject);
        glDeleteVertexArrays(1, &this->vertexArrayObject);
    }

    void Particles::draw()
    {
        this->setupBuffers();
        
        // Draw mesh
        glBindVertexArray(this->vertexArrayObject);
        //glDrawElements(GL_TRIANGLES, this->indices.size(), GL_UNSIGNED_INT, 0);
        glDrawArrays(GL_POINTS, 0, this->particles.size());
        glBindVertexArray(0);
    }


    bool Particles::setupBuffers()
    {
        this->vertices.clear();

        for (auto& particle : this->particles)
            if(particle.lifespan > 0.0f)
                this->vertices.push_back(particle.position);

        // VAO
        glBindVertexArray(this->vertexArrayObject);

        // VBO
        glBindBuffer(GL_ARRAY_BUFFER, this->vertexBufferObject);
        glBufferData(GL_ARRAY_BUFFER, this->vertices.size() * sizeof(Position),
            vertices.data(), GL_STATIC_DRAW);

        // Vertex positions
        glEnableVertexAttribArray(0);
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Position), (void*)0);
        // Vertex normals
        //glEnableVertexAttribArray(1);
        //glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Particle), (void*)offsetof(Vertex, normal));
        // Vertex texture coordinates
        //glEnableVertexAttribArray(2);
        //glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Particle), (void*)offsetof(Vertex, textureCoordinate));

        glBindVertexArray(0);

        return true;
    }

}