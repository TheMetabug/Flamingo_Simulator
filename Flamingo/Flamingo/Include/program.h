#ifndef PROGRAM_H
#define PROGRAM_H

#include <SFML/Graphics.hpp>
#include <iostream>

namespace al
{

class vector
{
public:

	vector();
	vector(float X, float Y);
	~vector();


	////get
	//float X();
	//float Y();

	////set
	//void X(float X);
	//void Y(float Y);

	float x,y;


private:

	sf::Vector2f m_vector;
};
vector operator -(const vector& RightVal);

vector operator +(const vector& LeftVal, const vector& RightVal);
vector operator -(const vector& LeftVal, const vector& RightVal);

vector& operator +=(vector& LeftVal, const vector& RightVal);
vector& operator -=(vector& LeftVal, const vector& RightVal);

vector operator *(const vector& LeftVal, float RightVal);
vector operator *(float LeftVal, const vector& RightVal);

vector& operator *=(vector& LeftVal, float RightVal);

vector operator /(const vector& LeftVal, float RightVal);
vector& operator /=(vector& LeftVal, float RightVal);

bool operator ==(const vector& LeftVal, const vector& RightVal);
bool operator !=(const vector& LeftVal, const vector& RightVal);


class texture
{
public:
	texture();
	texture(std::string TextureName);
	~texture();

	void loadTexture(std::string TextureName);

protected:
	sf::Texture* m_texture;
	friend class sprite;
};

class sprite
{
public:
	sprite();
	sprite(al::texture Texture);
	~sprite();

	void setTexture(al::texture Texture);
	void setPosition(al::vector Position);
	void setOrigin(al::vector Origin);

protected:
	sf::Sprite* m_sprite;
	int m_layer;
	friend class viewport;
};

class viewport
{
public:
	viewport(sf::RenderWindow *window);
	~viewport();

	void addSprite(al::sprite* Sprite);
	void draw();

private:
	sf::RenderWindow* m_window;
	std::vector<sprite*> m_layer[1000];

};



}

#endif