#pragma once

#include "Program.hpp"

namespace engine
{
	namespace implementation
	{
		/**
		* @brief A shader manager class that manages shaders in the stage.
		*/
		class Scene
		{
		public:
			/**
			* @brief A shader manager class that manages shaders in the stage.
			*/
			virtual void draw(const engine::Program&);
		};

	}
}
