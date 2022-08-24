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
	* @brief Shader data structure, contains the source code and the shader type.
	*/
	struct ShaderData
	{
		ShaderSource source;
		ShaderType type;
	};

}