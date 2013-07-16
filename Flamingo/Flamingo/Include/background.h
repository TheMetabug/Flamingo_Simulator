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

	al::vector m_waterPosition;

	al::texture* m_skyTexture;
	al::sprite m_sky;

	al::texture* m_waterTexture;
	al::sprite m_water;

	al::texture* m_opacityTexture;
	al::sprite m_waterOpacity;

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

	std::vector<al::texture*> m_cloudsTexture;
	std::vector<al::sprite*> m_clouds;
	std::vector<al::vector> m_cloudPositions;

	float m_startPosition_x, m_respawnPosition_x, m_startPosition_y, m_respawnPosition_y;
};

class tree
{

public:
	tree(al::vector Scale, al::vector Position, float speed);
	~tree();
	void update(float DeltaTime);
	void draw(al::viewport* Viewport);

private:
	al::texture* m_treeTexture;
	al::sprite* m_treeSprite;
	al::vector m_treePosition;
	al::vector m_treeScale;

	float m_rotation, m_timer, m_speed;

};

#endif