#include "program.h"


using namespace al;

#pragma region Vector

vector::vector()
	: x(0), y(0)
{}

vector::vector(sf::Vector2f sfVector)
{
	x = sfVector.x;
	y = sfVector.y;
}

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
	left = 0;
	top = 0;
	width = 0;
	height = 0;
}
rectangle::rectangle(float Left, float Top, float Width, float Height)
{
	//sf::Rect<float> asdf(,);
	left = Left;
	top = Top;
	width = Width;
	height = Height;
}
rectangle::rectangle(vector Position, float Width, float Height)
{
	left = Position.x;
	top = Position.y;
	width = Width;
	height = Height;
}
rectangle::rectangle(vector Position, vector Size)
{
	left = Position.x;
	top = Position.y;
	width = Size.x;
	height = Size.y;
}
rectangle::~rectangle()
{}

bool rectangle::intersects(rectangle Rectangle)
{
	return sf::Rect<float>(width, height, left, top).intersects(sf::Rect<float>(Rectangle.width, Rectangle.height, Rectangle.left, Rectangle.top));
}
bool rectangle::contains(vector Position)
{
	return sf::Rect<float>(width, height, left, top).contains(sf::Vector2<float>(Position.x, Position.y));
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
	  m_layer(0),
	  m_originPoint(0)
{
	m_sprite = new sf::Sprite();
}

sprite::sprite(al::texture *Texture)
	: m_layer(0),
	  m_originPoint(0)
{
	m_sprite = new sf::Sprite();
	setTexture(Texture);
}

sprite::~sprite()
{
	std::cout<<"deleting sprite"<<std::endl;
	delete m_sprite;
}

void sprite::setTexture(al::texture *Texture)
{
	m_sprite->setTexture(*Texture->m_texture); 
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
void sprite::setOriginPoint(int Point)
{
	if (0 < Point && Point < 10)
		m_originPoint = Point;
	else 
		m_originPoint = 0;

	switch (Point)
	{
	case 1:
		m_sprite->setOrigin(m_sprite->getLocalBounds().width * 0.0f, m_sprite->getLocalBounds().height * 1.0f);
		break;
	case 2:
		m_sprite->setOrigin(m_sprite->getLocalBounds().width * 0.5f, m_sprite->getLocalBounds().height * 1.0f);
		break;
	case 3:
		m_sprite->setOrigin(m_sprite->getLocalBounds().width * 1.0f, m_sprite->getLocalBounds().height * 1.0f);
		break;
	case 4:
		m_sprite->setOrigin(m_sprite->getLocalBounds().width * 0.0f, m_sprite->getLocalBounds().height * 0.5f);
		break;
	case 5:
		m_sprite->setOrigin(m_sprite->getLocalBounds().width * 0.5f, m_sprite->getLocalBounds().height * 0.5f);
		break;
	case 6:
		m_sprite->setOrigin(m_sprite->getLocalBounds().width * 1.0f, m_sprite->getLocalBounds().height * 0.5f);
		break;
	case 7:
		m_sprite->setOrigin(m_sprite->getLocalBounds().width * 0.0f, m_sprite->getLocalBounds().height * 0.0f);
		break;
	case 8:
		m_sprite->setOrigin(m_sprite->getLocalBounds().width * 0.5f, m_sprite->getLocalBounds().height * 0.0f);
		break;
	case 9:
		m_sprite->setOrigin(m_sprite->getLocalBounds().width * 1.0f, m_sprite->getLocalBounds().height * 0.0f);
		break;
	default:
		m_sprite->setOrigin(0,0);
		std::cout<<"Sprite origin out of range, origin set to top left"<<std::endl;
		break;
	}
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
	vector qwerty(m_sprite->getLocalBounds().width, m_sprite->getLocalBounds().height);
	return vector(m_sprite->getLocalBounds().width, m_sprite->getLocalBounds().height);
}
vector sprite::getTransformedSize()
{
	sf::Rect<float> asdofi = m_sprite->getGlobalBounds();
	vector qwerty(m_sprite->getGlobalBounds().width, m_sprite->getGlobalBounds().height);
	return vector(m_sprite->getGlobalBounds().width, m_sprite->getGlobalBounds().height);
}
void sprite::setTextureRectangle(rectangle Rectangle)
{
	int left = Rectangle.left;
	int top = Rectangle.top;
	int width = Rectangle.width;
	int height = Rectangle.height;
	m_sprite->setTextureRect(sf::IntRect(left,top,width,height));
}

vector sprite::getTextureSize()
{
	vector qwerty(m_sprite->getTexture()->getSize().x,m_sprite->getTexture()->getSize().y);
	return vector(m_sprite->getTexture()->getSize().x,m_sprite->getTexture()->getSize().y);
}

#pragma endregion

#pragma region Viewport

viewport::viewport(sf::RenderWindow* window)
	: m_window(window)
{}

viewport::~viewport()
{}

void viewport::draw(al::sprite* Sprite)
{
	m_layer[Sprite->m_layer].push_back(Sprite);
}

void viewport::renderSprites()
{
 	for (int i = 0; i < 1001; ++i)
	{
		for(int j = 0; j < m_layer[i].size(); ++j)
		{
			m_window->draw(*m_layer[i][j]->m_sprite);
		}
		m_layer[i].clear();
	}
}

#pragma endregion

#pragma endregion