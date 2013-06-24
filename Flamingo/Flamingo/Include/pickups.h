#ifndef PICKUPS_H
#define PICKUPS_H

#include <SFML/Graphics.hpp>
#include <iostream>
#include <stdlib.h>
#include "animation.h"
#include "hitbox.h"

namespace pups
{
	enum ItemName
	{
		Shoe = 0,
		Fish,
		Plancton
	};

	//Class for pickup types, containing texture, sprite, id and edibility
	class pickup
	{
	public:
		pickup(sf::Texture* Texture, ItemName itemName, float FoodValue);
		~pickup();
		sf::Texture* m_texture;
		ItemName m_itemName;
		float m_foodValue;
	};


	//Class for individual items, contains pointer to pickup, telling what type of item this is
	class item
	{

	public:
		item(sf::Vector2f Position, pickup* Pickup);
		~item();

		void update(float DeltaTime);
		void draw(sf::RenderWindow *window);

		sf::Vector2f m_position;
		pickup* m_pickup;
		sf::Sprite* m_sprite;
		animation* m_animation;
		hitbox* m_hitbox;

	private:
		sf::Vector2f m_direction;

	};
}
//Class that creates pickup types, controls individual items
class pickups
{

public:
	pickups(){}
	pickups(sf::RenderWindow *Window);
	~pickups();
	void update(float DeltaTime);
	void draw();
	

private:
	float timer;

	sf::RenderWindow *window;
	sf::Vector2f spawnPosition;

	std::vector<pups::pickup*> pickupList;
	std::vector<pups::item*> itemList;

	sf::Texture* texture;
};

#endif