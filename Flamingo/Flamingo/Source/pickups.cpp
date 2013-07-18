#include "pickups.h"
#include <time.h>


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
#if _DEBUG
	std::cout<<"deleted pickup type"<<std::endl;
#endif
}

// Item
item::item(al::vector Position, pickup* Pickup)
	: m_position(Position),
	  m_pickup(Pickup),
	  m_state(-1),
	  m_timer(0)
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
	m_sprite->setPosition(m_position);
	m_sprite->setOrigin((m_sprite->getSize() / 2));
	m_sprite->setScale(m_pickup->m_scale);
	float hitboxSize = 0.9f;
	m_hitbox = new hitbox(m_position, m_sprite->getTransformedSize()*hitboxSize,
		m_sprite->getTransformedSize()*hitboxSize/2,false);
	m_sprite->setLayer(10-290);

	if (m_pickup->m_itemName == Shoe)
	{
		m_animation->ChangeAnimation(Pickup->m_itemName * 3,1);
	}

	m_sprite->setColor(170,210,250,0);
}
item::~item()
{
#if _DEBUG
	std::cout<<"aaand its gone"<<std::endl;
#endif
	delete m_sprite;
	delete m_animation;
	delete m_hitbox;
}

bool item::update(float DeltaTime)
{
	switch (m_state)
	{
	case -1:
		m_timer += DeltaTime;
		m_sprite->setColor(170,210,250, m_timer * m_pickup->m_opacity*255);
		if (m_timer > 0.5)
		{
			m_hitbox->isEnabled = true;
		}
		if (m_timer > 1)
		{
			m_sprite->setColor(170,210,250,m_pickup->m_opacity*255);
			m_state = 0;
		}
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
	pickupList.push_back(new pickup(m_texture, Shoe, -1.0f, 5.0f, 0.35f, 0.9f));
	pickupList.push_back(new pickup(m_texture, Can, -1.0f, 0.0f, 0.35f, 0.9f));
	pickupList.push_back(new pickup(m_texture, Krill, 1.0f, 5.0f, 0.35f, 0.85f));
}
pickups::~pickups()
{
#if _DEBUG
	std::cout<<"deleting pickups"<<std::endl;
#endif
	delete m_texture;
	for (int i = 0; i < pickupList.size(); ++i)
	{
		delete pickupList[i];
#if _DEBUG
		std::cout<<"deleted pickup "<<i+1<<std::endl;
#endif
	}

	for (int i = 0; i < itemList.size(); ++i)
	{
#if _DEBUG
		std::cout<<"deleting item "<<i+1<<" ";
#endif
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
		case -1: // fading in
		case 0: // floating around
			if (m_collision->head->isEnabled)
			{
				if (m_collision->HitHead(itemList[i]->m_hitbox) && !m_flamingo->m_hasFood)
				{
#if _DEBUG
					std::cout<<"collide "<<i<<std::endl;
#endif

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
				m_soundLibrary->m_sounds[18]->playWithRandPitch(0.4f); // pop
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
						m_soundLibrary->m_sounds[9]->playWithRandPitch(0.4f); // mäisk
						m_soundLibrary->m_sounds[17]->m_sound->setPitch(0.8);
						m_soundLibrary->m_sounds[17]->play(); //vihollislintu 
						

						itemList[i]->m_state = 5;
						itemList[i]->m_direction = itemList[i]->m_position - m_enemy->m_enemyBirdPosition;
					}
					else
					{
						m_nest->mad(DeltaTime);
						m_soundLibrary->m_sounds[17]->m_sound->setPitch(1.0);
						m_soundLibrary->m_sounds[17]->play(); //vihollislintu
						deleteItem(i);
					}
				}
				break;
			default:
				if (m_nest->eat(DeltaTime, c_item, itemList[i]->m_pickup->m_foodValue))
				{
					deleteItem(i);
					m_soundLibrary->m_sounds[5]->playWithRandPitch(0.1f);
				}
				else
				{
					if(itemList[i]->m_pickup->m_foodValue <= 0 && c_item != 0)
						m_soundLibrary->m_sounds[12]->playWithRandPitch(0.1f); // piip

					m_soundLibrary->m_sounds[9]->playWithRandPitch(0.4f); // mäisk
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
#if _DEBUG
			std::cout<<"Undefined item state"<<std::endl;
#endif
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
		m_timer -= 2.0f + (rand()%200)/100.0f;

		addItem();
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
#if _DEBUG
		std::cout<<"deleting item "<<i+1<<" ";
#endif
		delete itemList[i];
		itemList.clear();
	}
	
	m_timer = 0;
}

void pickups::deleteItem(int i)
{
	delete itemList[i];
	itemList.erase(itemList.begin() + i);
	m_index--;
}
void pickups::addItem()
{
	if (itemList.size() < 12)
	{
		for (int i = 0; i < 1; ++i)
		{
			float posX = WATER_LEFT + (WATER_RIGHT-WATER_LEFT) * (rand()%100)/100.0f;
			float posY = WATER_TOP + (WATER_BOTTOM-WATER_TOP) * (rand()%100)/100.0f;
			vector position(posX,posY);

			int rarity = rand()%100;
			ItemName name;
			if (rarity < 15)
			{
				if (countItem(Shoe) <3)
					name = Shoe;
				else if (countItem(Can) <2)
					name = Can;
				else
					name = Plancton;
			}
			else if (rarity < 25)
			{
				
				if (countItem(Can) <2)
					name = Can;
				else if (countItem(Shoe) <3)
					name = Shoe;
				else
					name = Plancton;
			}
			else if (rarity < 50)
			{
				name = Shrimp;
			}
			else if (rarity < 75)
			{
				name = Plancton;
			}
			else if (rarity < 100)
			{
				name = Krill;
			}

			itemList.push_back(new item(position,pickupList[name]));
		}
	}
}

int pickups::countItem(ItemName itemName)
{
	int retVal = 0;
	for (int i = 0; i < itemList.size(); ++i)
	{
		if (itemList[i]->m_pickup->m_itemName == itemName)
			retVal++;
	}
	return retVal;
}