#ifndef FLAMINGO_H
#define FLAMINGO_H

#include <SFML/Graphics.hpp>
#include <iostream>
#include <math.h>
#include "hitbox.h"
#include "program.h"

class neckPiece
{
public:
	neckPiece(){}
	~neckPiece(){}
	
	al::sprite m_sprite;

	sf::Vector2f m_positionMultiplier, m_positionRelative;
	
};

class flamingo
{
	public:
	 flamingo(){}
	 flamingo(sf::RenderWindow *Window, collision* Collide);
	~flamingo();
	void update(float DeltaTime);
	void draw(al::viewport* Viewport);

	private:

	sf::RenderWindow *window;
	///////////BODY////////////

	sf::Vector2f m_flamingoPosition;

	////////////HEAD///////////

	sf::Vector2f m_mousePosition, m_headPosition, m_headOrigin, m_crossHair;

	hitbox* m_headHitbox;

	int m_drag, m_headRotate;

	/////////////NECK//////////

	sf::Vector2f m_bodyToHead;

	std::vector<neckPiece*> m_neckPieces;



	// Textures and sprites
	al::texture* m_headTexture;
	al::texture* m_crossTexture;
	al::texture* m_neckTexture;
	al::texture* m_bodyTexture;
	al::sprite m_flamingoNeck;
	al::sprite m_flamingoHead;
	al::sprite m_crosshairSprite;
	al::sprite m_flamingoBody;
	
};

#endif