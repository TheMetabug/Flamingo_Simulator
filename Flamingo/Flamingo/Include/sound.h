#ifndef SOUND_H
#define SOUND_H

#include <SFML\Graphics.hpp>
#include <iostream>
#include <SFML\Audio.hpp>

class music
{
public:
	music();
	music(std::string Filename);
	~music();

	void load(std::string filename);
	void play();
	void stop();
	void pause();
	std::string m_musicName;
	

private:
	sf::Music* m_music;
};

class sound
{
public:
	sound();
	sound(std::string Filename);
	~sound();

	void load(std::string filename);
	void play();
	void stop();
	void pause();
	std::string m_soundName;
private:
	sf::SoundBuffer *m_buffer;
	sf::Sound *m_sound;
};

class soundLibrary
{
public:
	soundLibrary();
	~soundLibrary();
	sound* findSound(std::string soundName);
	music* findMusic(std::string musicName);

	std::vector<sound*> m_sounds;
	std::vector<music*> m_musics;
};

#endif