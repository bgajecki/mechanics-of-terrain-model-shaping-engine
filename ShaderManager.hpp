#pragma once

#include <array>
#include "Program.hpp"


namespace Engine
{
	/**
	* @brief Unique pointer to program object.
	*/
	typedef std::unique_ptr<Program> ProgramPointer;

	/**
	* @brief Vector of unique pointers to program objects.
	*/
	typedef std::vector<ProgramPointer> ProgramVector;

	/**
	* @brief A shader manager class that manages shaders in the stage.
	*/
	class ShaderManager
	{
	public:

		ShaderManager() = default;

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
		* @return Pointer to program.
		*/
		Program* createProgram();

		/**
		* @brief Delete program.
		* @param program Pointer to program.
		*/
		void deleteProgram(Program*);

		/**
		* @brief Delete all programs.
		*/
		void deletePrograms();
		
	private:
		/**
		* @brief Vector of programs. Contains all programs used by stage.
		*/	
		ProgramVector programs;
	};
}