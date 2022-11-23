#include "Shader.hpp"

namespace engine
{
	namespace implementation
	{
		/**
		* @brief Shaders loading mediator class.
		*/
		class ShaderManager
		{
		public:
			ShaderManager() = default;
			~ShaderManager() = default;

			/**
			* @brief Only one istance of shader loader  object.
			*/
			ShaderManager(const ShaderManager&) = delete;

			/**
			* @brief Only one istance of shader loader object.
			*/
			ShaderManager(ShaderManager&&) = delete;

			/**
			* @brief Add shader to shader loader list.
			* @param shader Path to shader and shader type.
			* @return Index of the shader.
			*/
			const engine::Shader createShader(ShaderType);

			/**
			* @brief Add shader to shader loader list.
			* @param shader Path to shader and shader type.
			* @return Index of the shader.
			*/
			const engine::Shader createShader(ShaderType type, const ShaderSource& path);

			/**
			* @brief Add shader to shader loader list.
			* @param shader Path to shader and shader type.
			* @return Index of the shader.
			*/
			void loadShader(const engine::Shader&, const ShaderSource& path);

			/**
			* @brief Delete shader from shader loader list.
			* @param shader Path to shader and shader type.
			*/
			void deleteShader(const engine::Shader);

			/**
			* @brief Add shader to shader loader list.
			* @param shader Path to shader and shader type.
			* @return Index of the shader.
			*/
			void deleteShaders();

		protected:


			/**
			* @brief List of the shaders contains paths and types.
			*/
			ShaderList shaders;
		};
	}
}