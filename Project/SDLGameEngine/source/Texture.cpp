#include "..\include\Texture.h"

Texture::Texture(std::string a_sPath, Vector2& a_vPos, int a_iWidth, int a_iHeight, float a_fRot)
{
	m_gGraphics = Graphics::Instance();
	
	m_vPos = a_vPos;
	m_iWidth = a_iWidth;
	m_iHeight = a_iHeight;
	m_fRotation = a_fRot;

	m_tTexture = AssetManager::Instance()->GetTexture(a_sPath);
}

Texture::Texture(std::string a_sPath, std::string a_sText, int size, SDL_Color color)
{
	m_gGraphics = Graphics::Instance();
	m_tTexture = AssetManager::Instance()->GetText(a_sText, a_sPath, size, color);

	SDL_QueryTexture(m_tTexture, NULL, NULL, &m_iWidth, &m_iHeight);
}



Texture::~Texture()
{
	m_tTexture = NULL;
	m_gGraphics = NULL;
}

void Texture::Render()
{
	m_gGraphics->DrawTexture(m_tTexture, m_vPos, m_iWidth, m_iHeight, m_fRotation);
}
