#pragma once

#include <vector>
#include <list>
#include <algorithm>
#include <functional>
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
		* @brief A program class that stores shaders and manage them.
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
			* Link program.
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
	
			template <typename UniformCallback, typename... RestOfParameters>
			void createUniform(UniformCallback uniformCallback, const char* name, RestOfParameters... restOfParameters)
			{
				this->createUniforms.push_back([=]()
				{
					GLuint location = glGetUniformLocation(this->id, name);
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

			/**
			* @brief Program Id.
			*/
			ProgramId id;

			/**
			* @brief Vector of shaders. Contains all shaders used by program.
			*/
			ShaderVector shaders;

			std::vector<std::function<void()>> createUniforms;
		};

		using ProgramList = std::list<Program>;
	}
	/**
	* @brief Shader const iterator.
	*/
	using Program = implementation::ProgramList::iterator;
}