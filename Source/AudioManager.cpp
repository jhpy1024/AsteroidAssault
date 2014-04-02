#include "AudioManager.hpp"

#include <iostream>
#include <cassert>

AudioManager::AudioManager()
{
	// TODO
	// ====================================================
	// Experiment with the chunk size if there is sound lag
	// ====================================================
	auto result = Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048);

	if (result < 0)
		std::cerr << "SDL_mixer failed to initialize:\n" << Mix_GetError() << std::endl;
}

void AudioManager::loadSound(const std::string& id, const std::string& fileName)
{
	auto sound = std::unique_ptr<Mix_Chunk, decltype(freeSound)>(Mix_LoadWAV(fileName.c_str()), &AudioManager::freeSound);

	assert(sound != nullptr);
	 
	m_Sounds[id] = std::move(sound);
}

void AudioManager::loadMusic(const std::string& id, const std::string& fileName)
{
	auto music = std::unique_ptr<Mix_Music, decltype(freeMusic)>(Mix_LoadMUS(fileName.c_str()), &AudioManager::freeMusic);

	assert(music != nullptr);

	m_Music[id] = std::move(music);
}

void AudioManager::freeSound(Mix_Chunk* chunk)
{
	Mix_FreeChunk(chunk);
}

void AudioManager::freeMusic(Mix_Music* music)
{
	Mix_FreeMusic(music);
}

// TODO
// ===================
// Allow looping sound
// ===================
void AudioManager::playSound(const std::string& id)
{
	Mix_PlayChannel(-1, m_Sounds[id].get(), 0);
}

// TODO
// ===================
// Allow looping music
// ===================
void AudioManager::playMusic(const std::string& id)
{
	Mix_PlayMusic(m_Music[id].get(), 0);
}

AudioManager& AudioManager::getInstance()
{
	if (m_Instance == nullptr)
		m_Instance = std::unique_ptr<AudioManager>(new AudioManager);

	return *m_Instance;
}