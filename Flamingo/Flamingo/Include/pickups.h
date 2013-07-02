#ifndef PICKUPS_H
#define PICKUPS_H

#include <SFML/Graphics.hpp>
#include <iostream>
#include <stdlib.h>
#include "animation.h"
#include "hitbox.h"
#include "program.h"

namespace pups
{
	enum ItemName
	{
		Shoe = 0,
		Shrimp,
		Plancton
	};

	//Class for pickup types, containing texture, sprite, id and edibility
	class pickup
	{
	public:
		pickup(al::texture* Texture, ItemName itemName, float FoodValue, float Speed);
		~pickup();
		al::texture* m_texture;
		ItemName m_itemName;
		float m_foodValue;
		float m_speed;
	};


	//Class for individual items, contains pointer to pickup, telling what type of item this is
	class item
	{

	public:
		item(sf::Vector2f Position, pickup* Pickup);
		~item();

		void update(float DeltaTime);
		void draw(al::viewport* Viewport);

		al::vector m_position;
		pickup* m_pickup;
		al::sprite* m_sprite;
		animation* m_animation;
		hitbox* m_hitbox;
		bool m_floating;

	private:
		al::vector m_direction;

	};
}
//Class that creates pickup types, controls individual items
class pickups
{

public:
	pickups(){}
	pickups(sf::RenderWindow *Window, collision *Collision);
	~pickups();
	void update(float DeltaTime);
	void draw(al::viewport* Viewport);
	void drawHitBoxes();
	

private:
	float m_timer;

	sf::RenderWindow *window;

	collision *m_collision;

	sf::Vector2f m_spawnPosition;

	std::vector<pups::pickup*> pickupList;
	std::vector<pups::item*> itemList;

	al::texture* m_texture;
};

#endif