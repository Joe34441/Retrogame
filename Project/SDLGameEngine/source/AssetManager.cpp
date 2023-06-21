#include "AssetManager.h"

AssetManager* AssetManager::m_sInstance = NULL;

AssetManager* AssetManager::Instance() {

	if (m_sInstance == NULL)
	{
		m_sInstance = new AssetManager();
	}

	return m_sInstance;
}

void AssetManager::Release()
{
	delete m_sInstance;
	m_sInstance = NULL;
}

SDL_Texture* AssetManager::GetTexture(std::string filename)
{
	char* cBasePath = SDL_GetBasePath();
	std::string sPath = cBasePath;
	sPath.append("Assets/" + filename);

	if (m_tTextures[sPath] == nullptr)
	{
		m_tTextures[sPath] = Graphics::Instance()->LoadTexture(sPath);
	}

	SDL_free(cBasePath);

	return m_tTextures[sPath];
}

SDL_Texture* AssetManager::GetText(std::string text, std::string filename, int size, SDL_Color color)
{
	TTF_Font* font = GetFont(filename, size);

	//key represents the combination of text, file name, size, RGB values
	std::string key = text + filename + static_cast<char>(size) + static_cast<char>(color.r) + static_cast<char>(color.b) + static_cast<char>(color.g);

	if (m_tText[key] == nullptr)
	{
		m_tText[key] = Graphics::Instance()->CreateTextTexture(font, text, color);
	}

	return m_tText[key];
}

Mix_Music* AssetManager::GetMusic(std::string filename)
{
	char* cBasePath = SDL_GetBasePath();
	std::string sPath = cBasePath;
	sPath.append("Assets/Audio/" + filename);

	if (m_mMusic[sPath] == nullptr)
	{
		m_mMusic[sPath] = Mix_LoadMUS(sPath.c_str());

		if (m_mMusic[sPath] == NULL)
		{
			printf("Music Loading Error: File-%s Error-%s", filename.c_str(), Mix_GetError());
		}
	}

	SDL_free(cBasePath);

	return m_mMusic[sPath];
}

Mix_Chunk* AssetManager::GetSFX(std::string filename)
{
	char* cBasePath = SDL_GetBasePath();
	std::string sPath = cBasePath;
	sPath.append("Assets/Audio/" + filename);

	if (m_mSFX[sPath] == nullptr)
	{
		m_mSFX[sPath] = Mix_LoadWAV(sPath.c_str());

		if (m_mSFX[sPath] == NULL)
		{
			printf("SFX Loading Error: File-%s Error-%s", filename.c_str(), Mix_GetError());
		}
	}

	SDL_free(cBasePath);

	return m_mSFX[sPath];
}

TTF_Font* AssetManager::GetFont(std::string filename, int size)
{
	char* cBasePath = SDL_GetBasePath();
	std::string sPath = cBasePath;
	sPath.append("Assets/Fonts/" + filename);

	std::string key = sPath + static_cast<char>(size);

	if (m_fFonts[key] == nullptr)
	{
		m_fFonts[key] = TTF_OpenFont(sPath.c_str(), size);
		if (m_fFonts[key] == nullptr)
		{
			printf("Font Loading Error: Font-%s Error-%s", filename.c_str(), TTF_GetError());
		}
	}

	SDL_free(cBasePath);

	return m_fFonts[key];
}

AssetManager::AssetManager()
{
}

AssetManager::~AssetManager()
{
	for (auto tex : m_tTextures)
	{
		if (tex.second != NULL)
		{
			SDL_DestroyTexture(tex.second);
		}
	}

	m_tTextures.clear();


	for (auto text : m_tText)
	{
		if (text.second != NULL)
		{
			SDL_DestroyTexture(text.second);
		}
	}

	m_tText.clear();


	for (auto font : m_fFonts)
	{
		if (font.second != NULL)
		{
			TTF_CloseFont(font.second);
		}
	}

	m_fFonts.clear();
}