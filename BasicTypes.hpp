#pragma once

#include <glm/glm.hpp> 
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
	using LifeSpan = float;

	using Index = GLuint;

	using Matrix = glm::mat4;

	struct Vertex
	{
		Position position;
		Normal normal;
		TextureCoordinate textureCoordinate;
	};

	struct Particle
	{
		Position position;
		Velocity velocity;
		Acceleration acceleration;
		LifeSpan lifespan;
	};

	struct Camera
	{
		Position eye, center, up;
		//rotateCamera();
	};

	struct VertexColor
	{
		Position position;
		Normal normal;
		Color color;
	};

	using Voxel = bool;
}