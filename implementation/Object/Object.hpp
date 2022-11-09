#pragma once

#include "Program.hpp"

namespace engine
{
	namespace implementation
	{
		/**
		* @brief A shader manager class that manages shaders in the stage.
		*/
		class Object
		{
		public:
			/**
			* @brief A shader manager class that manages shaders in the stage.
			*/
			virtual void draw();

			/**
			* Draw mesh
			*/
			engine::Program program;
		};

	}
}
