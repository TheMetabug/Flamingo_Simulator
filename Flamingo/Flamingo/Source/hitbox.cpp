#include "hitbox.h"

using namespace al;

hitbox::hitbox(al::vector _Position, al::vector _Size, al::vector _Origo, bool _isEnabled)
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

void hitbox::draw(sf::RenderWindow* window)
{
	if (isEnabled)
	{
		sf::RectangleShape box;
		box.setSize(sf::Vector2f(hitRect().width,hitRect().height));
		box.setOutlineColor(sf::Color::Red);
		box.setOutlineThickness(3);
		box.setFillColor(sf::Color::Transparent);
		box.setPosition(hitRect().left, hitRect().top);
		window->draw(box);
	}
	else
	{
		sf::RectangleShape box;
		box.setSize(sf::Vector2f(hitRect().width,hitRect().height));
		box.setOutlineColor(sf::Color::Yellow);
		box.setOutlineThickness(3);
		box.setFillColor(sf::Color::Transparent);
		box.setPosition(hitRect().left, hitRect().top);
		window->draw(box);
	}
}

rectangle hitbox::hitRect()
{
	return rectangle(Position - Origo, Size);
}

collision::collision()
{
	head = NULL;
	enemy = NULL;
}

collision::~collision()
{
	std::cout<<"deleted collision"<<std::endl;
	for (int i = 0; i < hatchlings.size(); ++i)
	{
		delete hatchlings[i];
		std::cout<<"hatchling "<<i<<" deleted"<<std::endl;
	}

	if (!head == NULL) 
	{
		delete head;
		std::cout<<"head hitbox was deleted"<<std::endl;
	}
	else
		std::cout<<"head hitbox was null"<<std::endl;

	if (!enemy == NULL)
	{
		delete enemy;
		std::cout<<"enemy hitbox was deleted"<<std::endl;
	}
	else
		std::cout<<"enemy hitbox was null"<<std::endl;
}

// Public


hitbox* collision::createHitBox(sf::Vector2f position, sf::Vector2u size, sf::Vector2f origo, int id, bool isEnabled)
{
	return createHitBox(position, vector(size.x, size.y), origo, id, isEnabled);
}

hitbox* collision::createHitBox(al::vector position, al::vector size, al::vector origo, int id, bool isEnabled)
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

void collision::DrawHitboxes(sf::RenderWindow* window)
{
	for (int i = 0; i < hatchlings.size(); ++i)
	{
		hatchlings[i]->draw(window);
	}
	if (!head == NULL) 
	{
		head->draw(window);
	}
	if (!enemy == NULL) 
	{
		enemy->draw(window);
	}
}


bool collision::HitHead(hitbox* ItemHitbox)
{
	if (ItemHitbox->isEnabled && head->isEnabled)
	{
		if (isCollided(ItemHitbox,head))
		{
			return true;
		}
	}

	return false;
}

int collision::HitHatchling(hitbox* ItemHitbox)
{
	for (int i = 0; i < hatchlings.size(); ++i)
	{
		if (isCollided(ItemHitbox,hatchlings[i]))
			return i;
	}

	return -1;
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
	if (hitbox1->isEnabled && hitbox2->isEnabled)
	{
		if(hitbox1->hitRect().intersects(hitbox2->hitRect()))
		{
			return true;
		}
	}

	return false;
}