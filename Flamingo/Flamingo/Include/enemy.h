#ifndef ENEMY_H
#define ENEMY_H

#include <SFML/Graphics.hpp>
#include <iostream>
#include "animation.h"
#include "hitbox.h"
#include "program.h"
#include "particleEngine.h"
#include <math.h>
#include "gui.h"

class enemy
{
public:
	enemy(collision* Collide, gui* Gui, particleEngine* ParticleEngine);
	~enemy();

	void update(float DeltaTime);
	void draw(al::viewport* Viewport);

	void reset();

private:
	void eat(float foodValue, al::vector itemDirection);
	void fly(float DeltaTime);
	void die(float DeltaTime);
	void fall(float DeltaTime);
	void happy(float DeltaTime);
	void respawn();
	void flyBack(float DeltaTime);

	animation* m_animation;
	hitbox* m_hitbox;
	collision *m_collision;
	al::vector m_enemyOrigin, m_enemyBirdPosition, m_prevPosition, m_direction;
	particleEngine* m_particleEngine;

	int m_birdPhase;
	float m_timer;
	float m_enemyRotate;



	al::texture *m_texture;
	al::sprite *m_sprite;

	// SCORE-stats
	gui *m_gui;

	friend class pickups;
	friend class gui;

};

#endif