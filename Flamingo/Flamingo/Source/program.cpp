#include "program.h"


using namespace al;

vector::vector()
	: x(0), y(0)
{}
vector::vector(float X, float Y)
	: x(X), y(Y)
{}

//Operators
#pragma region Vector Operators
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

#pragma endregion yippee


//float vector::X()
//{
//	return m_vector.x;
//}
//float vector::Y()
//{
//	return m_vector.y;
//}
//
//void vector::X(float X)
//{
//	m_vector.x = X;
//}
//void vector::Y(float Y)
//{
//	m_vector.y = Y;
//}


vector::~vector(){}


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
	//m_animation = new animation(m_testbuttonS, 3, 96, 96, false, 0);
	//m_sprite->setPosition(m_testbuttonPos);
	//m_sprite->setOrigin(sf::Vector2f(m_testbuttonS->getLocalBounds().width/2,
	//					     m_testbuttonS->getLocalBounds().height/2));
	//m_testbuttonS->setScale(1,1);
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