#include "pickups.h"
#include <time.h>

using namespace pups;
using namespace al;


#pragma region Pickup
pickup::pickup(al::texture* Texture, ItemName itemName, float FoodValue, float Speed):
	m_texture(Texture),
	m_itemName(itemName),
	m_foodValue(FoodValue),
	m_speed(Speed)
{
}

pickup::~pickup()
{
	std::cout<<"deleted pickup type"<<std::endl;
}
#pragma endregion

#pragma region Item

item::item(al::vector Position, pickup* Pickup)
	: m_position(Position),
	  m_pickup(Pickup),
	  m_floating(true)
{
	m_sprite = new al::sprite((Pickup->m_texture));
	m_animation = new animation(m_sprite,1,256,256,false, 1.0f, Pickup->m_itemName);
	m_sprite->setPosition(vector(m_position));
	m_sprite->setOrigin(vector(m_sprite->getSize() / 2));
	m_sprite->setScale(0.5f,0.5f);
	float asdf = m_sprite->getTransformedSize().x;
	m_hitbox = new hitbox(m_position, m_sprite->getTransformedSize(),
		m_sprite->getTransformedSize()/2,
		true);

	m_direction = vector((rand()%200 / 100.0f)-1,(rand()%200 / 100.0f)-1);
}

item::~item()
{
	std::cout<<"aaand its gone"<<std::endl;
}

void item::update(float DeltaTime)
{

	if (m_floating)
	{
		m_position += m_direction * DeltaTime * m_pickup->m_speed;

		stayInWater();
	}
	else
	{
		m_position += m_direction * DeltaTime * 100;
	}

	m_sprite->setPosition(m_position);
	m_hitbox->Position = m_position;
}

void item::draw(al::viewport* Viewport)
{
	Viewport->draw(m_sprite);
}

void item::stayInWater()
{
	float left = 450, right = 1280, top = 500, bottom = 720;
	if (m_position.x < left)
	{
		m_direction.x = -m_direction.x;
		m_position.x = left;
	}
	else if (m_position.x > right)
	{
		m_direction.x = -m_direction.x;
		m_position.x = right;
	}
	if (m_position.y < top)
	{
		m_direction.y = -m_direction.y;
		m_position.y = top;
	}
	else if (m_position.y > bottom)
	{
		m_direction.y = -m_direction.y;
		m_position.y = bottom;
	}
}

#pragma endregion

#pragma region Pickups

pickups::pickups(collision *Collision, nest* Nest, enemy* Enemy, flamingo* Flamingo)
	: m_collision(Collision),
	  m_nest(Nest),
	  m_enemy(Enemy),
	  m_flamingo(Flamingo),
	  m_timer(0)
{
	m_spawnPosition = al::vector(500,500);

	m_texture = new texture("itemsplaceholder.png"); // Texture containing all item animations
	
	pickupList.push_back(new pickup(m_texture, Shoe, 0.0f, 20.0f));
	pickupList.push_back(new pickup(m_texture, Shrimp, 1.0f, 200.0f));
	pickupList.push_back(new pickup(m_texture, Plancton, 1.0f, 60.0f));
}

pickups::~pickups()
{
	std::cout<<"deleting pickups"<<std::endl;
	for (int i = 0; i < pickupList.size(); ++i)
	{
		delete pickupList[i];
		std::cout<<"deleted pickup "<<i+1<<std::endl;
	}

	for (int i = 0; i < itemList.size(); ++i)
	{
		std::cout<<"deleting item "<<i+1<<" ";
		delete itemList[i];
	}
}

void pickups::update(float DeltaTime)
{
	m_timer += DeltaTime;

	for (int i = itemList.size() - 1; i >= 0; --i)
	{
		itemList[i]->update(DeltaTime);

		if (m_collision->HitHead(itemList[i]->m_hitbox))
		{
			std::cout<<"collide "<<i<<std::endl;
			itemList[i]->m_floating = false;
			outOfWater.push_back(itemList[i]);
			itemList.erase(itemList.begin() + i);
		}
	}

	for (int i = outOfWater.size() - 1; i >= 0; --i)
	{
		outOfWater[i]->update(DeltaTime);

		if (m_collision->HitEnemy(outOfWater[i]->m_hitbox))
		{
			std::cout<<"collide enemy "<<i<<std::endl;
			delete outOfWater[i];
			outOfWater.erase(outOfWater.begin() + i);
		}

		switch (m_collision->HitHatchling(outOfWater[i]->m_hitbox))
		{
		case 0:
			std::cout<<"pickup hitting nest"<<std::endl;
			break;
		case 1:
			std::cout<<"pickup hitting hatchling 1"<<std::endl;
			break;
		case 2:
			std::cout<<"pickup hitting hatchling 2"<<std::endl;
			break;
		case 3:
			std::cout<<"pickup hitting hatchling 3"<<std::endl;
			break;
		default:
			std::cout<<"undefined collision to hatchling"<<std::endl;
			break;
		}
	}

	if (m_timer > 2.0f)
	{
		m_timer -= 1.0f;

		if (itemList.size() < 20)
		{
			for (int i = 0; i < 1; ++i)
			{
				int rarity = rand()%100;
				ItemName name;
				if (rarity <25)
				{
					name = Shoe;
				}
				else if (rarity < 50)
				{
					name = Shrimp;
				}
				else if (rarity < 100)
				{
					name = Plancton;
				}

				itemList.push_back(new item(m_spawnPosition,pickupList[name]));
			}
		}
	}
}

void pickups::draw(al::viewport* Viewport)
{
	for (int i = 0; i < itemList.size(); ++i)
	{
		itemList[i]->draw(Viewport);
	}

	for (int i = 0; i < outOfWater.size(); ++i)
	{
		outOfWater[i]->draw(Viewport);
	}
}

void pickups::drawHitBoxes()
{
	for (int i = 0; i < itemList.size(); ++i)
	{
		itemList[i]->m_hitbox->draw(window);
	}
}

#pragma endregion