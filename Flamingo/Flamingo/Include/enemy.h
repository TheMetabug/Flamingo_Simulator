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
	sf::Vector2f m_enemyOrigin, m_enemyBirdPosition;

	float m_enemyRotate;

	sf::Texture *m_enemyTexture;
	sf::Sprite *m_enemyBird;

};

#endif