#pragma once

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <GL/glew.h> 
#include <array>

namespace engine
{
	/**
	* @brief 3D position type.
	*/
	using Position = glm::vec3;

	/**
	* @brief 3D normal type.
	*/
	using Normal = glm::vec3;

	/**
	* @brief Type of texture coordinate.
	*/
	using TextureCoordinate = glm::vec2;

	/**
	* @brief Type of color.
	*/
	using Color = glm::vec4;

	/**
	* @brief Type of velocity.
	*/
	using Velocity = glm::vec3;

	/**
	* @brief Type of acceleration.
	*/
	using Acceleration = glm::vec3;

	/**
	* @brief Type of lifespan.
	*/
	using Lifespan = GLfloat;

	/**
	* @brief Type of index.
	*/
	using Index = GLuint;

	/**
	* @brief Type of matrix.
	*/
	using Matrix = glm::mat4;

	/**
	* @brief Type of angle.
	*/
	using Angle = GLfloat;

	/**
	* @brief Type of direction.
	*/
	using Direction = glm::vec3;

	/**
	* @brief Type of primitives type.
	*/
	using PrimitivesType = GLenum;


	/**
	* @brief Vertex.
	* @tparam T Type of attribute - color or texture coordinate.
	*/
	template<typename T>
	struct Vertex
	{
		/**
		* @brief 3D position of the vertex.
		*/
		Position position;

		/**
		* @brief 3D normal of the vertex.
		*/
		Normal normal;

		/**
		* @brief Attribute of the vertex.
		*/
		T attribute;
	};

	/**
	* @brief Particle.
	*/
	struct Particle
	{
		/**
		* @brief 3D position of the particle.
		*/
		Position position;

		/**
		* @brief Velocity of the particle.
		*/
		Velocity velocity;

		/**
		* @brief Acceleration of the particle.
		*/
		Acceleration acceleration;

		/**
		* @brief Lifespan of the particle.
		*/
		Lifespan lifespan;
	};
}