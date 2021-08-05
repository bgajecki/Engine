#include "Entity.hpp"

namespace Engine
{
	Entity::Entity()
		: Sprite()
	{
	}

	Entity::Entity(const Position_t& position, const Size_t& size, Texture texture)
		: Sprite(position, size, texture)
	{
	}

	Motion_t* Entity::addMotion(const Motion_t& motion)
	{
		for (auto& i : this->motions)
		{
			if (!i)
			{
				i.reset(new Motion_t(motion));
				return dynamic_cast<Motion_t*>(i.get());
				break;
			}
		}
		return nullptr;
	}

	void Entity::deleteMotion(size_t i)
	{
		this->motions[i].reset();
	}

	Angel DegreesToRadians(Angel degrees)
	{
		const double M_PI = 3.141592;
		return M_PI * degrees / 180.0;
	}
}

