#ifndef GAME_H
#define GAME_H

#include <SFML/Graphics.hpp>
#include <iostream>
#include "head.h"
#include "background.h"
#include "gui.h"
#include "enemy.h"
#include "nest.h"

class game 
{
public:
	game(sf::RenderWindow *Window);

	~game();

	void update(sf::Time DeltaTime);

	void draw();

private:
	sf::RenderWindow *window;

	// hitbox


	// animation


	// gui
	gui *text;

	// head
	head flamingoHead;

	// nest
	nest flamingonest;

	// enemy
	enemy enemyBird;

	// pickups


	// water
	background water;

	// particles



};

#endif