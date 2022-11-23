#include "Object.hpp"

namespace engine
{
	namespace implementation
	{
		Object::Object()
			: position(0.0f, 0.0f, 0.0f)
		{

		}

		void Object::draw()
		{

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

		void Object::setProgram(const engine::Program& program)
		{
			this->program = program;
		}

		const engine::Program Object::getProgram() const
		{
			return this->program;
		}
	}
}
