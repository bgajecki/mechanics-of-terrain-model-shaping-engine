#include "Object.hpp"

namespace engine
{
	namespace implementation
	{
		Object::Object()
			: position(0.0f, 0.0f, 0.0f), primitivesType(GL_TRIANGLES)
		{
			//this->preDrawSettings = [](auto) { };
			//this->postDrawSettings = [](auto) { };
		}

		void Object::setPosition(Position position)
		{
			this->position = position;
		}

		Position Object::getPosition() const
		{
			return this->position;
		}

		Matrix Object::getModelMatrix() const
		{
			Matrix model = Matrix(1.0f);
			model = glm::translate(model, this->position);
			return model;
		}

		//void Object::setPreDrawSettings(SettingsFunction function)
		//{
		//	this->preDrawSettings = function;
		//}

		//void Object::setPostDrawSettings(SettingsFunction function)
		//{
		//	this->postDrawSettings = function;
		//}

		//void Object::callPreDrawSettings()
		//{
		//	this->preDrawSettings(this);
		//}

		//void Object::callPostDrawSettings()
		//{
		//	this->postDrawSettings(this);
		//}

		void Object::setProgram(const engine::Program& program)
		{
			this->program = program;
		}

		const engine::Program Object::getProgram() const
		{
			return this->program;
		}

		void Object::setPrimitivesType(PrimitivesType primitivesType)
		{
			this->primitivesType = primitivesType;
		}

		PrimitivesType Object::getPrimitivesType() const
		{
			return this->primitivesType;
		}
	}
}
