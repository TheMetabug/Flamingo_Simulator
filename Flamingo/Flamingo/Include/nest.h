#ifndef NEST_H
#define NEST_H

#include <SFML/Graphics.hpp>
#include <iostream>
#include "hitbox.h"
#include "animation.h"
#include "program.h"
#include "gui.h"
#include "particleEngine.h"
#include "sound.h"
class nest;
//Hatchling

class hatchling
{
public:
	hatchling(nest* Nest, collision* Collide);
	~hatchling();

	void update(float DeltaTime);
	void draw(al::viewport* Viewport);

	void fly();
	void eat(float foodValue);
	void mad();
	void happy();
	void die();

	void reset();


	al::vector m_position;
	al::sprite* m_sprite;
	al::sprite* m_flySprite;
	animation *m_animation;
	particleEngine* m_particleEngine;
	animation *m_flyAnimation;
	hitbox* m_hitbox;
	float m_timer, m_eatPoints, m_rotation, m_flyScale, m_travelTime;
	bool m_isThere;
	bool m_fly;
	int m_state;

	nest *m_nest;

	friend class nest;
};

//Nest

class nest
{
public:
	nest(collision* Collide, gui* Gui, particleEngine* ParticleEngine);
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
	void removeEgg();
	void updateEggPositions();
	void reset();

	int m_whichBird;

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
				m_eggVector,
				m_eggTarget;

	particleEngine* m_particleEngine;

	al::texture *m_eggTexture;
	std::vector<al::sprite*> m_eggs;

	al::sprite *m_theEgg;
	animation *m_eggAnimation;

	al::texture *m_nestTexture;
	al::sprite	 m_flamingonest;

	al::sprite	 m_flamingonestFront;

	al::texture *m_hatchlingTexture;
	al::texture *m_hatchlingFlyTexture;
	std::vector<hatchling*> m_hatchlings;

	//al::sprite *m_hatchlingFly;
	//animation *m_hatchlingFlyAnimation;

	int m_eggCount;
	float m_hatchlingRotation, m_timer, m_eggTimer, m_travelTime, m_scale, m_theEggScale;
	bool m_hatching;
	bool m_egging;

	bool m_noEggs;
	
	// SCORE-stats
	gui *m_gui;

	// sound
	soundLibrary* m_soundLibrary;

	friend class pickups;
	friend class hatchling;
	friend class gui;
};

#endif