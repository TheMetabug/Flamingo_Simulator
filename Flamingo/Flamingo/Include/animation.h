#ifndef ANIMATION_H
#define ANIMATION_H

#include <SFML/Graphics.hpp>
#include <iostream>
#include <math.h>


class animation
{
public:
	animation(sf::Sprite *Sprite, int Frames, int FramesizeX, int FramesizeY, bool Flip = false, float Fps= (5.0f), int FirstFrame = 0);
	~animation();
	void update(float deltaTime);
	void ChangeAnimation(int FirstFrameofLoop, int FramesinLoop, int AnimationStartPoint, float Fps);
private:
	void setVisibleFrame();
	
	sf::Sprite *sprite;

	float timer;
	int currentFrame;
	float fps;
	int firstFrame;
	int frames;
	int framesizeX;
	int framesizeY;
	bool flip;
	bool transition;
	int counter;
};

#endif