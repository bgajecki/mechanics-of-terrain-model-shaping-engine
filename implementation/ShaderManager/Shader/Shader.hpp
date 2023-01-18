#pragma once

#include <iostream>
#include <sstream>
#include <fstream>
#include <iterator>
#include <numeric>
#include <list>
#include <vector>
#include <string>
#include <GL/glew.h>

namespace engine
{
	namespace implementation
	{
		/**
		* @brief Shader source type.
		*/
		using ShaderSource = std::string;

		/**
		* @brief Type for shader type.
		*/
		using ShaderType = GLuint;

		/**
		* @brief Shader ID type.
		*/
		using ShaderId = GLuint;

		/**
		* @brief A shader class that store shader ID and type. Delivers funcionality of loading
		*/
		class Shader final
		{
			/**
			* @brief Program class need access to private fields of the Shader class.
			*/
			friend class Program;
		public:
			/**
			* @brief Initialize shader.
			*/
			Shader() = delete;

			/**
			* @brief Initialize shader.
			* @param shaderType Type of the shader.
			*/
			Shader(ShaderType shaderType);

			/**
			* @brief Initialize shader.
			* @param shaderType Type of the shader.
			* @param path Path to the shader source code.
			*/
			Shader(ShaderType type, const ShaderSource& path);

			/**
			* @brief Shader can't be copied, because it's creating problem with assignment.
			*/
			Shader(const Shader&) = delete;

			/**
			* @brief Swaping shader IDs.
			*/
			Shader(Shader&&) noexcept;

			/**
			* @brief Delete shader if already exist.
			*/
			~Shader();

			/**
			* @brief Compile shader.
			* @param shaderInfo Contains shader code and shader type.
			*/
			void compile(const ShaderSource& shaderInfo);

			/**
			* @brief Delete shader if already exist and initialize fields of the class.
			*/
			void clear();

		private:
			/**
			* @brief Load shader source from path and return it.
			* @param path Path to the shader source code.
			* @return Shader source code.
			*/
			const ShaderSource getShaderSource(const ShaderSource& path);

			/**
			* @brief Check compilation status of the shader.
			*/
			void checkCompilationStatus();

			/**
			* @brief Shader ID.
			*/
			ShaderId id;

			/**
			* @brief Shader type.
			*/
			ShaderType type;
		};

		/**
		* @brief List of shaders.
		*/
		using ShaderList = std::list<Shader>;
	}
	/**
	* @brief Shader const iterator.
	*/
	using Shader = implementation::ShaderList::iterator;
}