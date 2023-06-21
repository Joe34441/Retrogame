#ifndef _GAMEMANAGER_H_
#define _GAMEMANAGER_H_

#include "Timer.h"
#include "SceneManager.h"

class GameManager
{
private:
	static GameManager* m_sInstance;

	const int FRAME_RATE = 60;
	Timer* m_tTimer;

	bool m_bQuit = false;

	Graphics* m_gGraphics;
	AssetManager* m_aAssetManager;
	InputManager* m_iInputManager;

	SceneManager* m_sSceneManager;

	SDL_Event m_sdlEvent;

public:
	static GameManager* Instance();
	static void Release();

	void Run();

private:
	GameManager();
	~GameManager();
};

#endif // _GAMEMANAGER_H_

