#include "AudioManager.hpp"

#include <iostream>
#include <cassert>

std::unique_ptr<AudioManager> AudioManager::m_Instance;

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

AudioManager::~AudioManager()
{
	freeAllSounds();
	freeAllMusic();
}

void AudioManager::loadSound(const std::string& id, const std::string& fileName)
{
	auto sound = Mix_LoadWAV(fileName.c_str());

	assert(sound != nullptr);
	 
	m_Sounds[id] = sound;
}

void AudioManager::loadMusic(const std::string& id, const std::string& fileName)
{
	auto music = Mix_LoadMUS(fileName.c_str());

	assert(music != nullptr);

	m_Music[id] = music;
}

void AudioManager::freeAllSounds()
{
	for (auto& pair : m_Sounds)
	{
		Mix_FreeChunk(pair.second);
	}

	m_Sounds.clear();
}

void AudioManager::freeAllMusic()
{
	for (auto& pair : m_Music)
	{
		Mix_FreeMusic(pair.second);
	}

	m_Music.clear();
}

void AudioManager::playSound(const std::string& id, int loops)
{
	Mix_PlayChannel(-1, m_Sounds[id], loops);
}

void AudioManager::playMusic(const std::string& id, int loops)
{
	Mix_PlayMusic(m_Music[id], loops);
}

AudioManager& AudioManager::getInstance()
{
	if (m_Instance == nullptr)
		m_Instance = std::unique_ptr<AudioManager>(new AudioManager);

	return *m_Instance;
}