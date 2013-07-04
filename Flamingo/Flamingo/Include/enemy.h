#ifndef ENEMY_H
#define ENEMY_H

#include <SFML/Graphics.hpp>
#include <iostream>
#include "animation.h"
#include "hitbox.h"
#include "program.h"
#include <math.h>

class enemy
{
public:
	//enemy(){}
	enemy(collision* Collide);
	~enemy();
	void update(float DeltaTime);
	void draw(al::viewport* Viewport);

private:
	sf::RenderWindow* window;
	animation* m_animation;
	hitbox* m_hitbox;
	collision *m_collision;
	al::vector m_enemyOrigin, m_enemyBirdPosition, m_prevPosition, m_direction;

	int m_birdPhase;
	float m_timer;
	float m_enemyRotate;
	void eat(float foodValue, al::vector itemDirection);
	void fly(float DeltaTime);
	void die(float DeltaTime);
	void fall(float DeltaTime);
	void respawn();

	//sf::Texture *m_enemyTexture;
	//sf::Sprite *m_enemyBird;

	al::texture *m_texture;
	al::sprite *m_sprite;

	friend class pickups;

};

#endif