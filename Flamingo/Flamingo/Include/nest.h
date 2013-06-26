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

	hitbox *m_nestHitbox;
	hitbox *m_hatchlingHitbox;

	sf::Vector2f m_nestPosition, m_nestOrigin, m_hatchlingPosition_1;

	sf::Texture *m_nestTexture;
	sf::Sprite m_flamingonest;

	sf::Texture *m_hatchlingTexture_1;
	sf::Sprite *m_hatchling_1;

};


#endif