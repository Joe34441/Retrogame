#include "..\include\Graphics.h"

Graphics* Graphics::m_sInstance = NULL;
bool Graphics::m_bInitalised = false;

Graphics* Graphics::Instance()
{
	if (m_sInstance == NULL)
	{
		m_sInstance = new Graphics();
	}
	return m_sInstance;
}

void Graphics::Release()
{
	delete m_sInstance;
	m_sInstance = NULL;
	m_bInitalised = false;
}

bool Graphics::Initialised()
{
	return m_bInitalised;
}

void Graphics::Render()
{
	SDL_RenderPresent(m_rRenderer);
}

SDL_Texture* Graphics::LoadTexture(std::string a_sPath)
{
	SDL_Texture* tTexture = NULL;

	SDL_Surface* sSurface = IMG_Load(a_sPath.c_str());
	if (sSurface == NULL)
	{
		printf("Image Load Error: Path(%s), Error(%s)\n", a_sPath.c_str(), IMG_GetError());

		return tTexture;
	}

	tTexture = SDL_CreateTextureFromSurface(m_rRenderer, sSurface);
	if (tTexture == NULL)
	{
		printf("Texture Creation Error: %s\n", IMG_GetError());
	}

	SDL_FreeSurface(sSurface);
	return tTexture;
}

SDL_Texture* Graphics::CreateTextTexture(TTF_Font* font, std::string text, SDL_Color color)
{
	SDL_Surface* surface = TTF_RenderText_Solid(font, text.c_str(), color);
	if (surface == NULL)
	{
		printf("Text Render Error: %s\n", TTF_GetError());
		return NULL;
	}

	SDL_Texture* tex = SDL_CreateTextureFromSurface(m_rRenderer, surface);
	if (tex == NULL)
	{
		printf("Text Texture Creation Error: %s\n", TTF_GetError());
		return NULL;
	}

	SDL_FreeSurface(surface);

	return tex;
}

void Graphics::ClearBackBuffer()
{
	SDL_RenderClear(m_rRenderer);
}

void Graphics::DrawTexture(SDL_Texture* a_tTexture, Vector2& a_vPos, int a_iWidth, int a_iHeight, float a_fRot)
{
	SDL_Rect renderQuad = { a_vPos.x, a_vPos.y, a_iWidth, a_iHeight };
	SDL_RendererFlip rFlip = SDL_FLIP_NONE;

	SDL_RenderCopyEx(m_rRenderer, a_tTexture, NULL, &renderQuad, a_fRot, NULL, rFlip);
}

Graphics::Graphics()
{
	m_bBackBuffer = NULL;
	m_bInitalised = Init();
}

Graphics::~Graphics()
{
	SDL_DestroyWindow(m_wWindow);
	m_wWindow = NULL;

	SDL_DestroyRenderer(m_rRenderer);
	m_rRenderer = NULL;

	IMG_Quit();

	TTF_Quit();

	SDL_Quit();
}

bool Graphics::Init()
{
	if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO) < 0)
	{
		printf("Initialisation Error:  %s\n", SDL_GetError());
		return false;
	}

	m_wWindow = SDL_CreateWindow("^^^^^^", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);

	if (m_wWindow == NULL)
	{
		printf("Window Creation Error: %s\n", SDL_GetError());
		return false;
	}

	m_rRenderer = SDL_CreateRenderer(m_wWindow, -1, SDL_RENDERER_ACCELERATED);
	if (m_rRenderer == NULL)
	{
		printf("Renderer Creation Error: %s\n", SDL_GetError());
		return false;
	}

	SDL_SetRenderDrawColor(m_rRenderer, 0x00, 0x00, 0x00, 0xFF); //black background

	int iFlag = IMG_INIT_PNG;
	if (!(IMG_Init(iFlag) & iFlag))
	{
		printf("Image Initalisation Error: %s\n", IMG_GetError());
		return false;
	}

	if (TTF_Init() == -1)
	{
		printf("TTF Initalisation Error: %s\n", TTF_GetError());
		return false;
	}



	m_bBackBuffer = SDL_GetWindowSurface(m_wWindow);
	return true;
}
