#ifndef ENEMY_H
#define ENEMY_H

#include <SFML/Graphics.hpp>
#include <iostream>

class enemy
{
public:
	enemy(){}
	enemy(sf::RenderWindow *Window);
	~enemy();
	void update(sf::Time DeltaTime);
	void draw();

private:
	sf::RenderWindow *window;
	
	sf::Vector2f enemyOrigin, enemyBirdPosition;

	int enemyRotate;


	sf::Texture *enemyTexture;
	sf::Sprite enemyBird;

};

#endif