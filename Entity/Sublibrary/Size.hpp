#pragma once

namespace Engine
{
	struct Size_t // Size structure
	{
		Size_t() = default;
		~Size_t() = default;

		Size_t(double width, double height)
		{
			this->width = width;
			this->height = height;
		}

		double width, height;
	};
}