#ifndef PARTICLEENGINE_H
#define PARTICLEENGINE_H

#include <iostream>
#include "program.h"
#include "particle.h"

class particleEngine
{
public:
	particleEngine(al::font* Font);
	~particleEngine();
	void update(float DeltaTime);
	void draw(al::viewport* Viewport);
	void reset();

	void addSplash(al::vector Position, al::vector Direction);
	void addFeather(al::vector Position, bool Enemy = false);
	void addFeather(al::vector Position, al::vector Direction, float SpreadDegrees, bool Enemy = false);
	void addScore(al::vector Position, float Score);
private:
	al::texture* m_splashTexture;
	al::texture* m_featherTexture;
	al::texture* m_plusPoint;
	al::texture* m_minusPoint;
	al::font* m_font;
	std::vector<particle*> m_particles;
};

#endif