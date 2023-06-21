#ifndef _PLAYSCREEN_H_
#define _PLAYSCREEN_H_

#include "InputManager.h"
#include "Texture.h"
#include "GameEntity.h"
#include "Colors.h"
#include "Timer.h"
#include "Levels.h"
#include "AudioManager.h"
#include "CollisionManager.h"
#include "LevelChanger.h"
#include "SpecialObjects.h"

class PlayScreen
{
private:
	//instances
	Timer* m_tTimer;
	InputManager* m_iInputManager;
	AudioManager* m_aAudioManager;
	CollisionManager* m_cCollisionManager;
	Colors* m_cColors;
	Levels* m_lLevels;
	LevelChanger* m_lLevelChanger;

	int m_iSceneToOpen; //scene to open


	//textures drawn for all levels
	Texture* m_tPlayerTexture;
	Texture* m_tBackgroundTexture;
	Texture* m_tLevelTitleTexture;
	Texture* m_tTimerTexture1;
	Texture* m_tTimerTexture2;
	Texture* m_tTimerTexture3;
	Texture* m_tGameOverTexture;

	const int m_iTitleTextSize = 75;
	const int m_iTimerTextSize = 45;


	//textures for special objects
	const static int m_iMaxNumOfSpeicalObjects = 20;
	Texture* m_tSpecialObjectsTextures[m_iMaxNumOfSpeicalObjects];
	bool m_bSpecialObjectsEnabled[m_iMaxNumOfSpeicalObjects];


	//constant textures for all levels
	const int m_iStandardTextureSize = 25;

	const Vector2 m_vPlaySpace = Vector2(775, 775);
	const Vector2 m_vPlayerSize = Vector2(42, 68);

	//variables for player
	Vector2 m_vPlayerTranslationLeft = Vector2(0, 0);
	Vector2 m_vPlayerTranslationRight = Vector2(0, 0);

	Texture* m_tLevelLayoutTextures[Levels::m_iLevelDepth][Levels::m_iLevelWidth]; //textures in displayed level

	int m_iCollisionState = 0; //collision state

	bool m_bFalling = true;

	const float m_fPlayerMovementSpeed = 6.0f;
	const float m_fPlayerFallingSpeed = 7.0f;

	float m_fPlayerDeathTimer = 0.0f;
	const float m_fPlayerDeathTime = 2.0f;
	bool m_bPlayerDeathFinished = false;

	struct AnimationFlags
	{
		bool dead = false;
		bool movingLeft = false;
		bool movingRight = false;
		bool jumpingLeft = false;
		bool jumpingRight = false;
		bool fallingLeft = false;
		bool fallingRight = false;
		bool jumping = false;
		bool falling = false;
		bool facingRight = false;
	};

	AnimationFlags PlayerAnimationFlags;

	std::string m_sLevel = "1-1"; //current level

	int m_iCurrentLevelIndex = 0;
	int m_iActiveCheckpointIndex = 0;

	const float m_fStage1TotalTime = 190.0f;
	float m_fStage1Timer = 0.0f;
	bool m_bStage1TimeOver = false;

	const float m_fGameOverScreenTotalTime = 3.0f;
	float m_fGameOverScreenTimer = 0.0f;
	bool m_bGameOver = false;

public:
	PlayScreen();
	~PlayScreen();

	void Update();
	void Render();

	void SetLevel(std::string sLevel);
	int CheckChangedScene();

	void RestartScene();

private:
	void GetInputs(Vector2& vTranslationLeft, Vector2& vTranslationRight);
	void CheckCollisions();
	void ApplyInputs();
	void AnimatePlayer();
	void ChangeNextLevel();
	void ChangeBackLevel();
	void UpdateSpecialObjects();
	void ApplyPlayerDeath();
	void UpdateTimer();
	void GameOver();

	void SetTextureMap(std::string level);
};

#endif // !_PLAYSCREEN_H_
