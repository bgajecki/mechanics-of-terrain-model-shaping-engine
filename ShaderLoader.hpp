#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <sstream>
#include "ShaderData.hpp"

namespace Engine
{
	using ShaderList = std::vector<ShaderData>;

	/**
	* @brief Shaders loading mediator class.
	*/
	class ShaderLoader
	{
	public:
		ShaderLoader() = default;
		~ShaderLoader() = default;

		/**
		* @brief Only one istance of shader loader  object.
		*/
		ShaderLoader(const ShaderLoader&) = delete;

		/**
		* @brief Only one istance of shader loader object.
		*/
		ShaderLoader(ShaderLoader&&) = delete;

		/**
		* @brief Add shader to shader loader list.
		* @param shader Path to shader and shader type.
		* @return Index of the shader.
		*/
		const size_t addShader(const ShaderData&);

		/**
		* @brief Delete shader from shader loader list.
		* @param shader Path to shader and shader type.
		*/
		void deleteShader(const size_t);

		/**
		* Load shader source from path and return it with shader type.
		* @param shaderIndex Index of shader.
		* @return Shader source code and type.
		*/
		const ShaderData& getShaderData(const size_t);

	private:
		/**
		* @brief List of the shaders contains paths and types.
		*/
		ShaderList shaders;
	};
}