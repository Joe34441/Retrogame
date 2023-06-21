#ifndef _STARTSCREEN_H_
#define _STARTSCREEN_H_


#include "InputManager.h"
#include "Texture.h"
#include "GameEntity.h"
#include "Colors.h"
#include "Timer.h"
#include "InputManager.h"
#include "AudioManager.h"

class StartScreen
{
private:
	Colors* m_cColors;
	Timer* m_tTimer;
	InputManager* m_iInputManager;
	AudioManager* m_aAudioManager;

	int m_iSceneToOpen = 0;

	//variables for menu text allignment etc
	const static int m_iTextSize = 80;
	const static int m_iTextSelectedSize = m_iTextSize + 10;
	const static int m_iTextIndent = 50;
	const static int m_iLineGap = 90;

	
	//all options in the menus
	struct Menu
	{
		std::map<int, Texture*> m_tMenuOptions;	//map of menu options textures
		int m_iSelectedOptionIndex = 0;
		int m_iNumberOfOptions;
		std::map<int, bool> m_bMenuOptionsEnabled; //boolean states of each options (enabled/disabled true/false)
	}; 

	int m_iCurrentMenu = 1;

	Menu MainMenu; //first & main menu
	Menu PlayMenu; //play menu
	Menu SettingsMenu; //settings menu
	Menu CreditsMenu; //credits menu


	//variables for stars background
	std::map<int, Texture*> m_tStars; //map of background stars

	std::string m_sStarPath;

	const static int m_iNumberOfStars = 20;

	Vector2 m_vStarsPositions[m_iNumberOfStars];
	Vector2 m_vStarsSizes[m_iNumberOfStars];

	float m_fStarsRotations[m_iNumberOfStars];

	int m_iStarsStates[m_iNumberOfStars];

	float m_fStarsAnimationTimer;
	float m_fStarsTotalAnimationTime;

	bool m_bStarsAnimationFinished;



	//variables for the title animation
	const static int m_iTitleTextSize = 200;

	Texture m_tTitle = Texture("RooseSally.ttf", "^", m_iTitleTextSize, { 0, 0, 0 });

	Vector2 m_vTitleAnimationStartPosNormal;
	Vector2 m_vTitleAnimationStartPosExtended;

	float m_fTitleAnimationTimer;
	float m_fTitleTotalAnimationTime;

	bool m_bTitleAnimationFinished;


	//variables for the spaceship
	Vector2 m_vSpaceshipSize;
	Vector2 m_vSpaceshipPos;

	Texture m_tSpaceship = Texture("Sprites/Special/Background/spaceshipflyingnoengine.png", m_vSpaceshipPos,
									static_cast<int>(m_vSpaceshipSize.x), static_cast<int>(m_vSpaceshipSize.y), 0.0f);


	//variables for the engine animation
	Vector2 m_vSpaceshipEngineSize;
	Vector2 m_vSpaceshipEngineAnimationStartPos;

	float m_fSpaceshipEngineAnimationTimer;
	float m_fSpaceshipEngineTotalAnimationTime;

	bool m_bSpaceshipAnimationFinished;

	Texture m_tSpaceshipEngine = Texture("Sprites/Special/Background/spaceshipengine-1.png", m_vSpaceshipEngineAnimationStartPos, 
										  static_cast<int>(m_vSpaceshipEngineSize.x), static_cast<int>(m_vSpaceshipEngineSize.y), 0.0f);

	//variables for the credits screen
	std::map<int, Texture*> m_tCreditsScreen;
	const int m_iCreditsTextSize = 30;
	const int m_iNumOfCreditsLines = 14;

public:
	StartScreen();
	~StartScreen();

	void Update();

	void Render();

	int CheckChangedScene();

private:
	void InitialiseMenu();
	void InitialiseStars();

	void GetMenuUpdate();
	void ApplyMenuUpdate();

	void UpdateAnimations();

	void UpdateTitleAnimation();
	void UpdateSpaceshipAnimation();
	void UpdateStarsAnimation();
};


#endif