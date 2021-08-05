#pragma once

namespace constants
{
	namespace Engine
	{
		constexpr size_t SIZE_OF_MOTIONS_ARRAY = 3u; // Player move(left and right), jump, repulse
		constexpr size_t SIZE_OF_ENTITIES_ARRAY = 200u; // I limit the number of entities
		constexpr size_t SIZE_OF_PROCESS_ARRAY = 6u; // Menus, scenes, game
		
		constexpr uint8_t SPACEBAR = 0x20; // Space key code
		constexpr uint8_t ESCAPE = 0x1B; // Escape key code
	}
}