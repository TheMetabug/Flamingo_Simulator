#ifndef BACKGROUND_H
#define BACKGROUND_H

#include <SFML/Graphics.hpp>
#include <iostream>
#include "program.h"

class background
{
public:
	//background(){}
	background();
	~background();
	void update(float DeltaTime);
	void draw(al::viewport* Viewport);

private:
	//sf::RenderWindow *window;

	sf::Vector2f m_waterPosition;

	al::texture* m_skyTexture;
	al::sprite m_sky;

	al::texture* m_waterTexture;
	al::sprite m_water;

	al::texture* m_groundTexture;
	al::sprite m_ground;

};

class cloud
{
public:
	//cloud(){}
	cloud();
	~cloud();
	void update(float DeltaTime);
	void draw(al::viewport* Viewport);

private:
	//sf::RenderWindow *window;

	al::texture* m_cloudTexture_1;
	al::sprite m_cloud_1;
	
	al::texture* m_cloudTexture_2;
	al::sprite m_cloud_2;

	al::texture* m_cloudTexture_3;
	al::sprite m_cloud_3;

	


};

#endif