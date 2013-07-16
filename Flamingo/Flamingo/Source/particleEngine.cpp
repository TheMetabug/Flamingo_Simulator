#include "particleEngine.h"

using namespace al;

particleEngine::particleEngine()
{
	m_splashTexture = new texture("splashAnimation.png");
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