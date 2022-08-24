#pragma once

#include <vector>
#include "ShaderData.hpp"

namespace Engine
{
	using ShaderId = GLuint;
	/**
	* A shader class that store shader id and type.
	*/
	class Shader
	{
	public:
		/**
		* Initialize fields of the class.
		*/
		Shader();

		/**
		* Initialize fields of the class and start shader compilation.
		* @param shaderInfo Contains shader code and shader type.
		*/
		Shader(const ShaderData&);

		/**
		* Shader can't be copied, because it's creating problem with assignment.
		*/
		Shader(const Shader&) = delete;

		/**
		* Swaping shader IDs.
		*/
		Shader(Shader&&);

		/**
		* Delete shader if already exist.
		*/
		~Shader();

		/**
		* Compile shader.
		* @param shaderInfo Contains shader code and shader type.
		*/
		void compile(const ShaderData&);

		/**
		* Delete shader if already exist and initialize fields of the class.
		*/
		void clear();

		/**
		* Get shader ID.
		* @return Shader ID. If equal zero, shader didn't compile yet.
		*/
		const ShaderId getId() const;

	private:
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
}