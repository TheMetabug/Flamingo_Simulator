#ifndef FLAMINGO_H
#define FLAMINGO_H

#include <SFML/Graphics.hpp>
#include <iostream>
#include <math.h>
#include "hitbox.h"
#include "program.h"
#include "sound.h"
#include "animation.h"
#include "input.h"
#include "particleEngine.h"

class neckPiece
{
public:
	neckPiece(){}
	~neckPiece();
	
	al::sprite m_sprite;
	al::vector m_positionMultiplier, m_positionRelative, m_turnedPositionMultiplier;
	
};

class flamingo
{
public:
	 //flamingo(){}
	 flamingo(soundLibrary* SoundLibrary, collision* Collide, al::input* Input, particleEngine* ParticleEngine);
	~flamingo();
	void update(float DeltaTime, bool MLPressed);
	void draw(al::viewport* Viewport);
	void reset();
	
	animation *m_headAnimation;

private:
	void flip(bool HeadFlipped);

	float m_moveTime;
	al::input* m_input;
	float m_timer, m_multiplier, m_throwMultiplier, m_headRotate, m_distance, m_maxDistance;
	bool m_hasFood;
	bool m_splashed;

	///////////BODY////////////

	al::vector m_flamingoPosition;

	////////////HEAD///////////

	al::vector m_mousePosition, m_mouseStartPos, m_headPosition, m_headOrigin, m_crossHair, m_direction;

	hitbox* m_headHitbox;

	int m_drag;

	/////////////NECK//////////

	al::vector m_bodyToHead;

	std::vector<neckPiece*> m_neckPieces;



	// Textures and sprites
	al::texture* m_headTexture;
	al::texture* m_crossTexture;
	al::texture* m_neckTexture;
	al::texture* m_bodyTexture;
	al::texture* m_arrowTexture;
	al::sprite m_flamingoNeck;
	al::sprite m_flamingoHead;
	al::sprite m_crosshairSprite;
	al::sprite m_flamingoBody;
	al::sprite m_arrowSprite;

	// sound
	soundLibrary* m_soundLibrary;
	particleEngine* m_particleEngine;
	
	friend class pickups;
};

#endif