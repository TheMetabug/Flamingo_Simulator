#include "hitbox.h"

using namespace al;

hitbox::hitbox(al::vector _Position, al::vector _Size, al::vector _Origo, bool _isEnabled)
{
	Position = _Position;
	Size = _Size;
	isEnabled = _isEnabled;
	Origo = _Origo;
	isRound = true;


}

hitbox::~hitbox()
{
#if _DEBUG
	std::cout<<"deleted hitbox"<<std::endl;
#endif
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
	if(isRound)
	{
		sf::CircleShape circle;
		circle.setRadius(hitRect().width/2);
		circle.setOutlineColor(sf::Color::Blue);
		circle.setOutlineThickness(3);
		circle.setFillColor(sf::Color::Transparent);
		circle.setPosition(hitRect().left, hitRect().top);
		window->draw(circle);
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
#if _DEBUG
	std::cout<<"deleted collision"<<std::endl;
#endif
	for (int i = 0; i < hatchlings.size(); ++i)
	{
		delete hatchlings[i];
#if _DEBUG
		std::cout<<"hatchling "<<i<<" deleted"<<std::endl;
#endif
	}

	if (!head == NULL) 
	{
		delete head;
#if _DEBUG
		std::cout<<"head hitbox was deleted"<<std::endl;
#endif
	}
#if _DEBUG
	else
		std::cout<<"head hitbox was null"<<std::endl;
#endif

	if (!enemy == NULL)
	{
		delete enemy;
#if _DEBUG
		std::cout<<"enemy hitbox was deleted"<<std::endl;
#endif
	}
#if _DEBUG
	else
		std::cout<<"enemy hitbox was null"<<std::endl;
#endif
}

// Public

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
#if _DEBUG
		std::cout<<"Invalid hitbox id, cannot create hitbox"<<std::endl;
#endif
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
			if (hitbox1->isRound && hitbox2->isRound)
			{
				if ((hitbox1->Position - hitbox2->Position).getLenght() <= ((hitbox1->Size.x + hitbox2->Size.x)/2.0f))
				{
					return true;
				}
				else
					return false;
			}
			return true;
		}
	}

	return false;
}