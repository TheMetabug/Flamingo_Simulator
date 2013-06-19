#ifndef FLAMINGO_H
#define FLAMINGO_H

#include <SFML/Graphics.hpp>
#include <iostream>
#include "hitbox.h"

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

////////////////////////////////

class neck
{
public:
	neck(){}
	neck(sf::RenderWindow *Window);
	~neck();
	void update(float DeltaTime);
	void draw();
private:
	sf::RenderWindow *window;

	sf::Vector2f neckPosition, neckOrigin;

	sf::Texture *neckTexture;
	sf::Sprite flamingoNeck;
	
};

//////////////////////////////////////
class flamingo
{
	public:
	
	private:
	

};
/////////////////////////////////////
class head
{
public:
	head(){}
	head(sf::RenderWindow *Window, collision* Collide);
	~head();
	void update(float DeltaTime);
	void draw();
private:
	sf::RenderWindow *window;

	hitbox *headHitbox;

	sf::Vector2f mousePosition, headPosition, headOrigin, crossHair;

	int drag;

	sf::Texture *headTexture;
	sf::Sprite flamingoHead;
	sf::Texture *crossTexture;
	sf::Sprite crosshairSprite;
};
#endif