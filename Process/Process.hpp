#pragma once

#include "../Entity/EntityManagement.hpp"

namespace Engine
{
	class Process // Abstract class
	{
	public:
		Process(void*);
		Process() = default;
		virtual ~Process() = default;

		void virtual Display() = 0;
		void virtual Special(int, int, int) = 0;
		void virtual OnKeyDown(unsigned char, int, int) = 0;
		void virtual OnMouseClick(int, int, int, int) = 0;
		void virtual Time(int) = 0;
	protected:
		EntityManagement entityManagement;
	};
}