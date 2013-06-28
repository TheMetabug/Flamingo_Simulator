#ifndef PROGRAM_H
#define PROGRAM_H

#include <SFML/Graphics.hpp>
#include <iostream>

namespace al
{


class vector
{};

class texture
{
public:
	texture(std::string TextureName);
	~texture();

	void loadTexture(std::string TextureName);

private:
	sf::Texture m_texture;
};

class sprite
{
public:
	sprite(texture);
	~sprite();

private:
	sf::Sprite m_sprite;
};

class viewport
{
public:
	viewport(sf::RenderWindow *window);
	~viewport();


private:
	sf::RenderWindow* m_window;

};



}

#endif