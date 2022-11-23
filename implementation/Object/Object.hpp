#pragma once

#include "Program.hpp"
#include "BasicTypes.hpp"

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
			Object();

			/**
			* @brief A shader manager class that manages shaders in the stage.
			*/
			~Object() = default;

			/**
			* @brief A shader manager class that manages shaders in the stage.
			*/
			virtual void draw();

			/**
			* @brief A shader manager class that manages shaders in the stage.
			*/
			void setPosition(Position);
			
			/**
			* @brief A shader manager class that manages shaders in the stage.
			*/
			Position getPosition() const;
			
			/**
			* @brief A shader manager class that manages shaders in the stage.
			*/
			void setProgram(const engine::Program&);

			/**
			* @brief A shader manager class that manages shaders in the stage.
			*/
			const engine::Program getProgram() const;

			/**
			* @brief A shader manager class that manages shaders in the stage.
			*/
			virtual Matrix getModelMatrix() const;

		protected:

			/**
			* Draw mesh
			*/
			engine::Program program;

			/**
			* Draw mesh
			*/
			Position position;
		};

	}
}
