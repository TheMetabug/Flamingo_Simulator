#ifndef HEAD_H
#define HEAD_H

#include <SFML/Graphics.hpp>
#include <iostream>
#include "hitbox.h"

class head
{
public:
	head(){}
	head(sf::RenderWindow *Window, collision* Collide);
	~head();
	void update(float DeltaTime);
	void draw();
private:
	sf::RenderWindow *window;

	hitbox *headHitbox;

	sf::Vector2f mousePosition, headPosition, headOrigin, crossHair;

	int drag;

	sf::Texture *headTexture;
	sf::Sprite flamingoHead;
	sf::Texture *crossTexture;
	sf::Sprite crosshairSprite;
};

#endif