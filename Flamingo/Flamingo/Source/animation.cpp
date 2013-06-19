#include "animation.h"



Animation::Animation(sf::Texture *Texture, int Frames, int FramesizeX, int FramesizeY, bool Flip, float Fps, int FirstFrame)
{
	frames = Frames;
	framesizeX = FramesizeX;
	framesizeY = FramesizeY;
	fps = Fps;
	firstFrame = FirstFrame;
	flip = Flip;
	timer = 0.0f;
}

