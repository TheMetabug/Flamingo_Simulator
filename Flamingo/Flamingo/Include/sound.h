#ifndef SOUND_H
#define SOUND_H

#include <SFML\Graphics.hpp>
#include <iostream>
#include <SFML\Audio.hpp>

class sound
{
public:
	//sound(){}
	sound();
	~sound();

private:
	sf::RenderWindow *window;
	sf::SoundBuffer *m_buffer;
	sf::Sound *m_sound;

};

#endif