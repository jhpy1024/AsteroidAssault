#ifndef AUDIO_MANAGER_HPP
#define AUDIO_MANAGER_HPP

#include <memory>
#include <map>
#include <string>

#include <SDL.h>
#include <SDL_mixer.h>

class AudioManager
{
public:
	~AudioManager();

	static AudioManager& getInstance();

	void loadSound(const std::string& id, const std::string& fileName);
	void playSound(const std::string& id, int loops = 0);

	void loadMusic(const std::string& id, const std::string& fileName);
	void playMusic(const std::string& id, int loops = 0);

	void toggleAudioEnabled();
	bool isAudioEnabled() const;

	void setMusicVolume(int volume);
	void setSoundVolume(int volume);

	int getMusicVolume() const;
	int getSoundVolume() const;

private:
	AudioManager();

	void freeAllSounds();
	void freeAllMusic();

private:
	static std::unique_ptr<AudioManager> m_Instance;

	std::map<std::string, Mix_Chunk*> m_Sounds;
	std::map<std::string, Mix_Music*> m_Music;

	bool m_AudioEnabled;

	int m_MusicVolume;
	int m_SoundVolume;
};

#endif