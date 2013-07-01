#ifndef SOUND_H
#define SOUND_H

#include <SFML\Graphics.hpp>
#include <iostream>
#include <SFML\Audio.hpp>

class music
{
public:
	music();
	~music();

	void load(std::string filename);
	void play();
	void stop();
	void pause();
	


private:
	sf::Music* m_music;
};

class sound
{
public:
	sound();
	~sound();

	void load(std::string filename);
	void play(int soundID);
	void stop(int soundID);
	void pause(int soundID);
	sf::Sound *m_sound;

private:
	sf::SoundBuffer *m_buffer;
	

};

#endif