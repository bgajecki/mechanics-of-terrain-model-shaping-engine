#include "ShaderManager.hpp"

namespace Engine
{
	ShaderManager::~ShaderManager()
	{
		this->deletePrograms();
	}

	Program* ShaderManager::createProgram()
	{
		this->programs.push_back(std::make_unique<Program>());
		auto programPointer = this->programs.back().get();
		return programPointer;
	}

	void ShaderManager::deleteProgram(Program* programPointer)
	{
		
		for(auto program = this->programs.begin(); program != this->programs.end();)
			if(programPointer == program->get())
				this->programs.erase(program);
		/*
		for (ProgramsVector::iterator program : this->programs)
			if (programPointer == program->get())
				this->programs.erase(program);
		*/
	}

	void ShaderManager::deletePrograms()
	{
		this->programs.clear();
	}
}