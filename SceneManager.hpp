#pragma once

#include "implementation/ShaderManager/ShaderManager.hpp"
#include "implementation/ProgramManager/ProgramManager.hpp"
#include "implementation/Scene/Scene.hpp"

namespace engine
{
	class SceneManager : public implementation::ShaderManager, public implementation::ProgramManager
	{
		/**
		* @brief Unique pointer to scene object.
		*/
		using ScenePointer = std::unique_ptr<implementation::Scene>;

		/**
		* @brief Vector of unique pointers to meshes objects.
		*/
		using SceneVector = std::vector<ScenePointer>;
	public:

		/**
		* Draw mesh
		*/
		SceneManager();
		
		/**
		* Draw mesh
		*/
		template<typename T, typename... RestOfParameters>
		T* createScene(RestOfParameters... restOfParameters)
		{
			this->scenes.push_back(std::make_unique<T>(*this, restOfParameters...));
			return dynamic_cast<T*>(this->scenes.back().get());
		}

		/**
		* Draw mesh
		*/
		void draw();
		
		/**
		* Draw mesh
		*/
		void setCurrentScene(implementation::Scene*);
		
	protected:
		/**
		* Draw mesh
		*/
		SceneVector scenes;

		/**
		* Draw mesh
		*/
		implementation::Scene* currentScene;
	};
}