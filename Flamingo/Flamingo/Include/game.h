#ifndef GAME_H
#define GAME_H

#include <SFML/Graphics.hpp>
#include <iostream>
#include "head.h"
#include "background.h"
#include "gui.h"
#include "enemy.h"
#include "nest.h"
#include "flamingo.h"
#include "neck.h"

class game 
{
public:
	game(sf::RenderWindow *Window);

	~game();

	void update(sf::Time DeltaTime);

	void draw();

private:
	sf::RenderWindow *window;

	// gameStates
	enum GameState
	{
		TitleScreen = 0,
		Play,
		Menu,
		Pause,
		Credits
	};

	GameState state;

	// hitbox


	// animation


	// gui
	gui *text;

	// head
	head flamingoHead;

	//neck
	neck flamingoNeck;

	//flamingo
	body flamingoBase;

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