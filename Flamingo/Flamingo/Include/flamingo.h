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

	sf::Vector2f mousePosition, headPosition, headOrigin, crossHair;

	hitbox *headHitbox;

	int drag, h_rotate;

	/////////////NECK//////////

	sf::Vector2f m_bodyToHead;

	std::vector<neckPiece> m_neckPieces;



	// Textures and sprites
	sf::Texture* headTexture;
	sf::Texture* crossTexture;
	sf::Texture* neckTexture;
	sf::Texture* bodyTexture;
	sf::Sprite flamingoNeck;
	sf::Sprite flamingoHead;
	sf::Sprite crosshairSprite;
	sf::Sprite flamingoBody;
	
};

#endif