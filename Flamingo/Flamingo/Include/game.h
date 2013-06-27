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
#include "pickups.h"
#include "renderStatistics.h"
#include "sound.h"

class game 
{
public:
	game(sf::RenderWindow *Window);

	~game();

	void update(sf::Time DeltaTime);

	void draw();
	void drawDebugInfo();

private:
	sf::RenderWindow *window;
	
	bool P_release;
	bool M_release;
	
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
	gui *m_gui;
	

	//flamingo
	flamingo* flamingoBase;

	// nest
	nest* flamingonest;

	// enemy
	enemy* enemyBird;

	// pickups
	pickups* m_pickups;

	// water
	background* backGround;

	// particles

	//renderstatistics
	renderStatistics* m_renderStatistics;

	////sound
	//sound* m_sound;


};

#endif