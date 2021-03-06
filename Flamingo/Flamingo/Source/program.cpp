#include "program.h"
#define PI 3.14159265358979323846264


using namespace al;

// Vector
vector::vector()
	: x(0), y(0)
{}
vector::vector(sf::Vector2f sfVector)
{
	x = (float)sfVector.x;
	y = (float)sfVector.y;
}
vector::vector(sf::Vector2i sfVector)
{
	x = (float)sfVector.x;
	y = (float)sfVector.y;
}
vector::vector(sf::Vector2u sfVector)
{
	x = (float)sfVector.x;
	y = (float)sfVector.y;
}
vector::vector(float X, float Y)
	: x(X), y(Y)
{}
vector::~vector(){}
float vector::getLenght()
{
	return sqrt(pow(x,2) + pow(y,2));
}
float vector::getAngle()
{
	if (x == 0)
	{
		if (y > 0)
			return 90;
		return 270;
	}
	else
	{
		float angle = float(atan(y/x)*(180.0f/PI));
		if (x < 0)
			angle += 180;
		else if (angle < 0)
			angle += 360;
		return angle;
	}
}
void vector::rotate(float Degrees)
{
	Degrees = fmod(Degrees,360);
	sf::Transform transform;
	transform.rotate(Degrees);
	vector rotated = transform.transformPoint(x,y);
	x = rotated.x;
	y = rotated.y;
}
#pragma region operators

vector vector::operator-()
{
	return vector(-this->x, -this->y);
}

vector vector::operator +(const vector& RightVal)
{
	return vector(this->x+RightVal.x,this->y+RightVal.y);
}
vector vector::operator -(const vector& RightVal)
{
	return vector(this->x-RightVal.x,this->y-RightVal.y);
}

vector &vector::operator +=(const vector& RightVal)
{
	this->x += RightVal.x;
	this->y += RightVal.y;
	return *this;
}
vector &vector::operator -=(const vector& RightVal)
{
	this->x -= RightVal.x;
	this->y -= RightVal.y;
	return *this;
}

vector vector::operator /(float RightVal)
{
	return vector(this->x / (float)RightVal,this->y / (float)RightVal);
}
vector &vector::operator /=(float RightVal)
{
	this->x /= (float)RightVal;
	this->y /= (float)RightVal;
	return *this;
}

bool vector::operator ==(const vector& RightVal)
{
	if (this->x == RightVal.x && this->y == RightVal.y)
		return true;
	return false;
}
bool vector::operator !=(const vector& RightVal)
{
	if (this->x == RightVal.x && this->y == RightVal.y)
		return false;
	return true;
}

namespace al
{

vector operator *(const vector& LeftVal, const float RightVal)
{
	return vector(LeftVal.x * RightVal,LeftVal.y * RightVal);
}
vector operator *(const float LeftVal, const vector& RightVal)
{
	return vector(LeftVal * RightVal.x,LeftVal * RightVal.y);
}

const vector &operator *=(vector& LeftVal, float RightVal)
{
	LeftVal.x *= RightVal;
	LeftVal.y *= RightVal;
	return LeftVal;
}

//void operator <<(std::ostream& Ostr, const vector RightVal)
//{
//    Ostr << "x:" << RightVal.x << ", y:" << RightVal.y << "";
//}

}

#pragma endregion

// Rectangle
rectangle::rectangle()
{
	left = 0;
	top = 0;
	width = 0;
	height = 0;
}
rectangle::rectangle(float Left, float Top, float Width, float Height)
{
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
rectangle::rectangle(sf::FloatRect Rect)
{
	left = Rect.left;
	top = Rect.top;
	width = Rect.width;
	height = Rect.height;
}
rectangle::~rectangle()
{}
bool rectangle::intersects(rectangle Rectangle)
{
	return sf::Rect<float>(left, top, width, height).intersects(sf::Rect<float>(Rectangle.left, Rectangle.top, Rectangle.width, Rectangle.height));
}
bool rectangle::contains(vector Position)
{
	return sf::Rect<float>(left, top, width, height).contains(sf::Vector2f(Position.x, Position.y));
}

// Texture
texture::texture()
	: m_texture(NULL)
{}
texture::texture(std::string TextureName)
	: m_texture(NULL)
{
	loadTexture(TextureName);
}
texture::~texture()
{
	delete m_texture;
}
void texture::loadTexture(std::string TextureName)
{
	if (m_texture == NULL)
	{
		m_texture = new sf::Texture();
		m_texture->loadFromFile("Assets/" + TextureName);
		m_texture->setSmooth(true);
	}
	else 
	{
#if _DEBUG
		std::cout<<"Texture already loaded";
#endif
	}
}

// Sprite
sprite::sprite()
	: m_layer(0),
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
#if _DEBUG
	std::cout<<"deleting sprite... ";
#endif
	delete m_sprite;
#if _DEBUG
	std::cout<<"done"<<std::endl;
#endif
}
void sprite::setTexture(al::texture *Texture)
{
	m_sprite->setTexture(*Texture->m_texture); 
}
void sprite::setTextureRectangle(rectangle Rectangle)
{
	int left = int(Rectangle.left + 0.5f);
	int top = int(Rectangle.top + 0.5f);
	int width = int(Rectangle.width + 0.5f);
	int height = int(Rectangle.height + 0.5f);
	m_sprite->setTextureRect(sf::IntRect(left,top,width,height));
}
vector sprite::getTextureSize()
{
	return vector((float)m_sprite->getTexture()->getSize().x,
		(float)m_sprite->getTexture()->getSize().y);
}

