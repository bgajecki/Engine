#pragma once

#include "./Sublibrary/Entity.hpp"

namespace Engine
{
	typedef std::array<std::unique_ptr<Entity>, constants::Engine::SIZE_OF_ENTITIES_ARRAY> EntityArray;

	class EntityManagement final // Entitys manager
	{
	public:
		EntityManagement() = default;
		~EntityManagement() = default;

		Entity* addEntity();
		Entity* addEntity(const Position_t& pos, const Size_t& size, Texture& txt);
		void deleteEntity(size_t i);

		void Run();
		void DrawsEntitys();
		bool isColision(const Object_t&, const Object_t&);
		bool isColision(Entity*, Entity*);

	private:
		void Motion(std::unique_ptr<Entity>&);
		EntityArray entitys;
	};
}