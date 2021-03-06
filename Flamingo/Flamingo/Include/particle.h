#ifndef PARTICLE_H
#define PARTICLE_H

#include "program.h"
#include "animation.h"
#include <iostream>

class particle
{
public:
	particle(al::vector Position, al::vector Direction, al::vector Scale, al::texture* Texture, float Life);
	virtual ~particle();
	virtual bool update(float DeltaTime);
	virtual void draw(al::viewport* Viewport);

protected:
	al::vector m_position;
	al::vector m_direction;
	al::vector m_scale;
	al::sprite m_sprite;
	float m_startLife;
	float m_life;
	bool m_dead;
};

class splashParticle : public particle
{
public:
	splashParticle(al::vector Position, al::vector Direction, al::vector Scale, al::texture* Texture);
	~splashParticle(){}
	bool update(float DeltaTime);

private:
	animation* m_animation;
	float m_startY;
};

class feather : public particle
{
public:
	feather(al::vector Position, al::vector Direction, al::vector Scale, al::texture* Texture, bool Enemy);
	~feather(){}
	bool update(float DeltaTime);
private:
	void setColor(int R = 255,int G = 255,int B = 255,int A = 255);

	float m_timer, m_rotate, m_r, m_g, m_b, m_a;
};

class scoreParticle : public particle
{
public:
	scoreParticle(al::vector Position, al::vector Direction, al::texture* Texture, al::font* Font, float Score);
	~scoreParticle(){}
	bool update(float DeltaTime);
	void draw(al::viewport* Viewport);
private:
	void stayOnScreen();
	al::text m_text;
	float m_r, m_g, m_b, m_a;
};

#endif