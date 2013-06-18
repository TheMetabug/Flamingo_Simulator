#ifndef HITBOX_H
#define HITBOX_H

#include <SFML\Graphics.hpp>
#include <iostream>
#include <SFML\Graphics\Rect.hpp>

class hitbox
{
public:
	hitbox(){}
	hitbox(sf::Vector2f _Position, sf::Vector2f _Size, bool _isEnabled);
	~hitbox();

	sf::Rect<int> hitRect();

	sf::Vector2f Position;
	sf::Vector2f Size;

	bool isEnabled;

private:

};

class collision
{
public:
	collision();
	~collision();

	hitbox* createHitBox(sf::Vector2f position, sf::Vector2f size, int id);

	void headPickup();
	void pickupHatchling();
	void pickupEnemy();
	void headEnemy();

	bool isCollided;

private:
	std::vector<hitbox> pickups;
	std::vector<hitbox> hatchlings;
	hitbox head;
	hitbox enemy;

};

#endif