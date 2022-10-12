#include "Shader.hpp"

namespace engine
{
	namespace implementation
	{
		Shader::Shader(const ShaderType type)
			: id(0u), type(type)
		{
			this->id = glCreateShader(this->type);
		}

		Shader::Shader(const ShaderType type, const ShaderSource& path)
			: Shader(type)
		{
			this->compile(path);
		}

		Shader::Shader(Shader&& shader) noexcept
		{
			std::swap(this->id, shader.id);
			std::swap(this->type, shader.type);
		}

		Shader::~Shader()
		{
			if (this->id != 0u)
				glDeleteShader(this->id);
		}

		void Shader::compile(const ShaderSource& path)
		{
			const auto& temp = this->getShaderSource(path);
			const char* src = temp.c_str();
			glShaderSource(this->id, 1, &src, NULL);
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

		const ShaderSource Shader::getShaderSource(const ShaderSource& path)
		{
			std::ifstream file(path);
			std::stringstream stream;

			if (!file.is_open())
			{
				std::cerr << "Could not read file " << path << ". File does not exist." << std::endl;
				stream << "";
			}
			else
			{
				stream << file.rdbuf();
			}

			ShaderSource source = stream.str();
			return source;
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
				std::copy(errorLog.begin(), errorLog.end(), std::ostream_iterator<char>(std::cerr, " "));

				this->clear(); // Don't leak the shader.
			}
		}
	}
}