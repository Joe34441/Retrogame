#include "..\include\GameManager.h"

GameManager* GameManager::m_sInstance = NULL;


GameManager* GameManager::Instance()
{
	if (m_sInstance == NULL)
	{
		m_sInstance = new GameManager();
	}
	return m_sInstance;
}

void GameManager::Release()
{
	delete m_sInstance;
	m_sInstance = NULL;

	Timer::Release();
}

void GameManager::Run()
{
	while (!m_bQuit)
	{
		m_tTimer->Update();

		while (SDL_PollEvent(&m_sdlEvent) != 0)
		{
			if (m_sdlEvent.type == SDL_QUIT)
			{
				m_bQuit = true;
			}
		}

		if (m_tTimer->DeltaTime() >= 1.0f / FRAME_RATE)
		{
			m_gGraphics->ClearBackBuffer();

			//call update & render on the scene manager
			m_sSceneManager->Update();
			m_sSceneManager->Render();
			

			m_gGraphics->Render();

			m_iInputManager->UpdatePreviousInput();

			m_tTimer->Reset();
		}
	}
}

GameManager::GameManager()
{
	m_bQuit = false;
	m_gGraphics = Graphics::Instance();

	if (!Graphics::Initialised())
	{
		m_bQuit = true;
	}

	m_aAssetManager = AssetManager::Instance();

	m_tTimer = Timer::Instance();

	m_iInputManager = InputManager::Instance();

	m_sSceneManager = SceneManager::Instance();
}

GameManager::~GameManager()
{
	AssetManager::Release();
	m_aAssetManager = NULL;

	SceneManager::Release();
	m_sSceneManager = NULL;

	Graphics::Release();
	m_gGraphics = NULL;

	Timer::Release();
	m_tTimer = NULL;

	InputManager::Release();
	m_iInputManager = NULL;
}
