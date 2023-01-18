#pragma once

#include "Program.hpp"

namespace engine
{
	namespace implementation
	{
		/**
		* @brief A program manager class that manages programs.
		*/
		class ProgramManager
		{
		public:
			/**
			* @brief ProgramManager constructor.
			*/
			ProgramManager() = default;

			/**
			* @brief ProgramManager destructor.
			*/
			~ProgramManager() = default;

			/**
			* @brief Only one istance of ProgramManager object.
			*/
			ProgramManager(const ProgramManager&) = delete;

			/**
			* @brief Only one istance of ProgramManager object.
			*/
			ProgramManager(ProgramManager&&) = delete;

			/**
			* @brief Create program and return instance.
			* @return Index of the program.
			*/
			const engine::Program createProgram();

			/**
			* @brief Delete program.
			* @param program Index of the program.
			*/
			void deleteProgram(const engine::Program&);

			/**
			* @brief Delete all programs.
			*/
			void deletePrograms();

			/**
			* @brief Link program.
			* @param index Program index.
			*/
			void linkProgram(const engine::Program&);

			/**
			* @brief Link all programs.
			*/
			void linkPrograms();

			/**
			* @brief Assign shader to program.
			* @param shader Shader index.
			* @param program Program index.
			* @return Pointer to created shader.
			*/
			void assignShader(const engine::Shader&, const engine::Program&);

			/**
			* @brief Assign shader to programs.
			* @param shader Shader index.
			* @param program Program index.
			* @param programs Rest of programs.
			*/
			template<typename... Programs>
			void assignShader(const engine::Shader& shader, Programs... programs)
			{
				this->assignShader(shader, programs...);
			}

		protected:
			/**
			* @brief Array of programs. Contains all programs used by stages.
			*/
			ProgramList programs;
		};
	}
}