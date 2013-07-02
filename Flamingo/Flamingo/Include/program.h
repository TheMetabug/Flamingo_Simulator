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
	vector(sf::Vector2f sfVector);
	vector(sf::Vector2i sfVector);
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
	rectangle(float Left, float Top, float Width, float Height);
	rectangle(vector Position, float Width, float Height);
	rectangle(vector Position, vector Size);
	rectangle(sf::FloatRect Rect);

	bool intersects(rectangle Rectangle);
	bool contains(vector Position);

	~rectangle();
	float width, height, left, top;
private:
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
	texture(texture& Texture);
	sf::Texture* m_texture;
	friend class sprite;
};

#pragma endregion

#pragma region Sprite

class sprite
{
public:
	sprite();
	sprite(al::texture* Texture);
	~sprite();

	void setTexture(al::texture* Texture);
	void setPosition(al::vector Position);
	void setOrigin(al::vector Origin);
	/*Set Origin Point according to location on numpad*/
	void setOriginPoint(int Point);
	void setScale(float ScaleX, float ScaleY);
	void setScale(float Scale);
	void setScale(vector Scale);
	/*Layer 0-1000*/
	void setLayer(int Layer);
	vector getPosition();
	vector getOrigin();
	vector getScale();
	vector getSize();
	vector getTransformedSize();
	rectangle getGlobalBounds();
	void setTextureRectangle(rectangle Rectangle);
	vector getTextureSize();

private:
	sprite(sprite& Sprite);
	sf::Sprite* m_sprite;
	int m_originPoint;
	int m_layer;
	friend class viewport;
};

#pragma endregion

#pragma region Font

class font
{
public:
	font();
	font(std::string Filename);
	~font();
	void loadFromFile(std::string Filename);
private:
	font(font& Font);
	sf::Font* m_font;
	friend class text;
};

#pragma endregion

#pragma region Text

class text
{
public:
	text();
	text(const std::string string, al::font* Font, unsigned int CharacterSize = 30);
	~text();

	void setFont(al::font* Font);
	void setString(std::string string);
	void setColor(unsigned int Red = 255, unsigned int Green = 255, unsigned int Blue = 255, unsigned int Alpha = 255);
	void setPosition(al::vector Position);
	void setOrigin(al::vector Origin);
	/*Set Origin Point according to location on numpad*/
	void setOriginPoint(int Point);
	void setScale(float ScaleX, float ScaleY);
	void setScale(float Scale);
	void setScale(vector Scale);
	/*Layer 0-1000*/
	void setLayer(int Layer);

	vector getPosition();
	vector getOrigin();
	vector getScale();
	vector getSize();
	vector getTransformedSize();
	rectangle getGlobalBounds();

private:
	text(text& Text);
	sf::Text* m_text;
	int m_originPoint;
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
	
	void draw(al::sprite* Sprite);
	void draw(al::text* Text);
	void renderSprites();

private:
	sf::RenderWindow* m_window;
	std::vector<sprite*> m_spriteLayer[1001];
	std::vector<text*> m_textLayer[1001];
};

#pragma endregion

#pragma endregion

}

#endif