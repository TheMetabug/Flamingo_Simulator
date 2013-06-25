#include "pickups.h"
#include <time.h>

using namespace pups;


//Pickup

pickup::pickup(sf::Texture* Texture, ItemName itemName, float FoodValue, float Speed)
	: m_texture(Texture),
	  m_itemName(itemName),
	  m_foodValue(FoodValue),
	  m_speed(Speed)
{
}

pickup::~pickup()
{
	std::cout<<"deleted pickup type"<<std::endl;
}



// Item

item::item(sf::Vector2f Position, pickup* Pickup)
	: m_position(Position),
	  m_pickup(Pickup),
	  m_floating(true)
{
	m_sprite = new sf::Sprite(*(Pickup->m_texture));
	m_animation = new animation(m_sprite,1,256,256,false, 1.0f, Pickup->m_itemName);
	m_sprite->setPosition(m_position);
	m_sprite->setOrigin(
		sf::Vector2f(	m_sprite->getLocalBounds().width / 2, 
						m_sprite->getLocalBounds().height / 2));
	m_sprite->setScale(0.5f,0.5f);

	m_hitbox = new hitbox(m_position,
		sf::Vector2f(m_sprite->getGlobalBounds().width,m_sprite->getGlobalBounds().height),
		sf::Vector2f(	m_sprite->getGlobalBounds().width / 2, 
						m_sprite->getGlobalBounds().height / 2),
		true);

	m_direction = sf::Vector2f((rand()%200 / 100.0f)-1,(rand()%200 / 100.0f)-1);
}

item::~item()
{
	std::cout<<"aaand its gone"<<std::endl;
}

void item::update(float DeltaTime)
{
	m_position += m_direction * DeltaTime * m_pickup->m_speed;

	if (m_floating)
	{
		float left = 450, right = 1280, top = 450, bottom = 720;
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

	m_sprite->setPosition(m_position);
	m_hitbox->Position = m_position;
}

void item::draw(sf::RenderWindow *window)
{
	window->draw(*m_sprite);
}



// Pickups

pickups::pickups(sf::RenderWindow *Window, collision *Collision)
	: window(Window),
	  m_collision(Collision),
	  timer(0)
{
	spawnPosition = sf::Vector2f(500,500);

	texture = new sf::Texture();
	texture->loadFromFile("Assets/itemsplaceholder.png"); // Texture containing all item animations
	texture->setSmooth(true);
	
	pickupList.push_back(new pickup(texture, Shoe, 0.0f, 20.0f));
	pickupList.push_back(new pickup(texture, Shrimp, 1.0f, 200.0f));
	pickupList.push_back(new pickup(texture, Plancton, 1.0f, 60.0f));
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
	timer += DeltaTime;

	for (int i = itemList.size() - 1; i >= 0; --i)
	{
		itemList[i]->update(DeltaTime);

		if (m_collision->HitHead(itemList[i]->m_hitbox))
		{
			std::cout<<"collide "<<i<<std::endl;
			delete itemList[i];
			itemList.erase(itemList.begin() + i);
		}

		else if (m_collision->HitEnemy(itemList[i]->m_hitbox))
		{
			std::cout<<"collide enemy "<<i<<std::endl;
			delete itemList[i];
			itemList.erase(itemList.begin() + i);
		}
	}

	if (timer > 2.0f)
	{
		timer -= 0.1f;

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

		itemList.push_back(new item(spawnPosition,pickupList[name]));
	}
}

void pickups::draw()
{
	for (int i = 0; i < itemList.size(); ++i)
	{
		itemList[i]->draw(window);
	}
}

void pickups::drawHitBoxes()
{
	for (int i = 0; i < itemList.size(); ++i)
	{
		itemList[i]->m_hitbox->draw(window);
	}
}