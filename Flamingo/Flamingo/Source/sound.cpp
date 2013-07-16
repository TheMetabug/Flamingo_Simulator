#include <sound.h>

///////// MUSIC /////////
music::music()
	:	m_volumeMultiplier(1.0f),
		m_mute(false)
{
	m_music = new sf::Music();
	setVolume(30);
}
music::music(std::string Filename)
	:	m_volumeMultiplier(1.0f),
		m_mute(false)
{
	m_music = new sf::Music();
	m_music->setLoop(true);
	setVolume(30);
	
	load(Filename);	
}

music::~music()
{
	delete m_music;
}

void music::load(std::string filename)
{
	m_music->openFromFile("Assets/Music/" + filename + ".wav");
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

void music::setVolume(float Volume)
{
	if (!m_mute)
		m_music->setVolume(Volume * m_volumeMultiplier);
	else
		m_music->setVolume(0);

	m_volume = Volume;
}

///////// SOUND //////////

sound::sound()
	:	m_volumeMultiplier(1.0f),
		m_mute(false)
{
	m_buffer = new sf::SoundBuffer();
	m_sound = new sf::Sound();
	m_sound->setBuffer(*m_buffer);
	setVolume(30);
}
sound::sound(std::string Filename)
	:	m_volumeMultiplier(1.0f),
		m_mute(false)
{
	m_buffer = new sf::SoundBuffer();
	load(Filename);
	m_sound = new sf::Sound();
	m_sound->setBuffer(*m_buffer);
	setVolume(100);
}
sound::~sound()
{
	delete m_buffer;
	delete m_sound;
}

void sound::load(std::string filename)
{
	m_buffer->loadFromFile("Assets/Sound effects/" + filename + ".wav");
	m_soundName = filename;
}
void sound::play()
{
	m_sound->play();
}
void sound::stop()
{
	m_sound->stop();
}
void sound::pause()
{
	m_sound->play();
}
void sound::setVolume(float Volume)
{
	if (!m_mute)
		m_sound->setVolume(Volume * m_volumeMultiplier);
	else
		m_sound->setVolume(0);

	m_volume = Volume;
}



soundLibrary::soundLibrary()
	:	m_mute(false),
		m_musicVolume(50),
		m_soundVolume(50)
{
#pragma region Musics

	m_musics.push_back(new music("versio3"));
	m_musics.push_back(new music("version2"));

#pragma endregion here we keep the musics, dont mix us plz
//////////////////////////////////////////////////////////DONT MIX THESE//////////////////
#pragma region Sounds

	m_sounds.push_back(new sound("bojoing"));
	m_sounds.push_back(new sound("sound1"));
	m_sounds.push_back(new sound("kuminauha"));
	m_sounds.push_back(new sound("kuminauha2_1"));
	m_sounds.push_back(new sound("button"));
	m_sounds.push_back(new sound("piip piip"));
	m_sounds.push_back(new sound("piip piip 2"));
	m_sounds.push_back(new sound("failure"));
	m_sounds.push_back(new sound("fail2"));
	m_sounds.push_back(new sound("mäisk"));
	m_sounds.push_back(new sound("mäisk2"));
	m_sounds.push_back(new sound("Energy"));
	m_sounds.push_back(new sound("iloinen piip piip"));
	m_sounds.push_back(new sound("kuoriutuminen"));
	m_sounds.push_back(new sound("kuoriutuminen kaksi"));
	m_sounds.push_back(new sound("vihainen piipiip"));
	m_sounds.push_back(new sound("yksi piip"));
	m_sounds.push_back(new sound("vihollislintu"));
	m_sounds.push_back(new sound("pop"));
	m_sounds.push_back(new sound("pop2"));
	m_sounds.push_back(new sound("pop3"));
	m_sounds.push_back(new sound("piipyksi2"));
	m_sounds.push_back(new sound("flamingo1"));
	m_sounds.push_back(new sound("flamingo2"));
	m_sounds.push_back(new sound("flamingo3"));
	m_sounds.push_back(new sound("flamingo4"));
	m_sounds.push_back(new sound("flamingo5"));
	m_sounds.push_back(new sound("kuminauha2_1"));
	m_sounds.push_back(new sound("boing"));







#pragma endregion here we keep the sounds, dont mix us plz
}
soundLibrary::~soundLibrary()
{
	for (int i = 0; i < m_sounds.size(); ++i)
		delete m_sounds[i];
	for (int i = 0; i < m_musics.size(); ++i)
		delete m_musics[i];
}

sound* soundLibrary::findSound(std::string soundName)
{
	for (int i = 0; i < m_sounds.size(); ++i)
	{
		if (m_sounds[i]->m_soundName == soundName)
			return m_sounds[i];
	}
	return NULL;
}
music* soundLibrary::findMusic(std::string musicName)
{
	for (int i = 0; i < m_musics.size(); ++i)
	{
		if (m_musics[i]->m_musicName == musicName)
			return m_musics[i];
	}
	return NULL;
}

void soundLibrary::mute(bool Mute)
{
	if (Mute)
	{
		for (int i = 0; i < m_musics.size(); ++i)
		{
			m_musics[i]->m_mute = true;
			m_musics[i]->setVolume(m_musics[i]->m_volume);
		}
		for (int i = 0; i < m_sounds.size(); ++i)
		{
			m_sounds[i]->m_mute = true;
			m_sounds[i]->setVolume(m_sounds[i]->m_volume);
		}
	}
	else
	{
		for (int i = 0; i < m_musics.size(); ++i)
		{
			m_musics[i]->m_mute = false;
			m_musics[i]->setVolume(m_musics[i]->m_volume);
		}
		for (int i = 0; i < m_sounds.size(); ++i)
		{
			m_sounds[i]->m_mute = false;
			m_sounds[i]->setVolume(m_sounds[i]->m_volume);
		}
	}
}

void soundLibrary::setMusicVolume(float volume)
{
	for (int i = 0; i < m_musics.size(); ++i)
	{
		m_musics[i]->m_volumeMultiplier = volume;
		m_musics[i]->setVolume(m_musics[i]->m_volume);
	}
	m_musicVolume = volume;
}

void soundLibrary::setSoundsVolume(float volume)
{
	for (int i = 0; i < m_sounds.size(); ++i)
	{
		m_sounds[i]->m_volumeMultiplier = volume;
		m_sounds[i]->setVolume(m_sounds[i]->m_volume);
	}
	m_soundVolume = volume;
}