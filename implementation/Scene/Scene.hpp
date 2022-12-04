#pragma once

#include "Program.hpp"

namespace engine
{
	namespace implementation
	{
		/**
		* @brief Interface class of the scene.
		*/
		class Scene
		{
		public:
			/**
			* @brief Drawing objects assigned to the scene and passed program by parameter.
			* @param program Program of shaders.
			*/
			virtual void draw(const engine::Program& program) = 0;
		};

	}
}
