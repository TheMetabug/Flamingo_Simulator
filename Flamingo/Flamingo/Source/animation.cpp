#include "animation.h"



animation::animation(sf::Sprite *Sprite, int Frames, int FramesizeX, int FramesizeY, bool Flip, float Fps, int FirstFrame)
{
	sprite = Sprite;
	frames = Frames;
	framesizeX = FramesizeX;
	framesizeY = FramesizeY;
	fps = Fps;
	firstFrame = FirstFrame;
	flip = Flip;
	timer = 0.0f;
}

void animation::update(float deltaTime)
{
	timer += deltaTime;

    if (timer > 1000 / fps) //frame changes
	{
		currentFrame++;
		if (currentFrame >= firstFrame + frames)
		{
			currentFrame = firstFrame;
		}
		timer -= 1000 / fps;
		counter++;
		
		int currentFrameX = currentFrame % (sprite->getTexture()->getSize().x / framesizeX) * framesizeX;
		int currentFrameY = (int)(floor((double)currentFrame / ((double)sprite->getTexture()->getSize().x / (double)framesizeX))) * framesizeY;
		sprite->setTextureRect(sf::Rect<int>(currentFrameX, currentFrameY, framesizeX, framesizeY));
	}
}

void animation::ChangeAnimation(int FirstFrameofLoop, int FramesinLoop, int AnimationStartPoint, float Fps)
{
	firstFrame = FirstFrameofLoop;
	frames = FramesinLoop;
	currentFrame = AnimationStartPoint;
	fps = Fps;
	timer = 0;
}