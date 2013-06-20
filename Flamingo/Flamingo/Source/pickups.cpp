#include "pickups.h"

pickup::pickup(std::string TextureLocation, int Id, bool Edible)
{
	texture = new sf::Texture();
	texture->loadFromFile(TextureLocation);
	texture->setSmooth(true);
	sprite.setTexture(*texture);
	sprite.setPosition(500,500);
	sprite.setOrigin(texture->getSize().x/2,texture->getSize().y/2);
	sprite.setScale(0.3f, 0.3f);
}

pickup::~pickup()
{
	std::cout<<"deleted pickup"<<std::endl;
}

item::item(sf::Vector2f Position, pickup Pickup)
{
}

item::~item()
{
}





pickups::pickups(sf::RenderWindow *Window)
{
	window = Window;
	pickupList.push_back(new pickup("Assets/FlamingoEmo_Head.png", 0, true));
}

pickups::~pickups()
{
	std::cout<<"deleting pickups"<<std::endl;
	for (int i = 0; i < pickupList.size(); ++i)
	{
		delete pickupList[i];
	}
}

void pickups::update(sf::Time DeltaTime)
{
	timer += DeltaTime.asMilliseconds()/1000.0f;
}

void pickups::draw()
{
	
}