#include "program.h"


using namespace al;

#pragma region Vector

vector::vector()
	: x(0), y(0)
{}

vector::vector(float X, float Y)
	: x(X), y(Y)
{}

vector::~vector(){}

#pragma region operators

vector operator-(const vector& RightVal)
{
	return vector(-RightVal.x,-RightVal.y);
}

vector operator +(const vector& LeftVal, const vector& RightVal)
{
	return vector(LeftVal.x+RightVal.x,LeftVal.y+RightVal.y);
}
vector operator -(const vector& LeftVal, const vector& RightVal)
{
	return vector(LeftVal.x-RightVal.x,LeftVal.y-RightVal.y);
}

vector& operator +=(vector& LeftVal, const vector& RightVal)
{
	LeftVal.x += RightVal.x;
	LeftVal.y += RightVal.y;
	return LeftVal;
}
vector& operator -=(vector& LeftVal, const vector& RightVal)
{
	LeftVal.x -= RightVal.x;
	LeftVal.y -= RightVal.y;
	return LeftVal;
}

vector operator *(const vector& LeftVal, float RightVal)
{
	return vector(LeftVal.x * RightVal,LeftVal.y * RightVal);
}
vector operator *(float LeftVal, const vector& RightVal)
{
	return vector(LeftVal * RightVal.x,LeftVal * RightVal.y);
}

vector& operator *=(vector& LeftVal, float RightVal)
{
	LeftVal.x *= RightVal;
	LeftVal.y *= RightVal;
	return LeftVal;
}

vector operator /(const vector& LeftVal, float RightVal)
{
	return vector(LeftVal.x / RightVal,LeftVal.y / RightVal);
}
vector& operator /=(vector& LeftVal, float RightVal)
{
	LeftVal.x /= RightVal;
	LeftVal.y /= RightVal;
	return LeftVal;
}

bool operator ==(const vector& LeftVal, const vector& RightVal)
{
	if (LeftVal.x == RightVal.x && LeftVal.y == RightVal.y)
		return true;
	return false;
}
bool operator !=(const vector& LeftVal, const vector& RightVal)
{
	if (LeftVal.x == RightVal.x && LeftVal.y == RightVal.y)
		return false;
	return true;
}

#pragma endregion

#pragma endregion

#pragma region Rectangle

rectangle::rectangle()
{
	m_rectangle.width = 0;
	m_rectangle.height = 0;
	m_rectangle.left = 0;
	m_rectangle.top = 0;
}
rectangle::rectangle(float Width, float Height, float Left, float Top)
{
	m_rectangle.width = Width;
	m_rectangle.height = Height;
	m_rectangle.left = Left;
	m_rectangle.top = Top;
}
rectangle::rectangle(float Width, float Height, vector Position)
{
	m_rectangle.width = Width;
	m_rectangle.height = Height;
	m_rectangle.left = Position.x;
	m_rectangle.top = Position.y;
}
rectangle::rectangle(vector Size, vector Position)
{
	m_rectangle.width = Size.x;
	m_rectangle.height = Size.y;
	m_rectangle.left = Position.x;
	m_rectangle.top = Position.y;
}
rectangle::~rectangle()
{}

void rectangle::setWidth(float Width)
{
	m_rectangle.width = Width;
}
void rectangle::setHeight(float Height)
{
	m_rectangle.height = Height;
}
void rectangle::setLeft(float Left)
{
	m_rectangle.left = Left;
}
void rectangle::setTop(float Top)
{
	m_rectangle.top = Top;
}
void rectangle::setSize(vector Size)
{
	m_rectangle.width = Size.x;
	m_rectangle.height = Size.y;
}
void rectangle::setPosition(vector Position)
{
	m_rectangle.left = Position.x;
	m_rectangle.top = Position.y;
}
float rectangle::getWidth()
{
	return m_rectangle.width;
}
float rectangle::getHeight()
{
	return m_rectangle.height;
}
float rectangle::getLeft()
{
	return m_rectangle.left;
}
float rectangle::getTop()
{
	return m_rectangle.top;
}
vector rectangle::getSize()
{
	return vector(m_rectangle.width, m_rectangle.height);
}
vector rectangle::getPosition()
{
	return vector(m_rectangle.left, m_rectangle.top);
}
bool rectangle::intersects(rectangle Rectangle)
{
	return m_rectangle.intersects(Rectangle.m_rectangle);
}
bool rectangle::contains(vector Position)
{
	return m_rectangle.contains(Position.x, Position.y);
}

#pragma endregion

#pragma region Drawing Methods

#pragma region Texture

texture::texture()
	: m_texture(NULL)
{}

texture::texture(std::string TextureName)
{
	loadTexture(TextureName);
}

texture::~texture()
{
	delete m_texture;
}

void texture::loadTexture(std::string TextureName)
{
	m_texture = new sf::Texture();
	m_texture->loadFromFile("Assets/" + TextureName);
	m_texture->setSmooth(true);
}

#pragma endregion

#pragma region Sprite

sprite::sprite()
	: m_sprite(NULL),
	  m_layer(0)
{}

sprite::sprite(al::texture Texture)
	: m_layer(0)
{
	setTexture(Texture);
}

sprite::~sprite()
{
	delete m_sprite;
}

void sprite::setTexture(al::texture Texture)
{
	m_sprite = new sf::Sprite();
	m_sprite->setTexture(*Texture.m_texture); 
}

void sprite::setPosition(al::vector Position)
{
	sf::Vector2f pos(Position.x,Position.y);
	m_sprite->setPosition(pos);
}

void sprite::setOrigin(al::vector Origin)
{
	sf::Vector2f pos(Origin.x,Origin.y);
	m_sprite->setOrigin(pos);
}

void sprite::setScale(float ScaleX, float ScaleY)
{
	m_sprite->setScale(ScaleX,ScaleY);
}
void sprite::setScale(float Scale)
{
	setScale(Scale,Scale);
}
void sprite::setScale(vector Scale)
{
	setScale(Scale.x,Scale.y);
}
void sprite::setLayer(int Layer)
{
	if (Layer >= 0 && Layer <= 1000)
		m_layer = Layer;
	else if (Layer < 0)
		m_layer = 0;
	else if (Layer > 1000)
		m_layer = 1000;
}
vector sprite::getSize()
{
	return vector(m_sprite->getLocalBounds().width, m_sprite->getLocalBounds().height);
}
vector sprite::getTransformedSize()
{
	return vector(m_sprite->getGlobalBounds().width, m_sprite->getGlobalBounds().height);
}

#pragma endregion

#pragma region Viewport

viewport::viewport(sf::RenderWindow* window)
	: m_window(window)
{}

viewport::~viewport()
{}

void viewport::addSprite(al::sprite* Sprite)
{
	m_layer[Sprite->m_layer].push_back(Sprite);
}

void viewport::draw()
{
	for (int i = 0; i < 1000; ++i)
	{
		for(int j = m_layer[i].size()-1; j >= 0; --j)
		{
			m_window->draw(*m_layer[i][j]->m_sprite);

			m_layer[i].erase(m_layer[i].begin() + j);
		}
	}
}

#pragma endregion

#pragma endregion