#include "pickups.h"
#include <time.h>

#define WATERX 900
#define WATERY 1350
#define WATERR 900
#define WATER_LEFT 400
#define WATER_RIGHT 1240
#define WATER_TOP 430
#define WATER_BOTTOM 680

using namespace pups;
using namespace al;

// Pickup
pickup::pickup(al::texture* Texture, ItemName itemName, float FoodValue, float Speed, float Scale, float Opacity):
	m_texture(Texture),
	m_itemName(itemName),
	m_foodValue(FoodValue),
	m_speed(Speed),
	m_scale(Scale),
	m_opacity(Opacity)
{
}
pickup::~pickup()
{
	std::cout<<"deleted pickup type"<<std::endl;
}

// Item
item::item(al::vector Position, pickup* Pickup)
	: m_position(Position),
	  m_pickup(Pickup),
	  m_state(0)
{
	m_sprite = new al::sprite((Pickup->m_texture));
	m_direction = vector((rand()%200 / 100.0f)-1,(rand()%200 / 100.0f)-1);
	m_animation = new animation(
		m_sprite,
		2,
		256,
		256, 
		((rand()%100))/100.0f + m_direction.getLenght()*m_pickup->m_speed/100.0f, 
		Pickup->m_itemName * 3);
	m_sprite->setPosition(vector(m_position));
	m_sprite->setOrigin(vector(m_sprite->getSize() / 2));
	m_sprite->setScale(m_pickup->m_scale);
	float hitboxSize = 0.9f;
	m_hitbox = new hitbox(m_position, m_sprite->getTransformedSize()*hitboxSize,
		m_sprite->getTransformedSize()*hitboxSize/2,true);
	m_sprite->setLayer(10-290);

	if (m_pickup->m_itemName == Shoe)
	{
		m_animation->ChangeAnimation(Pickup->m_itemName * 3,1);
	}

	m_sprite->setColor(170,210,250,m_pickup->m_opacity*255);
}
item::~item()
{
	std::cout<<"aaand its gone"<<std::endl;
	delete m_sprite;
	delete m_animation;
	delete m_hitbox;
}

bool item::update(float DeltaTime)
{
	switch (m_state)
	{
	case 0:
		m_position += m_direction * DeltaTime * m_pickup->m_speed;

		stayInWater();
		{
			int layer = ((m_position.y - WATER_TOP) / (WATER_BOTTOM - WATER_TOP)) * 275 + 10;
			//if (layer < 40 || layer > 280)
			//	std::cout<<layer<<std::endl;

			m_sprite->setLayer(layer);
			m_sprite->setScale(m_pickup->m_scale * (0.7f + layer / 600.0f));
			m_sprite->setPosition(m_position);
		}
		break;
	case 1:
		m_sprite->setScale(m_pickup->m_scale);
		m_direction = vector(0,0);
		m_sprite->setPosition(m_position);
		m_sprite->setColor(255,255,255,255);
		break;
	case 4:
		m_direction.y += 1000*DeltaTime;
		m_position += m_direction * DeltaTime;
		m_sprite->setPosition(m_position);
		if (m_position.y > 1000)
			return false;
		break;
	case 5:
		m_direction.y += 1000*DeltaTime;
		m_position += m_direction * DeltaTime;
		m_sprite->setPosition(m_position);
		if (m_position.y > 1000)
			return false;
		break;
	default:
		break;
	}

	m_animation->update(DeltaTime);
	m_sprite->setPosition(m_position);
	m_hitbox->Position = m_position;
	return true;
}
void item::draw(al::viewport* Viewport)
{
	Viewport->draw(m_sprite);
}

void item::stayInWater()
{
	vector direction(m_position - vector(WATERX,WATERY));
	if (direction.getLenght() > WATERR)
	{
		m_direction.rotate(180 - 2*(m_direction.getAngle() - direction.getAngle()));
		m_position += (1-(direction.getLenght() / WATERR)) * direction;
	}

	float left = WATER_LEFT;
	float right = WATER_RIGHT;
	//float top = WATER_TOP;
	float bottom = WATER_BOTTOM;
	if (m_position.x < WATER_LEFT)
	{
		m_direction.x = -m_direction.x;
		m_position.x = WATER_LEFT;
	}
	else 
		if (m_position.x > WATER_RIGHT)
	{
		m_direction.x = -m_direction.x;
		m_position.x = WATER_RIGHT;
	}
	//if (m_position.y < top)
	//{
	//	m_direction.y = -m_direction.y;
	//	m_position.y = top;
	//}
	//else 
		if (m_position.y > WATER_BOTTOM)
	{
		m_direction.y = -m_direction.y;
		m_position.y = WATER_BOTTOM;
	}

}

