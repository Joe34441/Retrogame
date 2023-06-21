#ifndef _AUDIOMANAGER_H_
#define _AUDIOMANAGER_H_

#include "AssetManager.h"

class AudioManager
{

private:
	static AudioManager* m_sInstance;

	AssetManager* m_aAssetManager;

public:
	static AudioManager* Instance();
	static void Release();

	void PlayMusic(std::string filename, int loops = -1);
	void PauseMusic();
	void ResumeMusic();

	void PlaySFX(std::string filename, int loops = 0, int channel = 0);

	void SetVolume(float volume);

private:
	AudioManager();
	~AudioManager();

};

#endif