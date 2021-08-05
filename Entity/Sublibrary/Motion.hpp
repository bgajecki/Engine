#pragma once
namespace Engine
{
	typedef double Angel;
	typedef Angel Direction; // The direction is specified as an angle in radians
	typedef double Speed;
	typedef double Acceleration;

	struct Motion_t // Motion structure
	{
		Motion_t() = default;
		~Motion_t() = default;

		Motion_t(Direction direction, Speed speed, Acceleration acceleration)
		{
			this->direction = direction;
			this->speed = speed;
			this->acceleration = acceleration;
		}

		Direction direction;
		Speed speed;
		Acceleration acceleration;
	};
}