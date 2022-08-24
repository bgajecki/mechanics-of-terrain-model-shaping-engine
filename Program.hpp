#pragma once

#include <vector>
#include <memory>
#include "Shader.hpp"


namespace Engine
{
	/**
	* @brief Program ID type.
	*/
	typedef GLuint ProgramId;

	/**
	* @brief Shared pointer to shader object.
	*/
	typedef std::shared_ptr<Shader> ShaderPointer;

	/**
	* @brief Vector of shared pointers to shader objects.
	*/
	typedef std::vector<ShaderPointer> ShaderVector;

	/**
	* @brief A program class that stores shaders and manage them.
	*/
	class Program
	{
	public:
		/**
		* @brief Create new instance of program.
		*/
		Program();

		/**
		* @brief Program can't be copied, because it's creating problem with assignment.
		*/
		Program(const Program&) = delete;

		/**
		* @brief Swaping program IDs.
		*/
		Program(Program&&);

		/**
		* @brief Delete program if already exist.
		*/
		~Program();

		/**
		* Link program.
		*/
		void link(const ShaderData&);

		/**
		* @brief Delete program if already exist and initialize fields of the class.
		*/
		void clear();

		/**
		* @brief Add a new shader in program.
		* @param shaderInfo Contains shader code and shader type.
		* @return Pointer to shader.
		*/
		Shader* addShader(const ShaderData&);

		/**
		* @brief Add a new existing shader in program.
		* @param  shader Pointer to existing shader.
		* @return Pointer to shader.
		*/
		Shader* addShader(Shader*);

		/**
		* @brief Delete shader by pointer.
		* @param Pointer to shader.
		*/
		void deleteShader(Shader*);

		/**
		* @brief Delete all shaders.
		*/
		void deleteShaders();

		/**
		* @brief Use program.
		*/
		void use();

		/**
		* @brief Get program Id.
		*/
		const ProgramId getId() const;
	private:
		/**
		* @brief Attach shaders to program.
		*/
		void attachShaders();

		/**
		* @brief Detach shaders from program.
		*/
		void detachShaders();

		/**
		* @brief Check program linking status.
		*/
		void checkLinkingStatus();

		/**
		* @brief Program Id.
		*/
		ProgramId id;

		/**
		* @brief Vector of shaders. Contains all shaders used by program.
		*/
		ShaderVector shaders;
	};
}