#ifndef PICKUPS_H
#define PICKUPS_H

namespace pups
{
	enum ItemName;
	class pickup;
	class item;
}
class pickups;


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
#include "particleEngine.h"

namespace pups
{
	enum ItemName
	{
		Plancton = 0,
		Shrimp,
		Krill,
		Shoe,
		Can,
		ItemsCount
	};

	//Class for pickup types, containing texture, sprite, id and edibility
	class pickup
	{
	public:
		pickup(al::texture* Texture, ItemName itemName, float FoodValue, float Speed, float Scale, float Opacity, pickups* Pickups);
		~pickup();
		al::texture* m_texture;
		ItemName m_itemName;
		float m_foodValue;
		float m_speed;
		float m_scale;
		float m_opacity;
		pickups* m_pickups;
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
		float m_timer;

	};
}

//Class that creates pickup types, controls individual items
class pickups
{

public:
	//pickups(){}
	pickups(collision *Collision, nest* Nest, enemy* Enemy, flamingo* Flamingo, soundLibrary* SoundLibrary, particleEngine* ParticleEngine);
	~pickups();

	void update(float DeltaTime);
	void draw(al::viewport* Viewport);
	void drawHitBoxes(sf::RenderWindow* window);
	void reset();

private:
	void deleteItem(int i);
	void addItem();
	int countItem(pups::ItemName itemName);

	float m_timer;
	nest *m_nest;
	enemy *m_enemy;
	flamingo *m_flamingo;
	int m_index;

	soundLibrary* m_soundLibrary;
	particleEngine* m_particleEngine;



	collision *m_collision;

	al::vector m_spawnPosition;

	std::vector<pups::pickup*> pickupList;
	std::vector<pups::item*> itemList;

	al::texture *m_texture;

	friend class pups::item;
};

#endif