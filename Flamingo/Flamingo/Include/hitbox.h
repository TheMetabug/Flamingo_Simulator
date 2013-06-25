#ifndef HITBOX_H
#define HITBOX_H

#include <SFML\Graphics.hpp>
#include <iostream>
#include <SFML\Graphics\Rect.hpp>

class hitbox
{
public:
	hitbox(){}
	hitbox(sf::Vector2f _Position, sf::Vector2f _Size, sf::Vector2f _Origo, bool _isEnabled);
	~hitbox();

	sf::Rect<float> hitRect();

	sf::Vector2f Position;
	sf::Vector2f Size;
	sf::Vector2f Origo;

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
	hitbox* createHitBox(sf::Vector2f position, sf::Vector2f size, sf::Vector2f origo, int id, bool isEnabled = true);

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