#include "animation.h"



animation::animation(al::sprite *Sprite, int Frames, int FramesizeX, int FramesizeY, bool Flip, float Fps, int FirstFrame)
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
	if (fmod(Sprite->getTextureSize().x,FramesizeX) != 0)
		std::cout<<"Check FramesizeX!!!!!!"<<std::endl;
	if (fmod(Sprite->getTextureSize().y,FramesizeY) != 0)
		std::cout<<"Check FramesizeY!!!!!!"<<std::endl;
}

animation::~animation()
{
	std::cout<<"deleted animation"<<std::endl;
}

void animation::update(float deltaTime)
{
	m_timer += deltaTime;
	//std::cout<<"timer "<< deltaTime<<std::endl;


	while (m_timer > 1.0 / m_fps) //frame changes
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
	//m_timer = 0;
}

void animation::setVisibleFrame()
{
	
	int currentFrameX = m_currentFrame % ((int)((m_sprite->getTextureSize().x / m_framesizeX)+0.5f)) * m_framesizeX;
	int currentFrameY = (int)(floor((double)m_currentFrame / ((double)m_sprite->getTextureSize().x / (double)m_framesizeX))) * m_framesizeY;
	al::rectangle frame = al::rectangle(currentFrameX, currentFrameY, m_framesizeX, m_framesizeY);
	m_sprite->setTextureRectangle(frame);
}

int animation::getCurrentFrame()
{
	return m_currentFrame;
}