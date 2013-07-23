#include "animation.h"



animation::animation(al::sprite *Sprite, int Frames, int FramesizeX, int FramesizeY, float Fps, int FirstFrame, bool Loop)
{
	m_loop = Loop;
	m_sprite = Sprite;
	m_frames = Frames;
	m_framesizeX = FramesizeX;
	m_framesizeY = FramesizeY;
	m_fps = Fps;
	m_currentFrame = m_firstFrame = FirstFrame;
	m_timer = 0.0f;
	setVisibleFrame();
#if _DEBUG
	if (fmod(Sprite->getTextureSize().x,float(FramesizeX)) != 0)
		std::cout<<"Check FramesizeX!!!!!!"<<std::endl;
	if (fmod(Sprite->getTextureSize().y,float(FramesizeY)) != 0)
		std::cout<<"Check FramesizeY!!!!!!"<<std::endl;
#endif
}

animation::~animation()
{
#if _DEBUG
	std::cout<<"deleted animation"<<std::endl;
#endif
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
			if (m_loop)
				m_currentFrame = m_firstFrame;
			else
				m_currentFrame--;
		}
		m_timer -= 1.0f / m_fps;
		//counter++;
		
		setVisibleFrame();
	}
}

void animation::ChangeAnimation(int FirstFrameofLoop, int FramesinLoop)
{
	m_firstFrame = FirstFrameofLoop;
	m_frames = FramesinLoop;
	m_currentFrame = FirstFrameofLoop;
	m_timer = 0;
	setVisibleFrame();
}

void animation::ChangeAnimation(int FirstFrameofLoop, int FramesinLoop, int AnimationStartPoint, float Fps)
{
	m_firstFrame = FirstFrameofLoop;
	m_frames = FramesinLoop;
	m_currentFrame = AnimationStartPoint;
	m_fps = Fps;
	m_timer = 0;
	setVisibleFrame();
}

void animation::setVisibleFrame()
{
	
	int currentFrameX = m_currentFrame % ((int)((m_sprite->getTextureSize().x / m_framesizeX)+0.5f)) * m_framesizeX;
	int currentFrameY = (int)(floor((double)m_currentFrame / ((double)m_sprite->getTextureSize().x / (double)m_framesizeX))) * m_framesizeY;
	al::rectangle frame = al::rectangle((float)currentFrameX, (float)currentFrameY, (float)m_framesizeX, (float)m_framesizeY);
	m_sprite->setTextureRectangle(frame);
}

int animation::getCurrentFrame()
{
	return m_currentFrame;
}