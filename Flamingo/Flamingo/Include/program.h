#ifndef PROGRAM_H
#define PROGRAM_H

#include <SFML/Graphics.hpp>
#include <iostream>

namespace al
{

#pragma region Vector

class vector
{
public:

	vector();
	vector(float X, float Y);
	~vector();

	float x,y;

private:

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

#pragma endregion

#pragma region Rectangle

class rectangle
{
public:
	rectangle();
	rectangle(float Width, float Height, float Left, float Top);
	rectangle(float Width, float Height, vector Position);
	rectangle(vector Size, vector Position);
	void setWidth(float Width);
	void setHeight(float Height);
	void setLeft(float Left);
	void setTop(float Top);
	void setSize(vector Size);
	void setPosition(vector Position);
	float getWidth();
	float getHeight();
	float getLeft();
	float getTop();
	vector getSize();
	vector getPosition();
	bool intersects(rectangle Rectangle);
	bool contains(vector Position);

	~rectangle();
	
private:
	sf::Rect<float> m_rectangle;
};

#pragma endregion

#pragma region Drawing Methods

#pragma region Texture

class texture
{
public:
	texture();
	texture(std::string TextureName);
	~texture();

	void loadTexture(std::string TextureName);

private:
	sf::Texture* m_texture;
	friend class sprite;
};

#pragma endregion

#pragma region Sprite

class sprite
{
public:
	sprite();
	sprite(al::texture Texture);
	~sprite();

	void setTexture(al::texture Texture);
	void setPosition(al::vector Position);
	void setOrigin(al::vector Origin);
	void setScale(float ScaleX, float ScaleY);
	void setScale(float Scale);
	void setScale(vector Scale);
	void setLayer(int Layer);
	vector getSize();
	vector getTransformedSize();
	

private:
	sf::Sprite* m_sprite;
	int m_layer;
	friend class viewport;
};

#pragma endregion

#pragma region Viewport

class viewport
{
public:
	viewport(sf::RenderWindow *window);
	~viewport();

	void addSprite(al::sprite* Sprite);
	void draw();

private:
	sf::RenderWindow* m_window;
	std::vector<sprite*> m_layer[1001];
};

#pragma endregion

#pragma endregion

}

#endif