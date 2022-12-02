#pragma once

#include "Program.hpp"
#include "BasicTypes.hpp"
#include <functional>

namespace engine
{
	namespace implementation
	{
		/**
		* @brief A shader manager class that manages shaders in the stage.
		*/
		class Object
		{
			/**
			* @brief A shader manager class that manages shaders in the stage.
			*/
			using SettingsFunction = std::function<void(Object*)>;
		public:
			/**
			* @brief A shader manager class that manages shaders in the stage.
			*/
			Object();

			/**
			* @brief A shader manager class that manages shaders in the stage.
			*/
			~Object() = default;

			/**
			* @brief A shader manager class that manages shaders in the stage.
			*/
			virtual void draw() = 0;

			/**
			* @brief A shader manager class that manages shaders in the stage.
			*/
			void setPosition(Position);
			
			/**
			* @brief A shader manager class that manages shaders in the stage.
			*/
			Position getPosition() const;
			
			/**
			* @brief A shader manager class that manages shaders in the stage.
			*/
			void setProgram(const engine::Program&);

			/**
			* @brief A shader manager class that manages shaders in the stage.
			*/
			const engine::Program getProgram() const;

			/**
			* @brief A shader manager class that manages shaders in the stage.
			*/
			void setPrimitivesType(PrimitivesType);

			/**
			* @brief A shader manager class that manages shaders in the stage.
			*/
			PrimitivesType getPrimitivesType() const;

			/**
			* @brief A shader manager class that manages shaders in the stage.
			*/
			virtual Matrix getModelMatrix() const;

			/**
			* @brief A shader manager class that manages shaders in the stage.
			*/
			//void setPreDrawSettings(SettingsFunction);

			/**
			* @brief A shader manager class that manages shaders in the stage.
			*/
			//void setPostDrawSettings(SettingsFunction);

			/**
			* @brief A shader manager class that manages shaders in the stage.
			*/
			//void callPreDrawSettings();

			/**
			* @brief A shader manager class that manages shaders in the stage.
			*/
			//void callPostDrawSettings();


		protected:
			/**
			* Draw mesh
			*/
			SettingsFunction preDrawSettings;

			/**
			* Draw mesh
			*/
			SettingsFunction postDrawSettings;

			/**
			* Draw mesh
			*/
			engine::Program program;

			/**
			* Draw mesh
			*/
			Position position;

			/**
			* Draw mesh
			*/
			PrimitivesType primitivesType;
		};

	}
}
