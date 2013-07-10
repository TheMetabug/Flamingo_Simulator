#include <sound.h>

///////// MUSIC /////////
music::music()
{
	m_music = new sf::Music();
}
music::music(std::string Filename)
{
	m_music = new sf::Music();
	m_music->setLoop(true);
	m_music->setVolume(30);

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

///////// SOUND //////////

sound::sound()
{
	m_buffer = new sf::SoundBuffer();
	m_sound = new sf::Sound();
	m_sound->setBuffer(*m_buffer);
}
sound::sound(std::string Filename)
{
	m_buffer = new sf::SoundBuffer();
	load(Filename);
	m_sound = new sf::Sound();
	m_sound->setBuffer(*m_buffer);
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



soundLibrary::soundLibrary()
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

#pragma endregion here we keep the sounds, dont mix us plz
}
soundLibrary::~soundLibrary()
{}

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