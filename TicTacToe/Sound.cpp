#include "Sound.h"
#include "MYDEBUGHELPER.h"

Sound::Sound()
{
	
}

Sound::Sound(std::string soundFile)
{
	create(soundFile);
}

Sound::~Sound()
{
	destroy();
}

void Sound::destroy()
{
	delete buffer;		// do we even need to delete this? everything inside will be deleted
	delete sound;
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

void Sound::play()
{
	sound->play();
}