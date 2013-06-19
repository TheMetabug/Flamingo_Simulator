#ifndef GAME_H
#define GAME_H

#include <SFML/Graphics.hpp>
#include <iostream>
#include "hitbox.h"
#include "background.h"
#include "gui.h"
#include "enemy.h"
#include "nest.h"
#include "flamingo.h"

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
	collision* collide;

	// animation


	// gui
	gui *text;

	// head
	flamingo flamingoHead;

	//neck
	flamingo flamingoNeck;

	//flamingo
	flamingo flamingoBase;

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