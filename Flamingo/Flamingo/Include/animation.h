#ifndef ANIMATION_H
#define ANIMATION_H

#include <SFML/Graphics.hpp>
#include <iostream>
#include <math.h>
#include "program.h"


class animation
{
public:
	animation(al::sprite *Sprite, int Frames, int FramesizeX, int FramesizeY, float Fps= (5.0f), int FirstFrame = 0);
	~animation();
	void update(float deltaTime);
	void ChangeAnimation(int FirstFrameofLoop, int FramesinLoop);
	void ChangeAnimation(int FirstFrameofLoop, int FramesinLoop, int AnimationStartPoint, float Fps = (5.0f));
	int getCurrentFrame();
private:
	void setVisibleFrame();
	
	al::sprite* m_sprite;

	float m_timer;
	int m_currentFrame;
	float m_fps;
	int m_firstFrame;
	int m_frames;
	int m_framesizeX;
	int m_framesizeY;
	bool m_flip;
	bool m_transition;
	//int counter;
};

#endif