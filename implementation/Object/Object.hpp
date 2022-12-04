#pragma once

#include "Program.hpp"
#include "BasicTypes.hpp"
#include <functional>

namespace engine
{
	namespace implementation
	{
		/**
		* @brief Abstract class of drawable objects.
		*/
		class Object
		{
			///**
			//* @brief Function type for performing settings.
			//*/
			//using SettingsFunction = std::function<void(Object*)>;
		public:
			/**
			* @brief Object constructor.
			*/
			Object();

			/**
			* @brief Object destruktor.
			*/
			~Object() = default;

			/**
			* @brief Drawing primitives.
			*/
			virtual void draw() = 0;

			/**
			* @brief Set position of the object.
			* @param position Position of the object.
			*/
			void setPosition(Position position);
			
			/**
			* @brief Get position of the object.
			* @return Position of the object.
			*/
			Position getPosition() const;
			
			/**
			* @brief Set program of shaders.
			* @param program Program of the shaders.
			*/
			void setProgram(const engine::Program& program);

			/**
			* @brief Get program of shaders.
			* @return Program of the shaders.
			*/
			const engine::Program getProgram() const;

			/**
			* @brief Set primitives type for input data.
			* @param primitivesType Primitives type for input data.
			*/
			void setPrimitivesType(PrimitivesType primitivesType);

			/**
			* @brief Get primitives type for input data.
			* @return Primitives type for input data.
			*/
			PrimitivesType getPrimitivesType() const;

			/**
			* @brief Get model matrix.
			* @return Model matrix.
			*/
			virtual Matrix getModelMatrix() const;

			///**
			//* @brief Set function performing settings for pre draw.
			//* @param preDrwaSettings Function performing settings for pre draw.
			//*/
			//void setPreDrawSettings(SettingsFunction preDrawSettings);

			///**
			//* @brief Set function performing settings for post draw.
			//* @param postDrwaSettings Function performing settings for post draw.
			//*/
			//void setPostDrawSettings(SettingsFunction postDrwaSettings);

			///**
			//* @brief Call function performing settings for pre draw.
			//*/
			//void callPreDrawSettings();

			///**
			//* @brief Call function performing settings for post draw.
			//*/
			//void callPostDrawSettings();

		protected:
			///**
			//* @brief Function performing settings for pre draw.
			//*/
			//SettingsFunction preDrawSettings;

			///**
			//* @brief Function performing settings for post draw.
			//*/
			//SettingsFunction postDrawSettings;

			/**
			* @brief Program of shaders.
			*/
			engine::Program program;

			/**
			* @brief Position of the object.
			*/
			Position position;

			/**
			* @brief Primitives type for input data.
			*/
			PrimitivesType primitivesType;
		};

	}
}