void sprite::setColor(unsigned int Red, unsigned int Green, unsigned int Blue, unsigned int Alpha)
{
	m_sprite->setColor(sf::Color((sf::Uint8)Red,(sf::Uint8)Green,(sf::Uint8)Blue,(sf::Uint8)Alpha));
}
void sprite::setPosition(al::vector Position)
{
	sf::Vector2f pos(Position.x,Position.y);
	m_sprite->setPosition(pos);
}
void sprite::setRotation(float Angle)
{
	m_sprite->setRotation(Angle);
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

	updateOrigin();
}
void sprite::updateOrigin()
{
	switch (m_originPoint)
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
#if _DEBUG
		std::cout<<"Sprite origin out of range, origin set to top left"<<std::endl;
#endif
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
	if (Layer >= 0 && Layer <= LAYER_COUNT)
		m_layer = Layer;
	else if (Layer < 0)
		m_layer = 0;
	else if (Layer > LAYER_COUNT)
		m_layer = LAYER_COUNT;
}
//vector sprite::getColor()
//{
//	return m_sprite->getColor(); fix this if u can
//}
vector sprite::getPosition()
{
	return m_sprite->getPosition();
}
vector sprite::getOrigin()
{
	return m_sprite->getOrigin();
}
vector sprite::getScale()
{
	return m_sprite->getScale();
}
vector sprite::getSize()
{
	vector qwerty(m_sprite->getLocalBounds().width, m_sprite->getLocalBounds().height);
	return vector(m_sprite->getLocalBounds().width, m_sprite->getLocalBounds().height);
}
vector sprite::getTransformedSize()
{
	sf::Rect<float> asdofi = m_sprite->getGlobalBounds();
	return vector(m_sprite->getGlobalBounds().width, m_sprite->getGlobalBounds().height);
}
rectangle sprite::getGlobalBounds()
{
	return rectangle(m_sprite->getGlobalBounds());
}

// Font
font::font()
{
	m_font = new sf::Font();
}
font::font(std::string Filename)
{
	m_font = new sf::Font();
	loadFromFile(Filename);
}
font::~font()
{
	delete m_font;
}
void font::loadFromFile(std::string Filename)
{
	m_font->loadFromFile("Assets/" + Filename);
}

