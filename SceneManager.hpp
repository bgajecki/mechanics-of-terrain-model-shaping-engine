#pragma once

#include "ShaderManager.hpp"
#include "Scene.hpp"

namespace Engine
{

	class SceneManager : public ShaderManager
	{
	public:

		std::vector<Scene> Scenes;
	private:

	};
}