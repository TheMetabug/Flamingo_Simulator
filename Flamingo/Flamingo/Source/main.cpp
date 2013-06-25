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
//#include "renderStatistics.h"

int main()
{
	srand(time(NULL));
	bool Debugging = false;
	bool F1Released = false;

	// Set window parametres
	

    sf::RenderWindow *window = new sf::RenderWindow(sf::VideoMode(1280, 720), "Flamingo Simulator 2013");
	//window->setFramerateLimit(120);

	// Deltatime stuff
	sf::Clock clock;
	sf::Time dt;

	game MainGame(window);
	renderStatistics m_renderStatistics(window);


	// Run the program as long as the window is open
    while (window->isOpen())
    {
		
		if(!sf::Keyboard::isKeyPressed(sf::Keyboard::F1))
			F1Released = true;
		else if (F1Released)
		{
			F1Released = false;
			Debugging = !Debugging;
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
        }

		// Update

		MainGame.update(dt);

		m_renderStatistics.update(dt);

		// Draw

		window->clear(sf::Color::Transparent);

		MainGame.draw();

		if (Debugging)
		{
			m_renderStatistics.draw();
			MainGame.drawDebugInfo();
		}


		//end the current frame
        window->display();

		dt = clock.restart();
    }

	delete window;

    return 0;
}