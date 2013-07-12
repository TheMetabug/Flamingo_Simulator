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
	void setVolume(float Volume);
	std::string m_musicName;
	

private:
	float m_volume;
	float m_volumeMultiplier;
	bool m_mute;

	sf::Music* m_music;

	friend class soundLibrary;
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
	void setVolume(float Volume);
	std::string m_soundName;

private:
	float m_volume;
	float m_volumeMultiplier;
	bool m_mute;

	sf::SoundBuffer *m_buffer;
	sf::Sound *m_sound;

	friend class soundLibrary;
};

class soundLibrary
{
public:
	soundLibrary();
	~soundLibrary();

	void mute(bool Mute);
	void setMusicVolume(float volume);
	void setSoundsVolume(float volume);

	sound* findSound(std::string soundName);
	music* findMusic(std::string musicName);

	std::vector<sound*> m_sounds;
	std::vector<music*> m_musics;
private:
	bool m_mute;
	float m_musicVolume;
	float m_soundVolume;
};

#endif