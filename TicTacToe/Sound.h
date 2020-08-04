#pragma once
#include "SFML/Audio.hpp"
	
class Sound
{
private:
	sf::SoundBuffer* buffer = nullptr;
	sf::Sound* sound = nullptr;
	sf::Music* music = nullptr;


	void create(std::string soundFile);
	void create(std::string musicFile, float volume);// for music
	void destroy();

public:
	Sound();
	Sound(std::string soundFile);
	Sound(std::string musicFile, float volume);		// for music
	~Sound();

	void play();
	void playMusic();


};