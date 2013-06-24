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

	for (int i = 0; i < hatchlings.size(); ++i)
		delete hatchlings[i];

	delete head;
	//delete enemy;
}

// Public


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
		hatchlings.push_back(retHitbox);
		break;
	case 1:
		head = retHitbox;
		break;
	case 2:
		enemy = retHitbox;
		break;
	default:
		std::cout<<"Invalid hitbox id, cannot create hitbox"<<std::endl;
		break;
	}

	return retHitbox;
}


bool collision::HitHead(hitbox* ItemHitbox)
{
	if (isCollided(ItemHitbox,head))
	{
		return true;
	}

	return false;
}

int collision::HitHatchling(hitbox* ItemHitbox)
{
	for (int i = 0; i < hatchlings.size(); ++i)
	{
		if (isCollided(ItemHitbox,hatchlings[i]))
			return i+1;
	}

	return 0;
}

bool collision::HitEnemy(hitbox* ItemHitbox)
{
	if (isCollided(ItemHitbox,enemy))
	{
		return true;
	}

	return false;
}

bool collision::isCollided(hitbox *hitbox1,hitbox *hitbox2)
{
	if(hitbox1->hitRect().intersects(hitbox2->hitRect()))
	{
		return true;
	}

	return false;
}