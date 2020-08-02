#pragma once
#include "SFML/Audio.hpp"
	
class Sound
{
private:
	sf::SoundBuffer* buffer = nullptr;
	sf::Sound* sound = nullptr;


	void create(std::string soundFile);
	void destroy();

public:
	Sound();
	Sound(std::string soundFile);
	~Sound();

	void play();


};