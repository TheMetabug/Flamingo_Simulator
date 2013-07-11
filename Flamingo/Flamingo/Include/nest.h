#ifndef NEST_H
#define NEST_H

#include <SFML/Graphics.hpp>
#include <iostream>
#include "hitbox.h"
#include "animation.h"
#include "program.h"
#include "gui.h"


class hatchling
{
public:
	hatchling()
		: m_isThere(true),
		  m_timer(0)
		{}

	~hatchling()
	{
		delete m_sprite;
		delete m_animation;
	}
	
	al::vector m_position;
	al::sprite* m_sprite;
	hitbox* m_hitbox;
	animation *m_animation;
	float m_timer, m_eatPoints;
	bool m_isThere;
};

class nest
{
public:
	nest(collision* Collide, gui* Gui);
	~nest();
	void update(float DeltaTime);
	void draw(al::viewport* Viewport);

	void egg(float DeltaTime);
	void sleep(float DeltaTime);
	bool eat(float DeltaTime, int Id, float foodValue);
	void die(float DeltaTime);
	void fly(float DeltaTime, int Id);
	void mad(float DeltaTime);
	void happy(float DeltaTime);

	void addEgg();

private:

	hitbox		*m_nestHitbox;
	hitbox		*m_hatchlingHitbox;

	al::vector	m_nestPosition,
				m_nestPositionFront, 
				m_nestOrigin,
				m_hatchlingPosition_1,
				m_hatchlingPosition_2,
				m_hatchlingPosition_3,
				m_eggPosition,
				m_eggVector;

	al::texture *m_eggTexture;
	std::vector<al::sprite*> m_eggs;

	al::sprite *m_theEgg;
	animation *m_eggAnimation;

	al::texture *m_nestTexture;
	al::sprite	 m_flamingonest;

	al::sprite	 m_flamingonestFront;

	al::texture *m_hatchlingTexture;
	std::vector<hatchling*> m_hatchlings;

	al::texture *m_hatchlingFlyTexture;
	al::sprite *m_hatchlingFly;
	animation *m_hatchlingFlyAnimation;

	int m_eggCount;
	float m_hatchlingRotation, m_timer, m_eggTimer;
	bool m_isAlive;
	
	// SCORE-stats
	gui *m_gui;

	friend class pickups;
	friend class gui;
};




#endif