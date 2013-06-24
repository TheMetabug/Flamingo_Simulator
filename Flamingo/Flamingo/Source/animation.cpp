#include "animation.h"



animation::animation(sf::Sprite *Sprite, int Frames, int FramesizeX, int FramesizeY, bool Flip, float Fps, int FirstFrame)
{
	sprite = Sprite;
	frames = Frames;
	framesizeX = FramesizeX;
	framesizeY = FramesizeY;
	fps = Fps;
	currentFrame = firstFrame = FirstFrame;
	flip = Flip;
	timer = 0.0f;
	setVisibleFrame();
}

animation::~animation()
{
	std::cout<<"deleted animation"<<std::endl;
}

void animation::update(float deltaTime)
{
	timer += deltaTime;
	//std::cout<<"timer "<< deltaTime<<std::endl;


	if (timer > 1.0 / fps) //frame changes
	{
		currentFrame++;
		if (currentFrame >= firstFrame + frames)
		{
			currentFrame = firstFrame;
		}
		timer -= 1.0 / fps;
		//counter++;
		
		setVisibleFrame();
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

void animation::setVisibleFrame()
{
	int currentFrameX = currentFrame % (sprite->getTexture()->getSize().x / framesizeX) * framesizeX;
	int currentFrameY = (int)(floor((double)currentFrame / ((double)sprite->getTexture()->getSize().x / (double)framesizeX))) * framesizeY;
	sprite->setTextureRect(sf::Rect<int>(currentFrameX, currentFrameY, framesizeX, framesizeY));
}