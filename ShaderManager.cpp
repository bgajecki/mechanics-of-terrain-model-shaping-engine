#include "ShaderManager.hpp"
#include "ShaderManager.hpp"
#include "ShaderManager.hpp"

namespace Engine
{
	template <size_t size>
	ShaderManager<size>::ShaderManager(const ShaderList& list)
		: shaderLoader(list)
	{
		this->programs.fill(std::make_unique());
	}

	template <size_t size>
	ShaderManager<size>::~ShaderManager()
	{
		this->deletePrograms();
	}

	template <size_t size>
	const int ShaderManager<size>::createProgram()
	{
		int index = -1;
		for (int i = 0u; i < this->programs.size(); i++)
		{
			if (!this->programs[i])
			{
				this->programs[i] = std::make_unique<Program>();
				index = i;
			}
		}
		return index;
	}

	template <size_t size>
	void ShaderManager<size>::deleteProgram(const size_t index)
	{
		this->programs[index].reset();
	}

	template <size_t size>
	void ShaderManager<size>::deletePrograms()
	{
		this->programs.clear();
	}

	template<size_t size>
	void ShaderManager<size>::linkProgram(const size_t index)
	{
		this->programs[index]->link();
	}

	template<size_t size>
	void ShaderManager<size>::linkPrograms()
	{
		for (auto& program : this->programs)
			program->link();
	}

	template<size_t size>
	ShaderWeakPointer ShaderManager<size>::assignShader(const size_t shader, const size_t program)
	{
		std::unique_ptr<ShaderData> data = this->shaderLoader.getShaderData(shader);
		ShaderWeakPointer createdShader = this->programs[program]->addShader(data);
		data.reset();
		return createdShader;
	}
}