#include "Program.hpp"

namespace Engine
{
	Program::Program() : id(0u)
	{
		this->id = glCreateProgram();
		this->shaders.reserve(2u); // Minimal size
	}


	Program::Program(Program&& program)
	{
		std::swap(this->id, program.id);
	}

	Program::~Program()
	{
		this->shaders.clear();
		if (this->id != 0u)
			glDeleteProgram(this->id);
	}

	void Program::link(const ShaderData& shaderInfo)
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

	ShaderWeakPointer Program::addShader(const ShaderData& shaderInfo)
	{
		this->shaders.push_back(std::make_shared<Shader>(shaderInfo));
		ShaderWeakPointer shader = this->shaders.back();
		return shader;
	}

	ShaderWeakPointer Program::addShader(ShaderWeakPointer shader)
	{
		if (ShaderSharedPointer shaderSharedPointer = shader.lock())
			this->shaders.push_back(std::move(shaderSharedPointer));
		return shader;
	}

	void Program::deleteShader(ShaderWeakPointer shader)
	{
		for(auto i = this->shaders.begin(); i != this->shaders.end();)
			if(*i == shader.lock())
				this->shaders.erase(i);
	}

	void Program::deleteShaders()
	{
		this->shaders.clear();
	}

	void Program::use()
	{
		glUseProgram(this->id);
	}

	const ProgramId Program::getId() const
	{
		return this->id;
	}

	void Program::attachShaders()
	{
		for (auto& shader : this->shaders)
			if(shader->getId() != 0u)
				glAttachShader(this->id, shader->getId());
	}

	void Program::detachShaders()
	{
		for (auto& shader : this->shaders)
			glDetachShader(this->id, shader->getId());
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
			DEBUG(std::copy(errorLog.begin(), errorLog.end(), std::ostream_iterator<char>(std::cerr, " "));)
		}
	}
}