#pragma once

#include "implementation/ShaderManager/ShaderManager.hpp"
#include "implementation/ProgramManager/ProgramManager.hpp"
#include "implementation/Scene/Scene.hpp"

namespace engine
{
	/**
	* @brief A scene manager class that manages scenes. It inherits from ShaderManager and ProgramManager.
	*/
	class SceneManager : public implementation::ShaderManager, public implementation::ProgramManager
	{
		/**
		* @brief Unique pointer to scene object.
		*/
		using ScenePointer = std::unique_ptr<implementation::Scene>;

		/**
		* @brief Vector of unique pointers to scenes.
		*/
		using SceneVector = std::vector<ScenePointer>;
	public:

		/**
		* @brief SceneManager constructor.
		*/
		SceneManager();
		
		/**
		* @brief Create a new scene.
		* @tparam T Type of the scene.
		* @tparam RestOfParameters Types of the rest of parameters.
		* @param restOfParameters Rest of parameters passed to the scene constructor.
		* @return Pointer to the created scene.
		*/
		template<typename T, typename... RestOfParameters>
		T* createScene(RestOfParameters... restOfParameters)
		{
			this->scenes.push_back(std::make_unique<T>(*this, restOfParameters...));
			return dynamic_cast<T*>(this->scenes.back().get());
		}

		/**
		* @brief Drawing objects assigned to the scene.
		*/
		void draw();
		
		/**
		* @brief Set current scene.
		* @param scene Pointer to the scene.
		*/
		void setCurrentScene(implementation::Scene* scene);
		
	protected:
		/**
		* @brief Scenes container.
		*/
		SceneVector scenes;

		/**
		* @brief Current scene.
		*/
		implementation::Scene* currentScene;
	};
}