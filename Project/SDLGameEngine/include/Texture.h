#ifndef _TEXTURE_H_
#define _TEXTURE_H_

#include "GameEntity.h"
#include "AssetManager.h"

class Texture : public GameEntity
{
private:
	SDL_Texture* m_tTexture;

	Graphics* m_gGraphics;

public:
	Texture(std::string a_sPath, Vector2& a_vPos, int a_iWidth, int a_iHeight, float a_fRot);
	Texture(std::string a_sPath, std::string a_sText, int size, SDL_Color color);

	~Texture();

	virtual void Render();
};

#endif // ! _TEXTURE_H_
