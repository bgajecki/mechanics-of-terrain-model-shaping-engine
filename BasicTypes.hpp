#pragma once

#include <glm/glm.hpp> 
#include <GL/glew.h> 

namespace engine
{
	using Position = glm::vec3;
	using Normal = glm::vec3;
	using TextureCoordinates = glm::vec2;

	using Matrix = glm::mat4;

	struct Vertex
	{
		Position position;
		Normal normal;
		TextureCoordinates textureCoordinates;
	};

	struct Camera
	{
		Position eye, center, up;
		rotateCamera();
	};

}