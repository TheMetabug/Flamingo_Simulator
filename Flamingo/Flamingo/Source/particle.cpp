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
	: particle(Position,1000*Direction,Scale,Texture,5.0f)
{
	if (Enemy)
		setColor(140,182,123);
	else
		setColor();
	m_scale = vector(
		0.8f + (rand()%400)/1000.0f,
		0.8f + (rand()%400)/1000.0f
		);
	if (rand()%100 < 50)
	{
		m_scale.y = -m_scale.y;
	}
	m_sprite.setScale(m_scale);
	m_timer = -0.08f;
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
	}
	else
	{
		m_life -= DeltaTime;
		m_sprite.setColor(m_r, m_g, m_b, (m_life/m_startLife) * m_a);
		if (m_life < 0)
			return true;
	}
	return false;
}