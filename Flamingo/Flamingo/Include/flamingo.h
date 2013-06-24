#ifndef FLAMINGO_H
#define FLAMINGO_H

#include <SFML/Graphics.hpp>
#include <iostream>
#include "hitbox.h"

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

	sf::Vector2f bodyPosition, bodyOrigin;

	sf::Texture *bodyTexture;
	sf::Sprite flamingoBody;

	////////////HEAD///////////

	hitbox *headHitbox;

	sf::Vector2f mousePosition, headPosition, headOrigin, crossHair;

	int drag, h_rotate;

	sf::Texture *headTexture;
	sf::Sprite flamingoHead;
	sf::Texture *crossTexture;
	sf::Sprite crosshairSprite;

	/////////////NECK//////////

	sf::Vector2f neckPosition, neckOrigin, neckHead;

	sf::Texture *neckTexture;
	sf::Sprite flamingoNeck;
	
};

#endif