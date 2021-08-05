#pragma once

namespace Engine
{
	struct Position_t // Position structure
	{
		Position_t() = default;
		~Position_t() = default;

		Position_t(double x, double y)
		{
			this->x = x;
			this->y = y;
		}

		double x, y;
	};
}