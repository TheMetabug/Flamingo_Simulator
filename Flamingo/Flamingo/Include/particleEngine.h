#ifndef PARTICLEENGINE_H
#define PARTICLEENGINE_H

#include <iostream>
#include "program.h"
#include "particle.h"

class particleEngine
{
public:
	particleEngine();
	~particleEngine();
	void update(float DeltaTime);
	void draw(al::viewport* Viewport);
	void reset();

	void addSplash(al::vector Position, al::vector Direction);
	void addFeather(al::vector Position);
	void addFeather(al::vector Position, al::vector Direction, float SpreadDegrees);
private:
	al::texture* m_splashTexture;
	al::texture* m_featherTexture;
	std::vector<particle*> m_particles;
};

#endif