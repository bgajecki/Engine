#pragma once

#include "Position.hpp"
#include "Size.hpp"

namespace Engine
{
	struct Object_t // Object structure
	{
		Object_t() = default;
		~Object_t() = default;

		Object_t(Position_t pos, Size_t size)
		{
			this->pos = pos;
			this->size = size;
		}

		Position_t pos;
		Size_t size;
	};
}