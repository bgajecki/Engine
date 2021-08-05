#include "Sprite.hpp"
#include <iostream>
namespace Engine
{
	Sprite::Sprite()
	{
		this->texture = 0;
	}

	Sprite::Sprite(const Position_t& position, const Size_t& size, Texture texture)
	{
		this->obj.pos = position;
		this->obj.size = size;
		this->texture = texture;
	}

	void Sprite::setPosition(const Position_t& position)
	{
		this->obj.pos = position;
	}

	void Sprite::setSize(const Size_t& size)
	{
		this->obj.size = size;
	}

	void Sprite::setTexture(Texture texture)
	{
 		this->texture = texture;
	}

	void Sprite::setRect(const Position_t& position, const Size_t& size)
	{
		this->obj.pos = position;
		this->obj.size = size;
	}

	void Sprite::Draw()
	{
		glBindTexture(GL_TEXTURE_2D, this->texture);
		glBegin(GL_QUADS);
		glTexCoord3d(0.0, 0.0, 0.0);
		glVertex3d(this->obj.pos.x, this->obj.pos.y, 0.0);
		glTexCoord3d(0.0, 1.0, 0.0);
		glVertex3d(this->obj.pos.x, this->obj.pos.y + this->obj.size.height, 0.0);
		glTexCoord3d(1.0, 1.0, 0.0);
		glVertex3d(this->obj.pos.x + this->obj.size.width, this->obj.pos.y + this->obj.size.height, 0.0);
		glTexCoord3d(1.0, 0.0, 0.0);
		glVertex3d(this->obj.pos.x + this->obj.size.width, this->obj.pos.y, 0.0);
		glEnd();
	}
}
