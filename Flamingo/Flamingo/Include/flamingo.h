#ifndef FLAMINGO_H
#define FLAMINGO_H

#include <SFML/Graphics.hpp>
#include <iostream>
#include "hitbox.h"

class neckPiece
{
public:
	neckPiece();
	~neckPiece();
	void update();
	void draw(sf::RenderWindow *window);
	
	sf::Texture *neckTexture;
	sf::Sprite flamingoNeck;

	sf::Vector2f m_position;
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

	////////////HEAD///////////

	hitbox *headHitbox;

	sf::Vector2f mousePosition, headPosition, headOrigin, crossHair;

	int drag, h_rotate;

	/////////////NECK//////////

	sf::Vector2f neckPosition, neckOrigin, neckHead;

	///////////BODY////////////

	sf::Vector2f bodyPosition;

	// Textures and sprites
	sf::Texture *headTexture;
	sf::Sprite flamingoHead;
	sf::Texture *crossTexture;
	sf::Sprite crosshairSprite;
	sf::Texture *neckTexture;
	sf::Sprite flamingoNeck;
	sf::Texture *bodyTexture;
	sf::Sprite flamingoBody;
	
};

#endif