// Text
text::text()
	: m_layer(0),
	  m_originPoint(0)
{
	m_text = new sf::Text();
}
text::text(const std::string string, al::font* Font, unsigned int CharacterSize)
	: m_layer(0),
	  m_originPoint(0)
{
	m_text = new sf::Text(string, *(Font->m_font), CharacterSize);
}
text::~text()
{
#if _DEBUG
	std::cout<<"deleting text... ";
#endif
	delete m_text;
#if _DEBUG
	std::cout<<"done"<<std::endl;
#endif
}
void text::setFont(al::font* Font)
{
	m_text->setFont(*(Font->m_font));
}
void text::setString(std::string string)
{
	m_text->setString(string);
}
void text::setCharacterSize(unsigned int CharacterSize)
{
	m_text->setCharacterSize(CharacterSize);
}
void text::setColor(unsigned int Red, unsigned int Green, unsigned int Blue, unsigned int Alpha)
{
	sf::Color color((sf::Uint8)Red, (sf::Uint8)Green, (sf::Uint8)Blue, (sf::Uint8)Alpha);
	m_text->setColor(color);
}
void text::setPosition(al::vector Position)
{
	sf::Vector2f pos(Position.x,Position.y);
	m_text->setPosition(pos);
}
void text::setOrigin(al::vector Origin)
{
	sf::Vector2f pos(Origin.x,Origin.y);
	m_text->setOrigin(pos);
}
void text::setOriginPoint(int Point)
{
	if (0 < Point && Point < 10)
		m_originPoint = Point;
	else 
		m_originPoint = 0;

	updateOrigin();
}
void text::updateOrigin()
{
	float charWidth = m_text->getCharacterSize()/12.0f;
	float charHeight = m_text->getCharacterSize()/3.8f;
	switch (m_originPoint)
	{
	case 1:
		m_text->setOrigin(charWidth + m_text->getGlobalBounds().width * 0.0f, charHeight + m_text->getGlobalBounds().height * 1.0f);
		break;
	case 2:
		m_text->setOrigin(charWidth + m_text->getGlobalBounds().width * 0.5f, charHeight + m_text->getGlobalBounds().height * 1.0f);
		break;
	case 3:
		m_text->setOrigin(charWidth + m_text->getGlobalBounds().width * 1.0f, charHeight + m_text->getGlobalBounds().height * 1.0f);
		break;
	case 4:
		m_text->setOrigin(charWidth + m_text->getGlobalBounds().width * 0.0f, charHeight + m_text->getGlobalBounds().height * 0.5f);
		break;
	case 5:
		m_text->setOrigin(charWidth + m_text->getGlobalBounds().width * 0.5f, charHeight + m_text->getGlobalBounds().height * 0.5f);
		break;
	case 6:
		m_text->setOrigin(charWidth + m_text->getGlobalBounds().width * 1.0f, charHeight + m_text->getGlobalBounds().height * 0.5f);
		break;
	case 7:
		m_text->setOrigin(charWidth + m_text->getGlobalBounds().width * 0.0f, charHeight + m_text->getGlobalBounds().height * 0.0f);
		break;
	case 8:
		m_text->setOrigin(charWidth + m_text->getGlobalBounds().width * 0.5f, charHeight + m_text->getGlobalBounds().height * 0.0f);
		break;
	case 9:
		m_text->setOrigin(charWidth + m_text->getGlobalBounds().width * 1.0f, charHeight + m_text->getGlobalBounds().height * 0.0f);
		break;
	default:
		m_text->setOrigin(charWidth,charHeight);
#if _DEBUG
		std::cout<<"Sprite origin out of range, origin set to top left"<<std::endl;
#endif
		break;
	}
	
}
void text::setScale(float ScaleX, float ScaleY)
{
	m_text->setScale(ScaleX,ScaleY);
}
void text::setScale(float Scale)
{
	setScale(Scale,Scale);
}
void text::setScale(vector Scale)
{
	setScale(Scale.x,Scale.y);
}
void text::setLayer(int Layer)
{
	if (Layer >= 0 && Layer <= 1000)
		m_layer = Layer;
	else if (Layer < 0)
		m_layer = 0;
	else if (Layer > 1000)
		m_layer = 1000;
}
vector text::getPosition()
{
	return m_text->getPosition();
}
vector text::getOrigin()
{
	return m_text->getOrigin();
}
vector text::getScale()
{
	return m_text->getScale();
}
vector text::getSize()
{
	return vector(m_text->getLocalBounds().width, m_text->getLocalBounds().height);
}
vector text::getTransformedSize()
{
	return vector(m_text->getGlobalBounds().width, m_text->getGlobalBounds().height);
}
rectangle text::getGlobalBounds()
{
	return rectangle(m_text->getGlobalBounds());
}

// Viewport
viewport::viewport(sf::RenderWindow* window)
	: m_window(window)
{}
viewport::~viewport()
{}
void viewport::draw(al::sprite* Sprite)
{
	m_objects[Sprite->m_layer].push_back(Sprite->m_sprite);
}
void viewport::draw(al::text* Text)
{
	m_objects[Text->m_layer].push_back(Text->m_text);
}
void viewport::renderSprites()
{
 	for (int i = 0; i < LAYER_COUNT + 1; ++i)
	{
		for(unsigned int j = 0; j < m_objects[i].size(); ++j)
		{
			m_window->draw(*m_objects[i][j]);
		}
		m_objects[i].clear();
	}
}
void viewport::close()
{
	m_window->close();
}