#ifndef ENEMY_H
#define ENEMY_H

#include <SFML/Graphics.hpp>
#include <iostream>
#include "animation.h"
#include "hitbox.h"

class enemy
{
public:
	enemy(){}
	enemy(sf::RenderWindow *Window, collision* Collide);
	~enemy();
	void update(float DeltaTime);
	void draw();

private:
	animation *Animator;
	sf::RenderWindow *window;

	hitbox *enemyHitbox;
	
	sf::Vector2f enemyOrigin, enemyBirdPosition;

	float enemyRotate;


	sf::Texture *enemyTexture;
	sf::Sprite *enemyBird;

};

#endif