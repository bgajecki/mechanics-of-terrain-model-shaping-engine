#include "Voxel.hpp"

namespace engine
{
	Voxel::Voxel()
		: active(false), type(0u)
	{

	}

	void Voxel::setType(unsigned type)
	{
		this->type = type;
	}

	unsigned Voxel::getType() const
	{
		return this->type;
	}

	void Voxel::setActive(bool active)
	{
		this->active = active;
	}

	bool Voxel::isActive() const
	{
		return this->active;
	}

	void Voxel::setLifespan(float lifespan)
	{
		if(lifespan > 0.0f)
			this->lifespan = lifespan;
	}

	float Voxel::getLifespan() const
	{
		return this->lifespan;
	}

	void Voxel::decreaseLifespan(float decrase)
	{
		this->lifespan -= decrase;
		if (this->lifespan <= 0.0f)
			this->active = false;
	}

}