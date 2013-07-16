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
#include "sound.h"

namespace pups
{
	enum ItemName
	{
		Plancton = 0,
		Shrimp,
		Shoe,
		Can,
		Krill
	};

	//Class for pickup types, containing texture, sprite, id and edibility
	class pickup
	{
	public:
		pickup(al::texture* Texture, ItemName itemName, float FoodValue, float Speed, float Scale, float Opacity);
		~pickup();
		al::texture* m_texture;
		ItemName m_itemName;
		float m_foodValue;
		float m_speed;
		float m_scale;
		float m_opacity;
	};

	//Class for individual items, contains pointer to pickup, telling what type of item this is
	class item
	{

	public:
		item(al::vector Position, pickup* Pickup);
		~item();

		bool update(float DeltaTime);
		void draw(al::viewport* Viewport);

		al::vector m_position;
		al::vector m_direction;
		pickup* m_pickup;
		al::sprite *m_sprite;
		animation* m_animation;
		hitbox* m_hitbox;
		int m_state;

	private:
		void stayInWater();

	};
}

//Class that creates pickup types, controls individual items
class pickups
{

public:
	//pickups(){}
	pickups(collision *Collision, nest* Nest, enemy* Enemy, flamingo* Flamingo, soundLibrary* SoundLibrary);
	~pickups();

	void update(float DeltaTime);
	void draw(al::viewport* Viewport);
	void drawHitBoxes(sf::RenderWindow* window);
	void reset();

private:
	void deleteItem(int i);
	void addItem();

	float m_timer;
	nest *m_nest;
	enemy *m_enemy;
	flamingo *m_flamingo;
	int m_index;

	soundLibrary* m_soundLibrary;



	collision *m_collision;

	al::vector m_spawnPosition;

	std::vector<pups::pickup*> pickupList;
	std::vector<pups::item*> itemList;

	al::texture *m_texture;


};

#endif