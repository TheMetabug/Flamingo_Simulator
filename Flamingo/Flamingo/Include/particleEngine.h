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
private:
	al::texture* m_splashTexture;
	std::vector<particle*> m_particles;
};

#endif