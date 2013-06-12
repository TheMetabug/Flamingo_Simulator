#ifndef HEAD_H
#define HEAD_H

#include <SFML/Graphics.hpp>
#include <iostream>


class head
{
public:
	head(){}
	head(sf::RenderWindow *Window);
	~head();
	void update(sf::Time DeltaTime);
	void draw();
private:
	sf::RenderWindow *window;

	sf::Vector2f mousePosition, headPosition, headOrigin, crossHair;

	int drag;

	sf::Texture *headTexture;
	sf::Sprite flamingoHead;

	sf::Texture *crossTexture;
	sf::Sprite crosshairSprite;
};



#endif