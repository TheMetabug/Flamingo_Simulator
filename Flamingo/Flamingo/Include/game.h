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
#include "program.h"
#include "input.h"

class game 
{
public:
	game(sf::RenderWindow *Window, al::viewport* Viewport);

	~game();

	void update(float deltaTime);

	void draw();
	void drawDebugInfo(sf::RenderWindow *window);
	al::input* m_input;

private:
	sf::RenderWindow *window;
	al::viewport* m_viewport;
	
	bool P_release;
	bool M_release;
	bool ML_release;
	
	// gameStates
	enum GameState
	{
		TitleScreen = 0,
		Play,
		Menu,
		Pause,
		Credits,
		Options,
		Gamemenu
	};

	GameState state;

	// hitbox
	collision* collide;

	// animation


	// gui
	gui *m_gui;

	// titleCard
	titleCard *m_titleCard;
	

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

	//cloud
	cloud* m_cloud;

	// particles

	//renderstatistics


	////sound
	soundLibrary* m_soundLibrary;


};

#endif