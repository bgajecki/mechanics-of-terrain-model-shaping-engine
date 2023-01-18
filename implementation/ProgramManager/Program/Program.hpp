#pragma once

#include <vector>
#include <list>
#include <algorithm>
#include <functional>
#include <unordered_map>
#include "Shader.hpp"


namespace engine
{
	namespace implementation
	{
		/**
		* @brief Program ID type.
		*/
		using ProgramId = GLuint;

		/**
		* @brief Vector of shared pointers to shader objects.
		*/
		using ShaderVector = std::vector<engine::Shader>;

		/**
		* @brief Program of shaders.
		*/
		class Program final
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
			Program(Program&&) noexcept;

			/**
			* @brief Delete program if already exist.
			*/
			~Program();

			/**
			* @brief Link program.
			*/
			void link();

			/**
			* @brief Delete program if already exist and initialize fields of the class.
			*/
			void clear();

			/**
			* @brief Add a new shader in program.
			* @param shaderInfo Contains shader code and shader type.
			* @return Pointer to shader.
			*/
			void addShader(const engine::Shader&);

			/**
			* @brief Delete shader by pointer.
			* @param Pointer to shader.
			*/
			void deleteShader(const engine::Shader&);

			/**
			* @brief Delete all shaders.
			*/
			void deleteShaders();

			/**
			* @brief Use program.
			*/
			void use();

			/**
			* @brief Load uniforms.
			*/
			void loadUniforms();

			/**
			* @brief Create a new uniform.
			* @tparam UniformCallback Type of function passed by uniformCallback parameter.
			* @tparam RestOfParameters Types of the rest of parameters.
			* @param uniformCallback Uniform callback for specified type of uniform.
			* @param name Name of the uniform.
			* @param restOfParameters Rest of parameters passed to the uniform callback.
			*/
			template <typename UniformCallback, typename... RestOfParameters>
			void createUniform(UniformCallback uniformCallback, const std::string& name, RestOfParameters... restOfParameters)
			{
				this->loadUniformsFunctions.push_back([this, uniformCallback, name, restOfParameters...]()
				{
					GLint location = this->getUniformLocation(name);
					uniformCallback(location, restOfParameters...);
				});
			}

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

			GLint getUniformLocation(const std::string& location);

			/**
			* @brief Program Id.
			*/
			ProgramId id;

			/**
			* @brief Vector of shaders. Contains all shaders used by program.
			*/
			ShaderVector shaders;

			std::vector<std::function<void()>> loadUniformsFunctions;

			std::unordered_map <std::string, GLint> uniformLocation;
		};
		/**
		* @brief List of programs.
		*/
		using ProgramList = std::list<Program>;
	}
	/**
	* @brief Shader const iterator.
	*/
	using Program = implementation::ProgramList::iterator;
}