#include <sound.h>

///////// MUSIC /////////
music::music()
{
	m_music = new sf::Music();
	load("Assets/whatislove.wav");	
}

music::~music()
{
	delete m_music;
}

void music::load(std::string filename)
{
	m_music->openFromFile(filename);
}

void music::play() 
{
	m_music->play();
}

void music::stop() 
{
	m_music->stop();
}

void music::pause()
{
	m_music->pause();
}

///////// SOUND //////////

sound::sound()
{
	m_buffer = new sf::SoundBuffer();
	load("Assets/boing.wav");
	m_sound = new sf::Sound();
	m_sound->setBuffer(*m_buffer);
	
	//m_sound->setLoop(true);

}
sound::~sound()
{
	delete m_buffer;
	delete m_sound;
}

void sound::load(std::string filename)
{
	m_buffer->loadFromFile(filename);
}
void sound::play(int soundID)
{
	switch(soundID)
	{
	case 0:
		m_sound->play();
		break;
	case 1:

		break;
	}
	
}
void sound::stop(int soundID)
{
	switch(soundID)
	{
	case 0:
		m_sound->stop();
		break;
	case 1:

		break;
	}

}
void sound::pause(int soundID)
{
	switch(soundID)
	{
	case 0:
		m_sound->play();
		break;
	case 1:

		break;
	}
}




