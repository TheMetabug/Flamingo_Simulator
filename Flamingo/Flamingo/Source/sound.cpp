#include <sound.h>

sound::sound()
{
	m_buffer = new sf::SoundBuffer();
	//sf::SoundBuffer *m_buffer;
	m_buffer->loadFromFile("Assets/whatislove.wav");

	m_sound = new sf::Sound();
	//sf::Sound *m_sound;
	m_sound->setBuffer(*m_buffer);
	m_sound->play();
	m_sound->setLoop(true);

}

sound::~sound()
{
	delete m_buffer;
	delete m_sound;
}
