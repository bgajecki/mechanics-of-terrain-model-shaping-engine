#pragma once

#include <array>
#include "Program.hpp"
#include "ShaderLoader.hpp"


namespace Engine
{
	/**
	* @brief Unique pointer to program object.
	*/
	using ProgramPointer = std::unique_ptr<Program>;

	/**
	* @brief Array of unique pointers to program objects.
	*/
	template <size_t size>
	using ProgramArray = std::array<ProgramPointer, size>;

	/**
	* @brief A shader manager class that manages shaders in the stage.
	*/
	template <size_t size>
	class ShaderManager
	{
	public:

		ShaderManager() = delete;

		/**
		* @brief Initialize shader loader by shader list.
		* @param list List of the paths and types of shaders.
		*/
		ShaderManager(const ShaderList&);

		/**
		* Delete all programs.
		*/
		~ShaderManager();

		/**
		* @brief Only one istance of ShaderManager object.
		*/
		ShaderManager(const ShaderManager&) = delete;
		/**
		* @brief Only one istance of ShaderManager object.
		*/
		ShaderManager(ShaderManager&&) = delete;

		/**
		* @brief Create program and return instance.
		* @return Index of the program.
		*/
		const int createProgram();

		/**
		* @brief Delete program.
		* @param program Index of the program.
		*/
		void deleteProgram(const size_t);

		/**
		* @brief Delete all programs.
		*/
		void deletePrograms();

		/**
		* @brief Link program.
		* @param index Program index.
		*/
		void linkProgram(const size_t);

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
		ShaderWeakPointer assignShader(const size_t, const size_t);

		/**
		* @brief Assign shader to programs.
		* @param shader Shader index.
		* @param program Program index.
		* @param programs Rest of programs.
		*/
		template<typename... Programs>
		void assignShader(const size_t shader, const size_t program, Programs... programs)
		{
			ShaderWeakPointer createdShader = this->assignShader(shader, program);
			auto helpFunction = [&programs] (auto& shader, const auto i)
			{
				this->programs[i]->addShader(shader);
			};
			helpFunction(createdShader, programs...);
		}

	private:
		/**
		* @brief Shader loader.
		*/
		ShaderLoader shaderLoader;
		/**
		* @brief Array of programs. Contains all programs used by stages.
		*/	
		ProgramArray<size> programs;
	};
}