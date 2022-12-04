#include "Shader.hpp"

namespace engine
{
	namespace implementation
	{
		/**
		* @brief A shader manager class that manages shaders.
		*/
		class ShaderManager
		{
		public:
			/**
			* @brief ShaderManager constructor.
			*/
			ShaderManager() = default;

			/**
			* @brief ShaderManager constructor.
			*/
			~ShaderManager() = default;

			/**
			* @brief Only one istance of ShaderManager object.
			*/
			ShaderManager(const ShaderManager&) = delete;

			/**
			* @brief Only one istance of ShaderManager object.
			*/
			ShaderManager(ShaderManager&&) = delete;

			/**
			* @brief Create shader.
			* @param shaderType Type of the shader.
			* @return Shader iterator.
			*/
			const engine::Shader createShader(ShaderType shaderType);

			/**
			* @brief Create shader.
			* @param shader Type Type of the shader.
			* @param path Path to the shader source code.
			* @return Shader iterator.
			*/
			const engine::Shader createShader(ShaderType type, const ShaderSource& path);

			/**
			* @brief Load shader source code.
			* @param shader Shader iterator.
			* @param path Path to the shader source code.
			* @return Index of the shader.
			*/
			void loadShader(const engine::Shader& shader, const ShaderSource& path);

			/**
			* @brief Delete shader.
			* @param shader Shader iterator.
			*/
			void deleteShader(const engine::Shader shader);

			/**
			* @brief Delete all shaders
			*/
			void deleteShaders();

		protected:

			/**
			* @brief List of the shaders.
			*/
			ShaderList shaders;
		};
	}
}