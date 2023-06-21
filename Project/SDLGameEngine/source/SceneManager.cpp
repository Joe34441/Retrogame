#include "SceneManager.h"

SceneManager* SceneManager::m_sInstance = NULL;

SceneManager* SceneManager::Instance()
{
	if (m_sInstance == NULL)
	{
		m_sInstance = new SceneManager();
	}
	return m_sInstance;
}

void SceneManager::Release()
{
	delete m_sInstance;
	m_sInstance = NULL;
}

void SceneManager::Render()
{
	switch (m_sCurrentScene)
	{
	case SCENES::start:
		m_sStartScreen->Render();
		break;

	case SCENES::play:
		m_pPlayScreen->Render();
		break;
	}
}

void SceneManager::Update()
{
	if (m_sCurrentScene == SCENES::start) CheckChangedScene(0);
	else if (m_sCurrentScene == SCENES::play) CheckChangedScene(1);

	switch (m_sCurrentScene)
	{
	case SCENES::start:
		m_sStartScreen->Update();
		break;

	case SCENES::play:
		m_pPlayScreen->Update();
		break;
	}
}

void SceneManager::CheckChangedScene(int scene)
{
	int nextScene = scene;

	switch (m_sCurrentScene)
	{
	case SCENES::start:
		nextScene = m_sStartScreen->CheckChangedScene();
		break;

	case SCENES::play:
		nextScene = m_pPlayScreen->CheckChangedScene();
		break;
	}

	if (nextScene != scene)
	{
		switch (nextScene)
		{
		case 0:
			m_sCurrentScene = SCENES::start;
			break;

		case 1:
			m_sCurrentScene = SCENES::play;
			break;
		}
	}
}

SceneManager::SceneManager()
{
	m_iInputManager = InputManager::Instance();

	m_sStartScreen = new StartScreen();
	m_pPlayScreen = new PlayScreen();

	m_sCurrentScene = SCENES::start;
}

SceneManager::~SceneManager()
{
	m_iInputManager = NULL;

	delete m_sStartScreen;
	m_sStartScreen = NULL;

	delete m_pPlayScreen;
	m_pPlayScreen = NULL;
}
