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
		* @brief Shader id type.
		*/
		using ShaderId = GLuint;

		/**
		* A shader class that store shader id and type.
		*/
		class Shader final
		{
			friend class Program;
		public:
			/**
			* Initialize fields of the class.
			*/
			Shader() = delete;
			/**
			* Initialize fields of the class.
			*/
			Shader(ShaderType);

			/**
			* Initialize fields of the class.
			*/
			Shader(ShaderType type, const ShaderSource& path);

			/**
			* Shader can't be copied, because it's creating problem with assignment.
			*/
			Shader(const Shader&) = delete;

			/**
			* Swaping shader IDs.
			*/
			Shader(Shader&&) noexcept;

			/**
			* Delete shader if already exist.
			*/
			~Shader();

			/**
			* Compile shader.
			* @param shaderInfo Contains shader code and shader type.
			*/
			void compile(const ShaderSource&);

			/**
			* Delete shader if already exist and initialize fields of the class.
			*/
			void clear();

		private:
			/**
			* Load shader source from path and return it with shader type.
			* @param shaderIndex Index of shader.
			* @return Shader source code and type.
			*/
			const ShaderSource getShaderSource(const ShaderSource&);

			/**
			* Check compilation status of the shader.
			*/
			void checkCompilationStatus();

			/**
			* Shader ID.
			*/
			ShaderId id;

			/**
			* Shader type.
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