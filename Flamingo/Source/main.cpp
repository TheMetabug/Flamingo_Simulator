/*
**
**
**
*/

// Copyright Asko Lahti, Esko Haila, Iida Korpela, Hanna Karvonen, Aleksi Jeskanen, Aleksi Jokihaara
// SFML is copyrighted to respective owners
#include <SFML/Graphics.hpp>
#include <iostream>

int main()
{
    sf::RenderWindow window(sf::VideoMode(1280, 720), "Flamingo Simulator 2013");
    sf::CircleShape shape(100.f);
	shape.setFillColor(sf::Color::Magenta);
	std::cout << "Kirjoitetaampas kommentti" << std::endl;

	// Run the program as long as the window is open
    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
			// This is called when window is closed
            if (event.type == sf::Event::Closed)
                window.close();

        }

		

        window.clear();

		// Put draw functions here
        window.draw(shape);


		//end the current frame
        window.display();
    }

    return 0;
}