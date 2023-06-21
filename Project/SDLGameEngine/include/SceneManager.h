#ifndef _SCENEMANAGER_H_
#define _SCENEMANAGER_H_

#include "StartScreen.h"
#include "PlayScreen.h"

class SceneManager
{
public:


private:
	static SceneManager* m_sInstance;

	enum class SCENES
	{
		start,
		play
	};

	SCENES m_sCurrentScene;

	InputManager* m_iInputManager;

	StartScreen* m_sStartScreen;
	PlayScreen* m_pPlayScreen;


public:
	static SceneManager* Instance();
	static void Release();

	void Render();
	void Update();

	void CheckChangedScene(int scene);

private:
	SceneManager();
	~SceneManager();

};

#endif