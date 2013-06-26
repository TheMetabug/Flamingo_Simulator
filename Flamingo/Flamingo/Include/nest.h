#ifndef NEST_H
#define NEST_H

#include <SFML/Graphics.hpp>
#include <iostream>
#include "hitbox.h"
#include "animation.h"


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

	animation *Animator;

	hitbox *m_nestHitbox;
	hitbox *m_hatchlingHitbox;

	sf::Vector2f m_nestPosition, m_nestOrigin, m_hatchlingPosition_1, m_hatchlingPosition_2, m_hatchlingPosition_3;
	std::vector<sf::Vector2f> m_hatchlingPositions;

	sf::Texture *m_nestTexture;
	sf::Sprite m_flamingonest;

	std::vector<sf::Texture*> m_hatchlingTextures;
	std::vector<sf::Sprite*> m_hatchlings;
	std::vector<hitbox*> m_hatchlingHitboxes;
	std::vector<animation*> m_animations;

};


#endif