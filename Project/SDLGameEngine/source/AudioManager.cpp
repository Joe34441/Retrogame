#include "AudioManager.h"

AudioManager* AudioManager::m_sInstance = NULL;

AudioManager* AudioManager::Instance()
{
	if (m_sInstance == NULL)
	{
		m_sInstance = new AudioManager();
	}

	return m_sInstance;
}

void AudioManager::Release()
{
	delete m_sInstance;
	m_sInstance = NULL;
}

void AudioManager::PlayMusic(std::string filename, int loops)
{
	Mix_PlayMusic(m_aAssetManager->GetMusic(filename), loops);
}

void AudioManager::PauseMusic()
{
	if (Mix_PlayingMusic() != 0)
	{
		Mix_PauseMusic();
	}
}

void AudioManager::ResumeMusic()
{
	if (Mix_PausedMusic() != 0)
	{
		Mix_ResumeMusic();
	}
}

void AudioManager::PlaySFX(std::string filename, int loops, int channel)
{
	Mix_PlayChannel(channel, m_aAssetManager->GetSFX(filename), loops);
}

void AudioManager::SetVolume(float volume)
{
	Mix_VolumeMusic((volume / 100.0f) * MIX_MAX_VOLUME);
}

AudioManager::AudioManager()
{
	m_aAssetManager = AssetManager::Instance();

	if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, MIX_DEFAULT_CHANNELS, 4096) < 0)
	{
		printf("Mixer Initialization Error: %s\n", Mix_GetError());
	}
}

AudioManager::~AudioManager()
{
	m_aAssetManager = NULL;
	Mix_Quit();
}
