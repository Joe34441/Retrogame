#ifndef _ASSETMANAGER_H_
#define _ASSETMANAGER_H_

#include "Graphics.h"
#include <map>
#include <SDL_mixer.h>

class AssetManager
{

private:
	static AssetManager* m_sInstance;

	std::map<std::string, SDL_Texture*> m_tTextures;

	std::map<std::string, SDL_Texture*> m_tText;
	std::map<std::string, TTF_Font*> m_fFonts;

	std::map<std::string, Mix_Music*> m_mMusic;
	std::map<std::string, Mix_Chunk*> m_mSFX;

public:
	static AssetManager* Instance();
	static void Release();

	SDL_Texture* GetTexture(std::string filename);

	SDL_Texture* GetText(std::string text, std::string filename, int size, SDL_Color color);

	Mix_Music* GetMusic(std::string filename);
	Mix_Chunk* GetSFX(std::string filename);

private:
	TTF_Font* GetFont(std::string filename, int size);

	AssetManager();
	~AssetManager();
};

#endif