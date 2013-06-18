#ifndef PICKUPS_H
#define PICKUPS_H

#include <SFML/Graphics.hpp>
#include <iostream>

//new class
class pickup
{
public:
	pickup(std::string TextureLocation, int Id, bool Edible);
	~pickup();
	int id;
	bool edible;
	
	sf::Sprite sprite;

private:
	sf::Texture *texture;
};


//new class
class item
{

public:
	item(sf::Vector2f Position, pickup Pickup);
	~item();
	sf::Vector2f position;
	pickup *m_pickup;
	

private:
	sf::Vector2f direction;

};

//new class
class pickups
{

public:
	pickups(){}
	pickups(sf::RenderWindow *Window);
	~pickups();
	void update(sf::Time DeltaTime);
	void draw();
	

private:
	float timer;

	sf::RenderWindow *window;
	sf::Vector2f spawnPosition;

	std::vector<pickup*> pickupList;
	std::vector<item> itemList;
};

#endif