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
	  m_state(0)
{
	m_sprite = new al::sprite((Pickup->m_texture));
	m_animation = new animation(m_sprite,1,256,256,false, 1.0f, Pickup->m_itemName);
	m_sprite->setPosition(vector(m_position));
	m_sprite->setOrigin(vector(m_sprite->getSize() / 2));
	m_sprite->setScale(0.35f,0.35f);
	float asdf = m_sprite->getTransformedSize().x;
	m_hitbox = new hitbox(m_position, m_sprite->getTransformedSize()/2,
		m_sprite->getTransformedSize()/4,true);
	m_sprite->setLayer(10-290);

	m_direction = vector((rand()%200 / 100.0f)-1,(rand()%200 / 100.0f)-1);
}

item::~item()
{
	std::cout<<"aaand its gone"<<std::endl;
}

void item::update(float DeltaTime)
{
	switch (m_state)
	{
	case 0:
		m_position += m_direction * DeltaTime * m_pickup->m_speed;

		stayInWater();
		break;
	case 1:
		m_direction = vector(0,0);
		break;
	case 4:
		m_direction.y += 3;
		m_position += m_direction * DeltaTime;
		break;
	default:
		break;
	}

	m_animation->update(DeltaTime);
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
	  m_timer(0),
	  m_index(-1)
{
	m_spawnPosition = al::vector(1200,600);

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

		switch (itemList[i]->m_state)
		{
		case 0: // floating around
			if (m_collision->head->isEnabled)
			{
				if (m_collision->HitHead(itemList[i]->m_hitbox) && !m_flamingo->m_hasFood)
				{
					std::cout<<"collide "<<i<<std::endl;
					if(m_index >= 0)
					{
						if(((itemList[i]->m_position - m_flamingo->m_headPosition).getLenght()) < 
							((itemList[m_index]->m_position - m_flamingo->m_headPosition).getLenght()))
						
							m_index = i;
					}
					else
					{
						m_index = i;
					}
				}
			}
			break;

		case 1: // in mouth
			itemList[i]->m_position = m_flamingo->m_headHitbox->Position;
			if (m_flamingo->m_drag == 0)
			{
				itemList[i]->m_state = 2;
			}
			break;

		case 2: // waiting for release
			itemList[i]->m_position = m_flamingo->m_headHitbox->Position;
			if (m_flamingo->m_drag == 2) // just released
			{
				itemList[i]->m_direction = m_flamingo->m_direction * (1+m_flamingo->m_throwMultiplier); // take direction
				itemList[i]->m_state = 3;
			}
			break;

		case 3: // wait till head stops
			if (m_flamingo->m_drag == 3)
			{
				itemList[i]->m_state = 4;
				m_flamingo->m_hasFood = false;
			}
			else
			{
				itemList[i]->m_position = m_flamingo->m_headHitbox->Position;
			}
			break;

		case 4: // flying
			int c_item = m_collision->HitHatchling(itemList[i]->m_hitbox);
			switch (c_item)
			{
			case -1:
				if (m_collision->HitEnemy(itemList[i]->m_hitbox))
				{
					m_enemy->eat(itemList[i]->m_pickup->m_foodValue, itemList[i]->m_direction);
					
					if(itemList[i]->m_pickup->m_foodValue == 0)
						m_nest->happy(DeltaTime);
					else
						m_nest->mad(DeltaTime);
					deleteItem(i); // delete in the end
				}
				break;
			default:
				m_nest->eat(DeltaTime, c_item, itemList[i]->m_pickup->m_foodValue);
				deleteItem(i); // delete in the end
				break;
			}
			break;
		}

	}

	if (m_index >= 0)
	{
		itemList[m_index]->m_state = 1;
		m_flamingo->m_hasFood = true;
		m_index = -1;
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
}

void pickups::drawHitBoxes(sf::RenderWindow* window)
{
	for (int i = 0; i < itemList.size(); ++i)
	{
		itemList[i]->m_hitbox->draw(window);
	}
}

void pickups::deleteItem(int i)
{
	delete itemList[i];
	itemList.erase(itemList.begin() + i);
	m_index--;
}

#pragma endregion
