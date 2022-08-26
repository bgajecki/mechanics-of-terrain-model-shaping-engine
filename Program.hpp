#pragma once

#include <vector>
#include <memory>
#include "Shader.hpp"


namespace Engine
{
	/**
	* @brief Program ID type.
	*/
	using ProgramId = GLuint;

	/**
	* @brief Shared pointer to shader object.
	*/
	using ShaderSharedPointer = std::shared_ptr<Shader>;

	/**
	* @brief Weak pointer to shader object.
	*/
	using ShaderWeakPointer = std::weak_ptr<Shader>;

	/**
	* @brief Vector of shared pointers to shader objects.
	*/
	using ShaderVector = std::vector<ShaderSharedPointer>;

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
		ShaderWeakPointer addShader(const ShaderData&);

		/**
		* @brief Add a new existing shader in program.
		* @param  shader Pointer to existing shader.
		* @return Pointer to shader.
		*/
		ShaderWeakPointer addShader(ShaderWeakPointer);

		/**
		* @brief Delete shader by pointer.
		* @param Pointer to shader.
		*/
		void deleteShader(ShaderWeakPointer);

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