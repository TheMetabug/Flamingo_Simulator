#ifndef ANIMATION_H
#define ANIMATION_H

#include <SFML/Graphics.hpp>
#include <iostream>


class Animation
{
public:
	Animation(sf::Texture *Texture, int Frames, int FramesizeX, int FramesizeY, bool Flip = false, float Fps= (5.0f), int FirstFrame = 0);
private:
	sf::Texture *texture;
	sf::Sprite sprite;

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