// Pickups
pickups::pickups(collision *Collision, nest* Nest, enemy* Enemy, flamingo* Flamingo, soundLibrary* SoundLibrary)
	: m_collision(Collision),
	  m_nest(Nest),
	  m_enemy(Enemy),
	  m_flamingo(Flamingo),
	  m_timer(0),
	  m_index(-1),
	  m_soundLibrary(SoundLibrary) 
{
	m_spawnPosition = al::vector(1200,600);

	m_texture = new texture("Item_sheet.png"); // Texture containing all item animations

	
	pickupList.push_back(new pickup(m_texture, Plancton, 1.0f, 40.0f, 0.35f, 0.75f));
	pickupList.push_back(new pickup(m_texture, Shrimp, 1.0f, 60.0f, 0.35f, 0.85f));
	pickupList.push_back(new pickup(m_texture, Shoe, -1.0f, 5.0f, 0.35f, 9.0f));
	pickupList.push_back(new pickup(m_texture, Can, -1.0f, 0.0f, 0.35f, 9.0f));
	pickupList.push_back(new pickup(m_texture, Krill, 1.0f, 5.0f, 0.35f, 0.85f));
}
pickups::~pickups()
{
	std::cout<<"deleting pickups"<<std::endl;
	delete m_texture;
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
		if(!itemList[i]->update(DeltaTime)) // update returns false if item needs to be deleted
		{
			deleteItem(i);
			break;
		}

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
			itemList[i]->m_animation->ChangeAnimation(itemList[i]->m_pickup->m_itemName * 3 + 2,1);
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
			{
			int c_item = m_collision->HitHatchling(itemList[i]->m_hitbox);
			switch (c_item)
			{
			case -1:
				if (m_collision->HitEnemy(itemList[i]->m_hitbox))
				{
					m_enemy->eat(itemList[i]->m_pickup->m_foodValue, itemList[i]->m_direction);
					
					if(itemList[i]->m_pickup->m_foodValue <= 0)
					{
						m_nest->happy(DeltaTime);
						m_soundLibrary->m_sounds[9]->play(); // mäisk
						itemList[i]->m_state = 5;
						itemList[i]->m_direction = itemList[i]->m_position - m_enemy->m_enemyBirdPosition;
					}
					else
					{
						m_nest->mad(DeltaTime);
						deleteItem(i);
					}
				}
				break;
			default:
				if (m_nest->eat(DeltaTime, c_item, itemList[i]->m_pickup->m_foodValue))
				{
					deleteItem(i);
					m_soundLibrary->m_sounds[6]->play();
				}
				else
				{
					if(itemList[i]->m_pickup->m_foodValue <= 0)
						m_soundLibrary->m_sounds[12]->play(); // piip

					m_soundLibrary->m_sounds[9]->play(); // mäisk
					itemList[i]->m_state = 5;
					itemList[i]->m_direction = itemList[i]->m_position - m_nest->m_nestPosition;
				}
				break;
			}
			}
			break;
		case 5:
			break;
		default:
			std::cout<<"Undefined item state"<<std::endl;
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
				if (rarity < 20)
				{
					name = Shoe;
				}
				else if (rarity < 40)
				{
					name = Shrimp;
				}
				else if (rarity < 60)
				{
					name = Plancton;
				}
				else if (rarity < 80)
				{
					name = Can;
				}
				else if (rarity < 100)
				{
					name = Krill;
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

	sf::CircleShape water;
	water.setPointCount(100);
	water.setRadius(WATERR);
	water.setOutlineColor(sf::Color::Red);
	water.setOutlineThickness(3);
	water.setFillColor(sf::Color::Transparent);
	water.setPosition(WATERX - WATERR,WATERY - WATERR);
	window->draw(water);
	
	sf::RectangleShape LeftLine;
		LeftLine.setSize(sf::Vector2f(2,WATER_BOTTOM-WATER_TOP));
		LeftLine.setPosition(sf::Vector2f(WATER_LEFT-1,WATER_TOP));
		LeftLine.setFillColor(sf::Color::Red);
		window->draw(LeftLine);
	sf::RectangleShape RightLine;
		RightLine.setSize(sf::Vector2f(2,WATER_BOTTOM-WATER_TOP));
		RightLine.setPosition(sf::Vector2f(WATER_RIGHT-1,WATER_TOP));
		RightLine.setFillColor(sf::Color::Red);
		window->draw(RightLine);
	sf::RectangleShape TopLine;
		TopLine.setSize(sf::Vector2f(WATER_RIGHT-WATER_LEFT,2));
		TopLine.setPosition(sf::Vector2f(WATER_LEFT,WATER_TOP-1));
		TopLine.setFillColor(sf::Color::Red);
		window->draw(TopLine);
	sf::RectangleShape BottomLine;
		BottomLine.setSize(sf::Vector2f(WATER_RIGHT-WATER_LEFT,2));
		BottomLine.setPosition(sf::Vector2f(WATER_LEFT,WATER_BOTTOM-1));
		BottomLine.setFillColor(sf::Color::Red);
		window->draw(BottomLine);
	//sf::IntRect left(WATER_LEFT-1,0,2,WINDOW_HEIGHT);
	//sf::IntRect right(WATER_RIGHT-1,0,2,WINDOW_HEIGHT);
	//sf::IntRect top(0,WATER_TOP-1,WINDOW_WIDTH,2);
	//sf::IntRect bottom(0,WATER_BOTTOM-1,WINDOW_WIDTH,2);

	
}
void pickups::reset()
{
	for (int i = 0; i < itemList.size(); ++i)
	{
		std::cout<<"deleting item "<<i+1<<" ";
		delete itemList[i];
		itemList.clear();
	}
}

void pickups::deleteItem(int i)
{
	delete itemList[i];
	itemList.erase(itemList.begin() + i);
	m_index--;
}
