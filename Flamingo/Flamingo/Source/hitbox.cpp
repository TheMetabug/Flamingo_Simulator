#include "hitbox.h"

hitbox::hitbox(sf::Vector2f _Position, sf::Vector2f _Size, sf::Vector2f _Origo, bool _isEnabled)
{
	Position = _Position;
	Size = _Size;
	isEnabled = _isEnabled;
	Origo = _Origo;

}

hitbox::~hitbox()
{
	std::cout<<"deleted hitbox"<<std::endl;
}

sf::Rect<float> hitbox::hitRect()
{
	return sf::Rect<float>(Position - Origo, Size);
}

collision::collision()
{

}

collision::~collision()
{
	for (int i = 0; i < pickups.size(); ++i)
		delete pickups[i];

	for (int i = 0; i < hatchlings.size(); ++i)
		delete hatchlings[i];

	delete head;
	delete enemy;
}

hitbox* collision::createHitBox(sf::Vector2f position, sf::Vector2u size, sf::Vector2f origo, int id, bool isEnabled)
{
	return createHitBox(position, sf::Vector2f(size.x, size.y), origo, id, isEnabled);
}

hitbox* collision::createHitBox(sf::Vector2f position, sf::Vector2f size, sf::Vector2f origo, int id, bool isEnabled)
{
	hitbox* retHitbox = new hitbox(position, size, origo, isEnabled);

	switch (id)
	{
	case 0:
		pickups.push_back(retHitbox);
		break;
	case 1:
		hatchlings.push_back(retHitbox);
		break;
	case 2:
		head = retHitbox;
		break;
	case 3:
		enemy = retHitbox;
		break;
	}

	return retHitbox;
}

void collision::headPickup()
{
	for (int i = 0; i < pickups.size(); ++i)
	{
		if (isCollided(head, pickups[i]))
		{
			std::cout<< "hit " << i << std::endl;
		}
	}
}

void collision::pickupHatchling()	{}
void collision::pickupEnemy()		{}
void collision::headEnemy()			{}

bool collision::isCollided(hitbox *hitbox1,hitbox *hitbox2)
{
	if(hitbox1->hitRect().intersects(hitbox2->hitRect()))
	{
		return true;
	}

	return false;
}
