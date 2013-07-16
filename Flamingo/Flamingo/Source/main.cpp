/*
**
**
**
*/

// Copyright Asko Lahti, Esko Haila, Iida Korpela, Hanna Karvonen, Aleksi Jeskanen, Aleksi Jokihaara
// SFML is copyrighted to respective owners
#include <SFML/Graphics.hpp>
#include <iostream>
#include "game.h"
#include "program.h"

//music
#include <SFML/Audio.hpp>

//#include "renderStatistics.h"

int main()
{
	srand(time(NULL));

	bool F1Released = false;
	bool F2Released = false;

	bool FPS = false;
	bool Hitbox = false;

	// Set window parametres
	
    sf::RenderWindow* window = new sf::RenderWindow(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), "Flamia");
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
	renderStatistics m_renderStatistics(window);
    window->display();
	MainGame.init();




	// Run the program as long as the window is open
    while (window->isOpen())
    {
		
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

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
		{
			window->close();
		}

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
				std::cout<<"lost focus ";
				MainGame.m_input->active = false;
			}

			if (event.type == sf::Event::GainedFocus)
			{
				std::cout<<"gain focus ";
				MainGame.m_input->active = true;
			}
        }

		// Update

		deltaTime = dt.asMicroseconds()/1000000.0f;
		MainGame.update(deltaTime);
		m_renderStatistics.update(dt);

		// Draw

		window->clear(sf::Color::Transparent);

		MainGame.draw();

		viewport->renderSprites();

		if (FPS)
		{
			m_renderStatistics.draw();
		}

		if (Hitbox)
		{
			MainGame.drawDebugInfo(window);
		}


		//end the current frame
        window->display();

		dt = clock.restart();

    }


    return 0;
}