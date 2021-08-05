#include "EntityManagement.hpp"

namespace Engine
{

	Entity* EntityManagement::addEntity()
	{
		for (auto& i : this->entitys)
		{
			if (!i)
			{
				i.reset(new Entity);
				return dynamic_cast<Entity*>(i.get());
				break;
			}
		}
		return nullptr;
	}

	Entity* EntityManagement::addEntity(const Position_t& pos, const Size_t& size, Texture& txt)
	{
		for (auto& i : this->entitys)
		{
			if (!i)
			{
				i.reset(new Entity(pos, size, txt));
				return dynamic_cast<Entity*>(i.get());
				break;
			}
		}
		return nullptr;
	}

	void EntityManagement::deleteEntity(size_t i)
	{
		this->entitys[i].reset();
	}


	void EntityManagement::Run()
	{
		for (auto& i : this->entitys)
		{
			if (i)
			{
				this->Motion(i);
				if (i->timmer)
					i->timmer(i);
			}
		}
	}

	void EntityManagement::DrawsEntitys()
	{
		for (auto& i : this->entitys)
			if (i)
				i->Draw();
	}

	bool EntityManagement::isColision(const Object_t& o1, const Object_t& o2)
	{
		if (o1.pos.x < o2.pos.x + o2.size.width && o1.pos.x + o1.size.width > o2.pos.x
			&& o1.pos.y < o2.pos.y + o2.size.height && o1.pos.y + o1.size.height > o2.pos.y)
			return true;
		else
			return false;
	}

	bool EntityManagement::isColision(Entity* e1, Entity* e2)
	{
		return this->isColision(e1->getObject(), e2->getObject());
	}

	void EntityManagement::Motion(std::unique_ptr<Entity>& ptr)
	{
		auto motions = ptr->getMotions();
		Position_t pos = ptr->getPosition();
		Size_t size = ptr->getSize();

		for (unsigned i = 0u; i < motions.size(); i++)
		{
			if (motions[i])
			{
				Speed speed = motions[i]->speed;
				Direction direction = motions[i]->direction;
				Acceleration acceleration = motions[i]->acceleration;

				pos.x += speed * cos(direction); // (x,y) => (Speed * cos(angel), Speed * sin(angel))
				pos.y += speed * sin(direction);
				/*
				if (pos.x + size.width > 1.0 || pos.x < -1.0 ||
					pos.y + size.height > 1.0 || pos.y < -1.0)
					ptr->deleteMotion(i);
				else
					ptr->setPosition(pos);

				if (speed + acceleration < 0.0)
					ptr->deleteMotion(i);
				else
				*/
				ptr->setPosition(pos);
				motions[i]->speed = speed + acceleration;

				if(ptr->colision)
					ptr->colision(ptr, this->entitys, i); // Collision checking
			}
		}
	}
}
