#pragma once

#include <glm/glm.hpp> 
#include <GL/glew.h> 

namespace Engine
{
	using Position_t = glm::vec3;
	using Normal_t = glm::vec3;
	using TextureCoordinates_t = glm::vec2;

	using Direction_t = glm::vec4;

	using TextureType = GLuint;

	struct Vertex
	{
		Position_t position;
		Normal_t normal;
		TextureCoordinates_t textureCoordinates;
	};

	struct Camera
	{
		Position_t position;
		Direction_t direction;
	};

}