#ifndef PICKUPS_H
#define PICKUPS_H

#include <SFML/Graphics.hpp>
#include <iostream>
#include <stdlib.h>
#include "animation.h"
#include "hitbox.h"
#include "program.h"
#include "nest.h"
#include "enemy.h"
#include "flamingo.h"

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
		item(al::vector Position, pickup* Pickup);
		~item();

		void update(float DeltaTime);
		void draw(al::viewport* Viewport);

		al::vector m_position;
		al::vector m_direction;
		pickup* m_pickup;
		al::sprite* m_sprite;
		animation* m_animation;
		hitbox* m_hitbox;
		bool m_floating;

	private:
		void stayInWater();

	};
}
//Class that creates pickup types, controls individual items
class pickups
{

public:
	//pickups(){}
	pickups(collision *Collision, nest* Nest, enemy* Enemy, flamingo* Flamingo);
	~pickups();
	void update(float DeltaTime);
	void draw(al::viewport* Viewport);
	void drawHitBoxes(sf::RenderWindow* window);
	

private:
	float m_timer;
	nest* m_nest;
	enemy* m_enemy;
	flamingo* m_flamingo;



	sf::RenderWindow *window;

	collision *m_collision;

	al::vector m_spawnPosition;

	std::vector<pups::pickup*> pickupList;
	std::vector<pups::item*> itemList;
	std::vector<pups::item*> outOfWater;

	al::texture* m_texture;

};

#endif