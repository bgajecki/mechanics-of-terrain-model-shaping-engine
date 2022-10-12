#include "Program.hpp"

namespace engine
{
	namespace implementation
	{
		Program::Program() : id(0u)
		{
			this->id = glCreateProgram();
			this->shaders.reserve(2u); // Minimal size
		}

		Program::Program(Program&& program) noexcept
		{
			std::swap(this->id, program.id);
		}

		Program::~Program()
		{
			this->shaders.clear();
			if (this->id != 0u)
				glDeleteProgram(this->id);
		}

		void Program::link()
		{
			this->attachShaders();
			glLinkProgram(this->id);
			this->checkLinkingStatus();
			this->detachShaders();
		}

		void Program::clear()
		{
			if (this->id != 0u)
			{
				this->shaders.clear();
				glDeleteProgram(this->id);
				this->id = glCreateProgram();
			}
		}

		void Program::addShader(const engine::Shader& shader)
		{
			if (std::find(this->shaders.begin(), this->shaders.end(), shader) == this->shaders.end())
				this->shaders.push_back(shader);
		}

		void Program::deleteShader(const engine::Shader& shader)
		{
			auto iterator = std::find(this->shaders.begin(), this->shaders.end(), shader);
			this->shaders.erase(iterator);
		}

		void Program::deleteShaders()
		{
			this->shaders.clear();
		}

		void Program::use()
		{
			glUseProgram(this->id);
			for (auto createUniform : this->createUniforms)
				createUniform();
		}

		void Program::attachShaders()
		{
			for (auto& shader : this->shaders)
				if (shader->id != 0u)
					glAttachShader(this->id, shader->id);
		}

		void Program::detachShaders()
		{
			for (auto& shader : this->shaders)
				glDetachShader(this->id, shader->id);
		}

		void Program::checkLinkingStatus()
		{
			GLint isLinked = 0;
			glGetProgramiv(this->id, GL_LINK_STATUS, &isLinked);
			if (isLinked == GL_FALSE)
			{
				GLint maxLength = 0;
				glGetProgramiv(this->id, GL_INFO_LOG_LENGTH, &maxLength);

				// The maxLength includes the NULL character
				std::vector<GLchar> errorLog(maxLength);
				glGetProgramInfoLog(this->id, maxLength, &maxLength, &errorLog[0]);

				// Print the error log in DEBUG mode
				std::copy(errorLog.begin(), errorLog.end(), std::ostream_iterator<char>(std::cerr, " "));
			}
		}
	}
}