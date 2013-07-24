/*
**
**
**
*/

// Copyright Asko Lahti, Esko Haila, Iida Korpela, Hanna Karvonen, Aleksi Jeskanen, Aleksi Jokihaara
// SFML is copyrighted to respective owners
#include <SFML/Graphics.hpp>
#include <iostream>
#include <Windows.h>
#include "game.h"
#include "program.h"

//music
#include <SFML/Audio.hpp>

#if _DEBUG
#include "renderStatistics.h"
#endif

int main()
{
	al::SCREENX = GetSystemMetrics(SM_CXSCREEN);
	al::SCREENY = GetSystemMetrics(SM_CYSCREEN);


	srand(unsigned int(time(NULL)));

#if _DEBUG
	bool F1Released = false;
	bool F2Released = false;

	bool FPS = false;
	bool Hitbox = false;
#else
	HWND hwnd = GetConsoleWindow();
	ShowWindow(hwnd, SW_HIDE);
#endif

	// Set window parametres
	
	sf::RenderWindow* window = new sf::RenderWindow(sf::VideoMode(al::SCREENX, al::SCREENY), "Flamia", sf::Style::Fullscreen);
	sf::Image icon;
	if (icon.loadFromFile("Assets/icon.png"))
		window->setIcon(64,64,icon.getPixelsPtr());
	sf::View view(sf::Vector2f(WINDOW_WIDTH/2,WINDOW_HEIGHT/2),sf::Vector2f(WINDOW_WIDTH,WINDOW_HEIGHT));
	window->setView(view);
	al::viewport* viewport = new al::viewport(window);
	//window->setFramerateLimit(120);

	////sound

	//sf::SoundBuffer m_buffer;
	//sf::Sound m_sound;
	//m_buffer.loadFromFile("Assets/jungle.wav");

	//m_sound.setBuffer(m_buffer);
	//m_sound.play();
	//m_sound.setLoop(true);

	// Deltatime stuff
	sf::Clock clock;
	sf::Time dt;
	float deltaTime;
	
	window->clear(sf::Color::Transparent);
	game MainGame(window, viewport);
	viewport->renderSprites();
#if _DEBUG
	renderStatistics m_renderStatistics(window);
#endif
    window->display();
	MainGame.init();




	// Run the program as long as the window is open
    while (window->isOpen())
    {
#if _DEBUG
		if(!sf::Keyboard::isKeyPressed(sf::Keyboard::F1))
			F1Released = true;
		else if (F1Released)
		{
			F1Released = false;
			FPS = !FPS;
		}
		
		if(!sf::Keyboard::isKeyPressed(sf::Keyboard::F2))
			F2Released = true;
		else if (F2Released)
		{
			F2Released = false;
			Hitbox = !Hitbox;
		}
#endif

		//if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
		//{
		//	window->close();
		//}

        sf::Event event;
        while (window->pollEvent(event))
        {
			// This is called when window is closed
            if (event.type == sf::Event::Closed)
			{
                window->close();
			}

			if (event.type == sf::Event::LostFocus)
			{
#if _DEBUG
				std::cout<<"lost focus ";
#endif
				MainGame.m_input->active = false;
			}

			if (event.type == sf::Event::GainedFocus)
			{
#if _DEBUG
				std::cout<<"gain focus ";
#endif
				MainGame.m_input->active = true;
			}
        }

		// Update

		deltaTime = dt.asMicroseconds()/1000000.0f;
		MainGame.update(deltaTime);

#if _DEBUG
		m_renderStatistics.update(dt);
#endif

		// Draw

		window->clear(sf::Color::Transparent);

		MainGame.draw();

		viewport->renderSprites();
		
#if _DEBUG
		if (FPS)
		{
			m_renderStatistics.draw();
		}

		if (Hitbox)
		{
			MainGame.drawDebugInfo(window);
		}
#endif



		//end the current frame
        window->display();

		dt = clock.restart();

    }


    return 0;
}