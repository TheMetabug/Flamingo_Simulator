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
	
    sf::RenderWindow window(sf::VideoMode(1280, 720), "Flamingo Simulator 2013");
	al::viewport viewport(&window);
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

	game MainGame(&window, &viewport);
	renderStatistics m_renderStatistics(&window);


	// Run the program as long as the window is open
    while (window.isOpen())
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
			window.close();
		}

        sf::Event event;
        while (window.pollEvent(event))
        {
			// This is called when window is closed
            if (event.type == sf::Event::Closed)
			{
                window.close();
			}
        }

		// Update

		deltaTime = dt.asMicroseconds()/1000000.0f;
		MainGame.update(deltaTime);
		m_renderStatistics.update(dt);

		// Draw

		window.clear(sf::Color::Transparent);

		MainGame.draw();

		if (FPS)
		{
			m_renderStatistics.draw();
		}

		if (Hitbox)
		{
			MainGame.drawDebugInfo();
		}


		//end the current frame
        window.display();

		dt = clock.restart();

    }


    return 0;
}