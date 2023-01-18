#include "SceneManager.hpp"

namespace engine
{
	SceneManager::SceneManager()
		: currentScene(nullptr)
	{
	}

	void SceneManager::draw()
	{
		if (this->currentScene == nullptr)
			return;

		for (auto i = this->programs.begin(); i != this->programs.end(); i++)
		{	
			i->use();
			this->currentScene->draw(i);
		}
		glUseProgram(0u);
	}

	void SceneManager::setCurrentScene(implementation::Scene* scene)
	{
		this->currentScene = scene;
	}
}