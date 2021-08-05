#pragma once

#include <memory>
#include <array>
#include <functional>
#include "Sprite.hpp"
#include "Motion.hpp"
#include "Constants.hpp"

namespace Engine
{
	typedef std::array<std::shared_ptr<Motion_t>, constants::Engine::SIZE_OF_MOTIONS_ARRAY> MotionArray;
	// typedef std::array<Texture, constants::Engine::SIZE_OF_ANIMATIONS_ARRAY> AnimationArray;	

	class Entity final : public Sprite // Entities/Objects
	{

	public:
		Entity();
		Entity(const Position_t&, const Size_t&, Texture);
		~Entity() = default;

		Motion_t* addMotion(const Motion_t&);
		void deleteMotion(size_t);

		MotionArray& getMotions() { return this->motions; }
		std::function<void(std::unique_ptr<Entity>&,
			const std::array<std::unique_ptr<Entity>, constants::Engine::SIZE_OF_ENTITIES_ARRAY>&,
			unsigned)> colision; // Motion method checking colision and trigger reaction on it
		std::function<void(std::unique_ptr<Entity>&)> timmer; // Animation method trigger at the right time
	protected:
		MotionArray motions;
		// AnimationArray animations;
	};

	typedef std::function<void(std::unique_ptr<Entity>&,
		const std::array<std::unique_ptr<Entity>, constants::Engine::SIZE_OF_ENTITIES_ARRAY>&,
		unsigned)> ColisionFunction;

	typedef std::function<void(std::unique_ptr<Entity>&)> TimmerFunction;

	Angel DegreesToRadians(Angel degrees);
}