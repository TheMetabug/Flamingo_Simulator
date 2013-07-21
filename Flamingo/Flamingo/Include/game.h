#ifndef GAME_H
#define GAME_H

class game;
enum GameState;

#include <SFML/Graphics.hpp>
#include <iostream>
#include "program.h"
#include "hitbox.h"
#include "background.h"
#include "gui.h"
#include "enemy.h"
#include "nest.h"
#include "flamingo.h"
#include "pickups.h"
#include "sound.h"
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
	
#if _DEBUG
	void drawDebugInfo(sf::RenderWindow *window);
#endif

	al::input* m_input;

private:
	sf::RenderWindow *window;
	al::viewport* m_viewport;
	
	al::vector m_ReturnPosition, m_ReturnOrigin;
	al::texture *m_ReturnTexture;
	al::sprite m_ReturnCheck;
	
	al::vector m_scorePosition, m_scoreOrigin;
	al::texture *m_scoreTexture;
	al::sprite m_Score;

	al::vector m_GmenuPosition, m_GmenuOrigin;
	al::texture *m_GmenuTexture;
	al::sprite m_GMenu;
	
	al::vector m_creditsPosition, m_creditsOrigin;
	al::texture *m_creditsTexture;
	al::sprite m_credits;

	al::vector m_optionsPosition, m_optionsOrigin;
	al::texture *m_optionsTexture;
	al::sprite m_options;

	al::texture* m_logoTexture;
	al::sprite m_logoSprite;
	al::vector m_logoPosition;

	al::texture* m_gameoverTexture;
	al::sprite m_gameoverSprite;
	al::vector m_gameoverPosition;

	al::texture* m_counterTexture;
	al::sprite m_counterSprite;
	al::vector m_counterPosition;

	al::texture* m_tutorial1Texture;
	al::sprite m_tutorial1;
	al::vector m_tutorial1Position;
	
	al::texture* m_tutorial2Texture;
	al::sprite m_tutorial2;
	al::vector m_tutorial2Position;

	al::texture* m_tutorial3Texture;
	al::sprite m_tutorial3;
	al::vector m_tutorial3Position;
	
	al::texture* m_tutorial4Texture;
	al::sprite m_tutorial4;
	al::vector m_tutorial4Position;
	
	al::font* m_font; //perusfontti
	al::font* m_font2; // ArialBlack "valikkofontti"

	bool P_release;
	bool M_release;
	bool ML_release;
	bool m_flamingoHeadPressed;
	bool m_muted;
	bool m_countingEggs;
	int m_tutorialNumber;
	float m_timer;
	int m_countSpeed;
	// gameStates

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

	// particles
	particleEngine* m_particleEngine;


	////sound
	soundLibrary* m_soundLibrary;


	al::texture m_pauseOpacityTexture;
	al::sprite m_pauseOpacitySprite;

	friend class gui;
};

enum GameState
{
	TitleScreen = 0,
	Play,
	Levelscore,
	GameOver,
	Menu,
	Tutorial,
	Credits,
	Options,
	Gamemenu,
	ReturnTitle,
	Quit
};

#endif