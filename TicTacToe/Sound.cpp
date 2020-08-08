#include "Sound.h"
#include "MYDEBUGHELPER.h"

Sound::Sound()
{
	
}

Sound::Sound(std::string soundFile)
{
	create(soundFile);
}

Sound::Sound(std::string musicFile, float volume)
{
	create(musicFile, volume);
}

Sound::~Sound()
{
	destroy();
}

void Sound::destroy()
{
	delete buffer;
	delete sound;
	delete music;
}

void Sound::create(std::string soundFile)
{
	buffer = new sf::SoundBuffer;
	sound = new sf::Sound;
	sound->setBuffer(*buffer);

	// Load our .wav buffer sample settings (16bit) to be read by sfml
	if (!buffer->loadFromFile(soundFile))
	{
		std::cout << "FILE: (" << soundFile << ") FAILED TO LOAD!" << std::endl;
	}
}

// Our music create fn
void Sound::create(std::string musicFile, float volume)
{
	music = new sf::Music;
	music->setVolume(volume);
	music->setLoop(true);

	if (!music->openFromFile(musicFile))
	{
		std::cout << "FILE: (" << musicFile << ") FAILED TO LOAD!" << std::endl;
	}
}

// Can we pass sf::music or sf::sound?
void Sound::play()
{
	sound->play();
}

void Sound::playMusic()
{
	music->play();
}