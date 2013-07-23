#ifndef ENEMY_H
#define ENEMY_H

class enemy;

#include <SFML/Graphics.hpp>
#include <iostream>
#include "animation.h"
#include "hitbox.h"
#include "program.h"
#include "particleEngine.h"
#include <math.h>
#include "gui.h"
#include "nest.h"

class enemy
{
public:
	enemy(collision* Collide, gui* Gui, particleEngine* ParticleEngine);
	~enemy();

	void update(float DeltaTime);
	void draw(al::viewport* Viewport);

	void reset();

	bool m_takingEgg;
	bool m_tookEgg;
	bool m_nestHasEggs;

private:
	void eat(float foodValue, al::vector itemDirection);
	void fly(float DeltaTime);
	void die(float DeltaTime);
	void fall(float DeltaTime);
	void happy(float DeltaTime);
	void respawn();
	void flyBack();
	void catchEgg(float DeltaTime);

	animation* m_animation;
	hitbox* m_hitbox;
	collision *m_collision;
	al::vector m_enemyOrigin, m_enemyBirdPosition, m_prevPosition, m_direction, m_eggPosition;
	particleEngine* m_particleEngine;

	int m_birdPhase;
	float m_timer;
	float m_enemyRotate,m_enemyDownFall, m_enemyLeftFall;



	al::texture *m_texture;
	al::sprite *m_sprite;

	al::texture *m_eggTexture;
	al::sprite *m_eggSprite;

	// SCORE-stats
	gui *m_gui;

	friend class pickups;
	friend class gui;

};

#endif