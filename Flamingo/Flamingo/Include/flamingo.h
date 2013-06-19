#ifndef FLAMINGO_H
#define FLAMINGO_H

#include <SFML/Graphics.hpp>
#include <iostream>

class body
{
public:
	body(){}
	body(sf::RenderWindow *Window);
	~body();
	void update(float DeltaTime);
	void draw();
private:
	sf::RenderWindow *window;

	sf::Vector2f bodyPosition, bodyOrigin;

	sf::Texture *bodyTexture;
	sf::Sprite flamingoBody;

};

//new class
class flamingo
{
	public:
	
	private:
	

};

#endif