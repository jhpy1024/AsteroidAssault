#ifndef AUDIO_MANAGER_HPP
#define AUDIO_MANAGER_HPP

#include <memory>
#include <map>
#include <string>

#include <SDL_mixer.h>

class AudioManager
{
public:
	static AudioManager& getInstance();

	void loadSound(const std::string& id, const std::string& fileName);
	void playSound(const std::string& id);

	void loadMusic(const std::string& id, const std::string& fileName);
	void playMusic(const std::string& id);

private:
	AudioManager();

	void freeSound(Mix_Chunk* chunk);
	void freeMusic(Mix_Music* music);

private:
	static std::unique_ptr<AudioManager> m_Instance;

	std::map<std::string, std::unique_ptr<Mix_Chunk, decltype(freeSound)>> m_Sounds;
	std::map<std::string, std::unique_ptr<Mix_Music, decltype(freeMusic)>> m_Music;
};

#endif