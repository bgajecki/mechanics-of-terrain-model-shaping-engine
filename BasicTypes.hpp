#pragma once

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <GL/glew.h> 
#include <array>

namespace engine
{
	using Position = glm::vec3;
	using Normal = glm::vec3;
	using TextureCoordinate = glm::vec2;
	using Color = glm::vec4;

	using Velocity = glm::vec3;
	using Acceleration = glm::vec3;
	using Lifespan = GLfloat;

	using Index = GLuint;

	using Matrix = glm::mat4;

	using Angle = GLfloat;

	using Direction = glm::vec3;

	using PrimitivesType = GLenum;

	template<typename T>
	struct Vertex
	{
		Position position;
		Normal normal;
		T attribute;
	};

	struct Particle
	{
		Position position;
		Velocity velocity;
		Acceleration acceleration;
		Lifespan lifespan;
	};
}