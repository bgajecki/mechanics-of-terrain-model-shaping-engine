#include <iostream>
#include <string>
#include <array>
#include <fstream>
#include <sstream>
#include <utility>
#include <GL/glew.h> 

#ifdef NDEBUG
#define DEBUG(x) (x)
#else 
#define DEBUG(x)
#endif

namespace Engine
{
	/**
	* @brief Shader source type.
	*/
	using ShaderSource = const char*;

	/**
	* @brief Type for shader type.
	*/
	using ShaderType = GLuint;

	/**
	* @brief List of shaders.
	*/
	enum ShaderList_t
	{
		VERTEX_SHADER
	};

	/**
	* @brief Shader information structure, contains source code and shader type.
	*/
	struct ShaderInfo
	{
		ShaderSource source;
		ShaderType type;
	};

	/**
	* @brief Shaders loading mediator class.
	*/
	
	template <size_t size>
	class Shaders
	{
	public:
		using ShaderList = std::array<ShaderInfo, size>;

		/**
		* @brief Initialization of shader list (paths and types).
		* @param shaderList List of the paths to shaders and shaders types.
		*/
		Shaders(ShaderList);

		/**
		* Initialization of shader list is needed.
		*/
		Shaders() = delete;
		~Shaders() = default;

		/**
		* @brief Only one istance of shaders object.
		*/
		Shaders(const Shaders&) = delete;

		/**
		* @brief Only one istance of shaders object.
		*/
		Shaders(Shaders&&) = delete;

		/**
		* Load shader source from path and return it with shader type.
		* @param shaderIndex Index of shader.
		* @return Shader source code and type.
		*/
		const ShaderInfo& getShaderInfo(const ShaderList_t);

	private:

		/**
		* @brief List of the shaders contains paths and types.
		*/
		ShaderList shaders;
	};
}