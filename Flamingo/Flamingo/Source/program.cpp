#include "program.h"
#define PI 3.14159265358979323846264


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

vector::vector(sf::Vector2i sfVector)
{
	x = sfVector.x;
	y = sfVector.y;
}

vector::vector(sf::Vector2u sfVector)
{
	x = sfVector.x;
	y = sfVector.y;
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
		if (y < 0)
			return 90;
		return 270;
	}
	else
	{
		float angle = atan(y/x)*(180.0f/PI);
		if (x > 0)
			angle += 180;
		else if (angle < 0)
			angle += 360;
		return angle;
	}
}

void vector::rotate(float Degrees)
{
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
	std::cout<<"deleting...  ";
	delete m_sprite;
	std::cout<<"deleted sprite"<<std::endl;
}

void sprite::setColor(sf::Uint8 R, sf::Uint8 G, sf::Uint8 B, sf::Uint8 A)
{
	m_sprite->setColor(sf::Color(R,G,B,A));
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

#pragma region Font

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

#pragma endregion

#pragma region Text

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
	delete m_text;
}

void text::setFont(al::font* Font)
{
	m_text->setFont(*(Font->m_font));
}

void text::setString(std::string string)
{
	m_text->setString(string);
}

void text::setColor(unsigned int Red, unsigned int Green, unsigned int Blue, unsigned int Alpha)
{
	sf::Color color(Red, Green, Blue, Alpha);
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

	switch (Point)
	{
	case 1:
		m_text->setOrigin(m_text->getLocalBounds().width * 0.0f, m_text->getLocalBounds().height * 1.0f);
		break;
	case 2:
		m_text->setOrigin(m_text->getLocalBounds().width * 0.5f, m_text->getLocalBounds().height * 1.0f);
		break;
	case 3:
		m_text->setOrigin(m_text->getLocalBounds().width * 1.0f, m_text->getLocalBounds().height * 1.0f);
		break;
	case 4:
		m_text->setOrigin(m_text->getLocalBounds().width * 0.0f, m_text->getLocalBounds().height * 0.5f);
		break;
	case 5:
		m_text->setOrigin(m_text->getLocalBounds().width * 0.5f, m_text->getLocalBounds().height * 0.5f);
		break;
	case 6:
		m_text->setOrigin(m_text->getLocalBounds().width * 1.0f, m_text->getLocalBounds().height * 0.5f);
		break;
	case 7:
		m_text->setOrigin(m_text->getLocalBounds().width * 0.0f, m_text->getLocalBounds().height * 0.0f);
		break;
	case 8:
		m_text->setOrigin(m_text->getLocalBounds().width * 0.5f, m_text->getLocalBounds().height * 0.0f);
		break;
	case 9:
		m_text->setOrigin(m_text->getLocalBounds().width * 1.0f, m_text->getLocalBounds().height * 0.0f);
		break;
	default:
		m_text->setOrigin(0,0);
		std::cout<<"Sprite origin out of range, origin set to top left"<<std::endl;
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

#pragma endregion

#pragma region Viewport

viewport::viewport(sf::RenderWindow* window)
	: m_window(window)
{}

viewport::~viewport()
{}

void viewport::draw(al::sprite* Sprite)
{
	m_objects[Sprite->m_layer].push_back(Sprite->m_sprite);
	//m_spriteLayer[Sprite->m_layer].push_back(Sprite);
}

void viewport::draw(al::text* Text)
{
	m_objects[Text->m_layer].push_back(Text->m_text);
	//m_textLayer[Text->m_layer].push_back(Text);
}

void viewport::renderSprites()
{
 	for (int i = 0; i < 301; ++i)
	{
		for(int j = 0; j < m_objects[i].size(); ++j)
		{
			m_window->draw(*m_objects[i][j]);
		}
		m_objects[i].clear();

		//for(int j = 0; j < m_spriteLayer[i].size(); ++j)
		//{
		//	m_window->draw(*m_spriteLayer[i][j]->m_sprite);
		//}
		//m_spriteLayer[i].clear();
		//for(int j = 0; j < m_textLayer[i].size(); ++j)
		//{
		//	m_window->draw(*m_textLayer[i][j]->m_text);
		//}
		//m_textLayer[i].clear();
	}
}

#pragma endregion

#pragma endregion