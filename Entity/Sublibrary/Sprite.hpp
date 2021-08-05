#pragma once

#include "Object.hpp"
#include "Texture.hpp"

namespace Engine
{
	class Sprite // Just sprite
	{
	public:
		Sprite();
		Sprite(const Position_t&, const Size_t&, Texture);
		virtual ~Sprite() = default;

		void setPosition(const Position_t&);
		void setSize(const Size_t&);
		void setTexture(Texture);
		void setRect(const Position_t&, const Size_t&);

		const Position_t getPosition() const { return this->obj.pos; }
		const Size_t getSize() const { return this->obj.size; }
		const Object_t getObject() const { return this->obj; }
		const Texture getTexture() const { return this->texture; }

		void Draw();
	protected:

		Texture texture;
		Object_t obj;
	};
}