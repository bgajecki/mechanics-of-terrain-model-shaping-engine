#include "Shader.hpp"

namespace Engine
{
	Shader::Shader() : id(0u), type(0u)
	{
	}

	Shader::Shader(const ShaderInfo& shaderInfo) : Shader()
	{
		this->Compile(shaderInfo);
	}

	Shader::Shader(Shader&& shader)
	{
		std::swap(this->id, shader.id);
		std::swap(this->type, shader.type);
	}

	Shader::~Shader()
	{
		if (this->id != 0u)
			glDeleteShader(this->id);
	}

	void Shader::compile(const ShaderInfo& shaderInfo)
	{
		this->type = shaderInfo.type;
		this->id = glCreateShader(this->type);
		glShaderSource(this->id, 1, &shaderInfo.source, NULL);
		glCompileShader(this->id);
		this->checkCompilationStatus();
	}

	void Shader::clear()
	{
		if (this->id != 0u)
		{
			glDeleteShader(this->id);
			this->id = 0u;
			this->type = 0u;
		}
	}

	const ShaderId Shader::getId() const
	{
		return this->id;
	}

	void Shader::checkCompilationStatus()
	{
		GLint isCompiled = 0;
		glGetShaderiv(this->id, GL_COMPILE_STATUS, &isCompiled);
		if (isCompiled == GL_FALSE)
		{
			GLint maxLength = 0;
			glGetShaderiv(this->id, GL_INFO_LOG_LENGTH, &maxLength);

			// The maxLength includes the NULL character
			std::vector<GLchar> errorLog(maxLength);
			glGetShaderInfoLog(this->id, maxLength, &maxLength, &errorLog[0]);

			// Print the error log in DEBUG mode
			DEBUG(std::copy(errorLog.begin(), errorLog.end(), std::ostream_iterator<char>(std::cerr, " "));)

			this->clear(); // Don't leak the shader.
		}
	}
}