#ifndef HITBOX_H
#define HITBOX_H

#include <SFML\Graphics.hpp>
#include <iostream>
#include <SFML\Graphics\Rect.hpp>
#include "program.h"

class hitbox
{
public:
	hitbox(){}
	hitbox(al::vector _Position, al::vector _Size, al::vector _Origo, bool _isEnabled);
	~hitbox();

	void draw(sf::RenderWindow* window);

	al::rectangle hitRect();

	al::vector Position;
	al::vector Size;
	al::vector Origo;

	bool isEnabled;

private:

};

class collision
{
public:
	collision();
	~collision();

	/**id list: hatchling = 0, head = 1, enemy = 2*/
	hitbox* createHitBox(sf::Vector2f position, sf::Vector2u size, sf::Vector2f origo, int id, bool isEnabled = true);
	hitbox* createHitBox(al::vector position, al::vector size, al::vector origo, int id, bool isEnabled = true);

	void DrawHitboxes(sf::RenderWindow* window);

	bool HitHead(hitbox* ItemHitbox);
	int HitHatchling(hitbox* ItemHitbox);
	bool HitEnemy(hitbox* ItemHitbox);

	bool isCollided(hitbox *hitbox1,hitbox *hitbox2);

private:
	std::vector<hitbox*> hatchlings;
	hitbox* head;
	hitbox* enemy;
};

#endif