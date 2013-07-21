#include "particle.h"

using namespace al;

particle::particle(vector Position, vector Direction, vector Scale, texture* Texture, float Life)
	: m_position(Position),
	  m_direction(Direction),
	  m_scale(Scale),
	  m_sprite(Texture),
	  m_life(Life),
	  m_startLife(Life),
	  m_dead(false)
{
	m_sprite.setPosition(Position);
	m_sprite.setScale(Scale);
	m_sprite.setLayer(300);
	m_sprite.setOrigin(m_sprite.getTextureSize()/2);
}
particle::~particle()
{}
bool particle::update(float DeltaTime)
{
	m_position += m_direction * DeltaTime;
	m_sprite.setPosition(m_position);
	m_life -= DeltaTime;
	if (m_life < 0)
		return true;
	return false;
}
void particle::draw(viewport* Viewport)
{
	Viewport->draw(&m_sprite);
}

splashParticle::splashParticle(vector Position, vector Direction, vector Scale, texture* Texture)
	: particle(Position,vector(Direction.x/5.0f,-Direction.y/5.0f),Scale,Texture,1.0f)
{
	m_startY = Position.y;
	//m_direction = vector(Direction.x/5.0f,-Direction.y/5.0f);
	m_animation = new animation(&m_sprite,7,176,114, 6 / m_life,0,false);
	m_sprite.setOrigin(m_sprite.getSize()/2);
	m_sprite.setColor(255,255,255,180);
	if (Direction.x > 0)
	{
		m_scale.x = -m_scale.x;
		m_sprite.setScale(m_scale);
	}
}
bool splashParticle::update(float DeltaTime)
{
	m_animation->update(DeltaTime);
	particle::update(DeltaTime);
	//m_life-= DeltaTime;
	m_sprite.setPosition(vector(m_position.x, m_startY + 50 * sin(PI*(-m_life/m_startLife))));
	m_sprite.setLayer(((m_position.y - WATER_TOP) / (WATER_BOTTOM - WATER_TOP)) * 275 + 80);
	if (m_animation->getCurrentFrame() > 5)
		return true;
	return false;
}

feather::feather(vector Position, vector Direction, vector Scale, texture* Texture, bool Enemy)
	: particle(Position,1000*Direction,Scale,Texture,5.0f + (0-(rand()%300)/100.0f))
{
	if (Enemy)
		setColor(140,182,123);
	else
		setColor();
	m_scale = vector(
		Scale.x + Scale.x * (0.2f - (rand()%400)/1000.0f),
		Scale.y + Scale.y * (0.2f - (rand()%400)/1000.0f)
		);
	if (rand()%100 < 50)
	{
		m_scale.y = -m_scale.y;
	}
	
	//m_sprite.setOrigin(vector(m_sprite.getTransformedSize().x/2,-m_sprite.getTransformedSize().y/2));

	m_sprite.setScale(m_scale);
	m_sprite.setLayer(280);

	m_timer = -0.08f;
	m_rotate = (rand()%1000)/100;
}
void feather::setColor(int R,int G,int B,int A)
{
	m_r = R - 15 + rand()%15;
	m_g = G - 15 + rand()%15;
	m_b = B - 15 + rand()%15;
	m_a = A - 100 + rand()%50;
	m_sprite.setColor(m_r, m_g, m_b, m_a);
}
bool feather::update(float DeltaTime)
{
	m_timer += DeltaTime;
	if (m_timer < 0)
	{
		m_direction *= (1-DeltaTime)*(1-DeltaTime);
		m_position += m_direction * DeltaTime;
		m_sprite.setPosition(m_position);
		particle::update(DeltaTime);
		m_rotate += DeltaTime*3600.0f;
		m_sprite.setRotation(m_rotate);
	}
	else
	{
		m_life -= DeltaTime;
		if (m_life < 0)
			return true;
		m_sprite.setColor(m_r, m_g, m_b, (m_life/m_startLife) * m_a);
		m_rotate += DeltaTime * 3.0f;
		m_position.y += DeltaTime * 5.0f;
		m_sprite.setPosition(m_position);
		if (m_scale.y > 0)
		{
			m_sprite.setRotation( sin(m_rotate) * 20);
		}
		else
		{
			m_sprite.setRotation( 180 + sin(m_rotate) * 20);
		}
	}
	return false;
}

scoreParticle::scoreParticle(al::vector Position, al::vector Direction, al::texture* Texture, al::font* Font, float Score)
	: particle(Position,Direction,vector(1,1),Texture,3.0f)
{
	m_sprite.setTexture(Texture);
	m_sprite.setOriginPoint(5);
	m_sprite.setLayer(300);
	m_text.setFont(Font);
	m_text.setCharacterSize(60);
	m_text.setString(std::to_string(long double(Score)));
	m_text.setOriginPoint(5);
	m_text.setLayer(300);

}
bool scoreParticle::update(float DeltaTime)
{
	//m_direction.y += 20 * DeltaTime;
	//m_position += 50 * m_direction * DeltaTime;
	m_life -= DeltaTime;
	m_scale = vector(1-(m_life/m_startLife),1-(m_life/m_startLife));

	m_sprite.setColor(255, 255, 255, (m_life/m_startLife) * 255);
	m_sprite.setPosition(m_position);
	m_sprite.setScale(m_scale);

	m_text.setColor(255, 255, 255, (m_life/m_startLife) * 255);
	m_text.setPosition(m_position);
	m_text.setScale(m_scale);

	//stayOnScreen();

	if (m_life < 0)
		return true;
	return false;
}
void scoreParticle::draw(viewport* Viewport)
{
	Viewport->draw(&m_sprite);
	Viewport->draw(&m_text);
}
void scoreParticle::stayOnScreen()
{
	float left = 0;
	float right = WINDOW_WIDTH;
	float top = 0;
	float bottom = WINDOW_HEIGHT;
	if (m_position.x < left)
	{
		m_direction.x = -m_direction.x;
		m_position.x = left;
	}
	else 
		if (m_position.x > right)
	{
		m_direction.x = -m_direction.x;
		m_position.x = right;
	}
	if (m_position.y < top)
	{
		m_direction.y = -m_direction.y;
		m_position.y = top;
	}
	else 
		if (m_position.y > bottom)
	{
		m_direction.y = -m_direction.y;
		m_position.y = bottom;
	}
}