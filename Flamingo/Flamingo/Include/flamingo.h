#ifndef FLAMINGO_H
#define FLAMINGO_H

#include <SFML/Graphics.hpp>
#include <iostream>
#include <math.h>
#include "hitbox.h"

class neckPiece
{
public:
	neckPiece(){}
	~neckPiece(){}
	
	sf::Sprite m_sprite;

	sf::Vector2f m_positionMultiplier, m_positionRelative;
	
};

class flamingo
{
	public:
	 flamingo(){}
	 flamingo(sf::RenderWindow *Window, collision* Collide);
	~flamingo();
	void update(float DeltaTime);
	void draw();

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

	std::vector<neckPiece> m_neckPieces;



	// Textures and sprites
	sf::Texture* m_headTexture;
	sf::Texture* m_crossTexture;
	sf::Texture* m_neckTexture;
	sf::Texture* m_bodyTexture;
	sf::Sprite m_flamingoNeck;
	sf::Sprite m_flamingoHead;
	sf::Sprite m_crosshairSprite;
	sf::Sprite m_flamingoBody;
	
};

#endif