#include "particleEngine.h"

using namespace al;

particleEngine::particleEngine(al::font* Font)
{
	m_splashTexture = new texture("splashAnimation.png");
	m_featherTexture = new texture("featherEffect.png");
	m_plusPoint = new texture("plusPoint.png");
	m_minusPoint = new texture("minusPoint.png");
	m_font = Font;
}
particleEngine::~particleEngine()
{
	delete m_splashTexture;
	for (int i = 0; i < m_particles.size(); ++i)
	{
		delete m_particles[i];
	}
}

void particleEngine::update(float DeltaTime)
{
 	for (int i = 0; i < m_particles.size(); ++i)
	{
		if (m_particles[i]->update(DeltaTime))
		{
			delete m_particles[i];
			m_particles.erase(m_particles.begin() + i);
		}
	}
}

void particleEngine::draw(al::viewport* Viewport)
{
	for (int i = 0; i < m_particles.size(); ++i)
	{
		m_particles[i]->draw(Viewport);
	}
}
void particleEngine::reset()
{
	for (int i = 0; i < m_particles.size(); ++i)
	{
		delete m_particles[i];
	}
	m_particles.clear();
}

void particleEngine::addSplash(al::vector Position, al::vector Direction)
{
	m_particles.push_back(new splashParticle(Position,Direction,vector(1,1),m_splashTexture));
}
void particleEngine::addFeather(al::vector Position, bool Enemy)
{
	vector direction = vector((rand()%200 / 100.0f)-1,0);
	direction.rotate((rand()%3600)/10.0f);
	addFeather(Position,direction, 0.0f, Enemy);
}
void particleEngine::addFeather(al::vector Position, al::vector Direction, float SpreadDegrees, bool Enemy)
{
	if (SpreadDegrees != 0)
		Direction.rotate((1-((rand()%2000)/1000.0f))*SpreadDegrees);
	m_particles.push_back(new feather(Position,Direction,vector(0.6f,0.6f),m_featherTexture,Enemy));
}

void particleEngine::addScore(al::vector Position, float Score)
{
	Score = float(int(floor(Score)));
	vector direction = vector((rand()%200 / 100.0f)-1,0);
	direction.rotate((rand()%3600)/10.0f);
	if (Score > 0)
		m_particles.push_back(new scoreParticle(Position,direction,m_plusPoint,m_font,Score));
	else if (Score < 0)
		m_particles.push_back(new scoreParticle(Position,direction,m_minusPoint,m_font,Score));
}