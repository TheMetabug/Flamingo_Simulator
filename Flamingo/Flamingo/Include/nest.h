#ifndef NEST_H
#define NEST_H

#include <SFML/Graphics.hpp>
#include <iostream>
#include "hitbox.h"
#include "animation.h"
#include "program.h"

class hatchling
{
public:
	hatchling()
		: m_isThere(true){}
	~hatchling()
	{
		delete m_sprite;
		delete m_animation;
	}

	al::vector m_position;
	al::sprite* m_sprite;
	hitbox* m_hitbox;
	animation* m_animation;
	bool m_isThere;
};

class nest
{
public:
	//nest(){}
	nest(collision* Collide);
	~nest();
	void update(float DeltaTime);
	void draw(al::viewport* Viewport);

	void egg(float DeltaTime);
	void sleep(float DeltaTime);
	bool eat(float DeltaTime, int Id, float foodValue);
	void die(float DeltaTime);
	void fly(float DeltaTime);
	void mad(float DeltaTime);

private:
	animation *Animator;

	hitbox *m_nestHitbox;
	hitbox *m_hatchlingHitbox;

	al::vector m_nestPosition, m_nestOrigin, m_hatchlingPosition_1, m_hatchlingPosition_2, m_hatchlingPosition_3;
	std::vector<al::vector> m_hatchlingPositions;

	al::texture *m_nestTexture;
	al::sprite m_flamingonest;

	al::texture* m_hatchlingTexture;
	std::vector<al::sprite*> m_hatchlings;
	std::vector<hitbox*> m_hatchlingHitboxes;
	std::vector<animation*> m_animations;

	float m_hatchlingRotation, m_timer;


	friend class pickups;
};




#endif