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

	Shader* Program::addShader(const ShaderData& shaderInfo)
	{
		this->shaders.push_back(std::make_shared<Shader>(shaderInfo));
		auto shaderPointer = this->shaders.back().get();
		return shaderPointer;
	}

	Shader* Program::addShader(Shader* shader)
	{
		if (shader->getId() == 0u)
			return nullptr;

		this->shaders.push_back(std::make_shared<Shader>(shader));
		auto shaderPointer = this->shaders.back().get();

		return shaderPointer;
	}

	void Program::deleteShader(Shader* shaderPointer)
	{
		for(auto shader = this->shaders.begin(); shader != this->shaders.end();)
			if(shaderPointer == shader->get())
				this->shaders.erase(shader);

		/*
		for (ShadersVector::iterator shader : this->shaders)
			if (shaderPointer == shader->get())
				this->shaders.erase(shader);
		*/
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
			glAttachShader(this->id, shader->getId());
	}

	void Program::detachShaders()
	{
		for (auto shader : this->shaders)
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