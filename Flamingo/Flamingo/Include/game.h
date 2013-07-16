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
#include "particleEngine.h"

class game 
{
public:
	game(sf::RenderWindow *Window, al::viewport* Viewport);
	~game();

	void init();
	void update(float deltaTime);
	void draw();

	void reset();

	void drawDebugInfo(sf::RenderWindow *window);

	al::input* m_input;

private:
	sf::RenderWindow *window;
	al::viewport* m_viewport;
	
	al::vector m_ReturnPosition, m_ReturnOrigin;
	al::texture *m_ReturnTexture;
	al::sprite m_ReturnCheck;
	
	al::vector m_GmenuPosition, m_GmenuOrigin;
	al::texture *m_GmenuTexture;
	al::sprite m_GMenu;
	
	al::vector m_creditsPosition, m_creditsOrigin;
	al::texture *m_creditsTexture;
	al::sprite m_credits;

	al::vector m_optionsPosition, m_optionsOrigin;
	al::texture *m_optionsTexture;
	al::sprite m_options;
	
	bool P_release;
	bool M_release;
	bool ML_release;
	bool m_muted;
	
	// gameStates
	enum GameState
	{
		TitleScreen = 0,
		Play,
		Menu,
		Pause,
		Credits,
		Options,
		Gamemenu,
		ReturnTitle
	};

	GameState m_state;

	// hitbox
	collision* collide;

	// animation


	// gui
	gui *m_gui;



	// titleCard
	titleCard *m_titleCard;


	

	//flamingo
	flamingo* m_flamingo;

	// nest
	nest* m_nest;

	// enemy
	enemy* m_enemy;

	// pickups
	pickups* m_pickups;

	// water
	background* m_background;

	//cloud
	cloud* m_cloud;

	// particles
	particleEngine* m_particleEngine;

	//renderstatistics


	////sound
	soundLibrary* m_soundLibrary;


	al::texture m_pauseOpacityTexture;
	al::sprite m_pauseOpacitySprite;

};

#endif