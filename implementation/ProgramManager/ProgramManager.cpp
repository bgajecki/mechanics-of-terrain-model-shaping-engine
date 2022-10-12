#include "ProgramManager.hpp"

namespace engine
{
	namespace implementation
	{
		const engine::Program ProgramManager::createProgram()
		{
			this->programs.push_back(Program::Program());
			return --this->programs.end();
		}

		void ProgramManager::deleteProgram(const engine::Program& program)
		{
			this->programs.erase(program);
		}

		void ProgramManager::deletePrograms()
		{
			this->programs.clear();
		}

		void ProgramManager::linkProgram(const engine::Program& program)
		{
			auto iterator = this->programs.begin();
			for (; iterator != this->programs.end(); iterator++)
				if (iterator == program)
					break;

			if (iterator != this->programs.end())
				iterator->link();
		}

		void ProgramManager::linkPrograms()
		{
			for (auto& program : this->programs)
				program.link();
		}

		void ProgramManager::assignShader(const engine::Shader& shader, const engine::Program& program)
		{
			auto iterator = this->programs.begin();
			for (; iterator != this->programs.end(); iterator++)
				if (iterator == program)
					break;

			if (iterator != this->programs.end())
				iterator->addShader(shader);
		}
	}
}