#include "animation.h"



animation::animation(sf::Sprite *Sprite, int Frames, int FramesizeX, int FramesizeY, bool Flip, float Fps, int FirstFrame)
{
	m_sprite = Sprite;
	m_frames = Frames;
	m_framesizeX = FramesizeX;
	m_framesizeY = FramesizeY;
	m_fps = Fps;
	m_currentFrame = m_firstFrame = FirstFrame;
	m_flip = Flip;
	m_timer = 0.0f;
	setVisibleFrame();
}

animation::~animation()
{
	std::cout<<"deleted animation"<<std::endl;
}

void animation::update(float deltaTime)
{
	m_timer += deltaTime;
	//std::cout<<"timer "<< deltaTime<<std::endl;


	if (m_timer > 1.0 / m_fps) //frame changes
	{
		m_currentFrame++;
		if (m_currentFrame >= m_firstFrame + m_frames)
		{
			m_currentFrame = m_firstFrame;
		}
		m_timer -= 1.0 / m_fps;
		//counter++;
		
		setVisibleFrame();
	}
}

void animation::ChangeAnimation(int FirstFrameofLoop, int FramesinLoop, int AnimationStartPoint, float Fps)
{
	m_firstFrame = FirstFrameofLoop;
	m_frames = FramesinLoop;
	m_currentFrame = AnimationStartPoint;
	m_fps = Fps;
	m_timer = 0;
}

void animation::setVisibleFrame()
{
	int currentFrameX = m_currentFrame % (m_sprite->getTexture()->getSize().x / m_framesizeX) * m_framesizeX;
	int currentFrameY = (int)(floor((double)m_currentFrame / ((double)m_sprite->getTexture()->getSize().x / (double)m_framesizeX))) * m_framesizeY;
	m_sprite->setTextureRect(sf::Rect<int>(currentFrameX, currentFrameY, m_framesizeX, m_framesizeY));
}