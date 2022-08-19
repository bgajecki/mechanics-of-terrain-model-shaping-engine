#include "Program.hpp"

namespace Engine
{
	Program::Program() : id(0u)
	{
		this->id = glCreateProgram();
		this->shaders.assign(2u); // Minimal size
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

	void Program::link(const ShaderInfo& shaderInfo)
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

	Shader* Program::addShader(const ShaderInfo& shaderInfo)
	{
		this->shaders.push_back(std::make_shared<Shader>(shaderInfo));
		auto shaderPointer = this->shaders.back();
		return shaderPointer;
	}

	Shader* Program::addShader(Shader* shader)
	{
		if (shader->getId() == 0u)
			return std::nullptr;

		this->shaders.push_back(std::make_shared<Shader>(shader));
		auto shaderPointer = this->shaders.back().get();

		return shaderPointer;
	}

	void Program::deleteShader(Shader* shaderPointer)
	{
		/*
		for(auto shader = this->shaders.begin(); shader != this->shaders.end();)
			if(shaderPointer == shader->get())
				this->shaders.erase(shader);
		*/
		for (ShadersVector::iterator shader : this->shaders)
			if (shaderPointer == shader->get())
				this->shaders.erase(shader);
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
		for (auto shader : this->shaders)
			glAttachShader(shader->getId());
	}

	void Program::detachShaders()
	{
		for (auto shader : this->shaders)
			glDetachShader(shader->getId());
	}

	void Program::checkLinkingStatus()
	{
		GLint isLinked = 0;
		glGetProgramiv(program, GL_LINK_STATUS, &isLinked);
		if (isLinked == GL_FALSE)
		{
			GLint maxLength = 0;
			glGetProgramiv(program, GL_INFO_LOG_LENGTH, &maxLength);

			// The maxLength includes the NULL character
			std::vector<GLchar> errorLog(maxLength);
			glGetProgramInfoLog(program, maxLength, &maxLength, &errorLog[0]);

			// Print the error log in DEBUG mode
			DEBUG(std::copy(errorLog.begin(), errorLog.end(), std::ostream_iterator<char>(std::cerr, " "));)
		}
	}
}