#ifndef NEST_H
#define NEST_H

#include <SFML/Graphics.hpp>
#include <iostream>
#include "hitbox.h"


class nest
{
public:
	nest(){}
	nest(sf::RenderWindow *Window, collision* Collide);
	~nest();
	void update(float DeltaTime);
	void draw();

private:
	sf::RenderWindow *window;

	hitbox *nestHitbox;
	hitbox *hatchlingHitbox;

	sf::Vector2f nestPosition, nestOrigin, hatchlingPosition;

	sf::Texture *nestTexture;
	sf::Sprite flamingonest;

	sf::Texture *m_hatchlingTexture;
	sf::Sprite *m_hatchling;

};


#endif