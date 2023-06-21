#include "StartScreen.h"


void StartScreen::Update()
{
	m_iSceneToOpen = 0;

	UpdateAnimations();
	GetMenuUpdate();
	ApplyMenuUpdate();
}

void StartScreen::GetMenuUpdate()
{
	//do keypressed etc
	if (m_iInputManager->KeyPressed(SDL_SCANCODE_W) ||
		m_iInputManager->KeyPressed(SDL_SCANCODE_UP))
	{
		// menu -= 1
		switch (m_iCurrentMenu)
		{
		case 1:
			if (MainMenu.m_iSelectedOptionIndex - 1 < 0) MainMenu.m_iSelectedOptionIndex = MainMenu.m_iNumberOfOptions - 1;
			else MainMenu.m_iSelectedOptionIndex -= 1;
			break;

		case 2:
			if (PlayMenu.m_iSelectedOptionIndex - 1 < 0) PlayMenu.m_iSelectedOptionIndex = PlayMenu.m_iNumberOfOptions - 1;
			else PlayMenu.m_iSelectedOptionIndex -= 1;
			break;

		case 3:
			if (SettingsMenu.m_iSelectedOptionIndex - 1 < 0) SettingsMenu.m_iSelectedOptionIndex = SettingsMenu.m_iNumberOfOptions - 1;
			else SettingsMenu.m_iSelectedOptionIndex -= 1;
			break;

		case 4:
			//only "Back" button - no need to change option
			break;
		}
	}

	if (m_iInputManager->KeyPressed(SDL_SCANCODE_S) ||
		m_iInputManager->KeyPressed(SDL_SCANCODE_DOWN))
	{
		// menu += 1
		switch (m_iCurrentMenu)
		{
		case 1:
			if (MainMenu.m_iSelectedOptionIndex + 1 >= MainMenu.m_iNumberOfOptions) MainMenu.m_iSelectedOptionIndex = 0;
			else MainMenu.m_iSelectedOptionIndex += 1;
			break;

		case 2:
			if (PlayMenu.m_iSelectedOptionIndex + 1 >= PlayMenu.m_iNumberOfOptions) PlayMenu.m_iSelectedOptionIndex = 0;
			else PlayMenu.m_iSelectedOptionIndex += 1;
			break;

		case 3:
			if (SettingsMenu.m_iSelectedOptionIndex + 1 >= SettingsMenu.m_iNumberOfOptions) SettingsMenu.m_iSelectedOptionIndex = 0;
			else SettingsMenu.m_iSelectedOptionIndex += 1;
			break;

		case 4:
			//only "Back" button - no need to change option
			break;
		}
	}

	if (m_iInputManager->KeyPressed(SDL_SCANCODE_D) ||
		m_iInputManager->KeyPressed(SDL_SCANCODE_RIGHT) ||
		m_iInputManager->KeyPressed(SDL_SCANCODE_SPACE) ||
		m_iInputManager->KeyPressed(SDL_SCANCODE_RETURN))
	{
		switch (m_iCurrentMenu)
		{
		case 1: //main menu
			if (MainMenu.m_iSelectedOptionIndex == 0) m_iCurrentMenu = 2;
			else if (MainMenu.m_iSelectedOptionIndex == 1) m_iCurrentMenu = 3;
			else if (MainMenu.m_iSelectedOptionIndex == 2) m_iCurrentMenu = 4;
			else if (MainMenu.m_iSelectedOptionIndex == 3) exit(EXIT_SUCCESS);
			break;

		case 2: //play menu
			if (PlayMenu.m_iSelectedOptionIndex == 0)
			{
				m_iSceneToOpen = 1;
				m_aAudioManager->PauseMusic();
				m_aAudioManager->PlayMusic("track1-1.wav", 1);
			}
			else if (PlayMenu.m_iSelectedOptionIndex == 1)
			{
				//load stage 2, which hasnt been added yet
			}
			else if (PlayMenu.m_iSelectedOptionIndex == 2) m_iCurrentMenu = 1;
			break;

		case 3: //settings menu
			if (SettingsMenu.m_iSelectedOptionIndex == 0)
			{
				m_aAudioManager->SetVolume(0.0f);
			}
			else if (SettingsMenu.m_iSelectedOptionIndex == 1)
			{
				m_aAudioManager->SetVolume(50.0f);
			}
			else if (SettingsMenu.m_iSelectedOptionIndex == 2)
			{
				m_aAudioManager->SetVolume(100.0f);
			}
			else if (SettingsMenu.m_iSelectedOptionIndex == 3)
			{
				m_iCurrentMenu = 1;
			}
			break;

		case 4: //credits menu
			m_iCurrentMenu = 1;
			break;
		}

		//set selected option to the top most one
		MainMenu.m_iSelectedOptionIndex = 0;
		PlayMenu.m_iSelectedOptionIndex = 0;
		SettingsMenu.m_iSelectedOptionIndex = 0;
		CreditsMenu.m_iSelectedOptionIndex = 0;
	}
}

void StartScreen::ApplyMenuUpdate()
{
	//switch menu or change selected options etc
	switch (m_iCurrentMenu)
	{
	case 1:
		for (int i = 0; i < MainMenu.m_iNumberOfOptions; i++)
		{
			if (i == MainMenu.m_iSelectedOptionIndex) //this option will be selected
			{
				MainMenu.m_bMenuOptionsEnabled[i] = true;
			}
			else //this option will remain or become deselected
			{
				MainMenu.m_bMenuOptionsEnabled[i] = false;
			}
		}
		break;

	case 2:
		for (int i = 0; i < PlayMenu.m_iNumberOfOptions; i++)
		{
			if (i == PlayMenu.m_iSelectedOptionIndex) //this option will be selected
			{
				PlayMenu.m_bMenuOptionsEnabled[i] = true;
			}
			else //this option will remain or become deselected
			{
				PlayMenu.m_bMenuOptionsEnabled[i] = false;
			}
		}
		break;

	case 3:
		for (int i = 0; i < SettingsMenu.m_iNumberOfOptions; i++)
		{
			if (i == SettingsMenu.m_iSelectedOptionIndex) //this option will be selected
			{
				SettingsMenu.m_bMenuOptionsEnabled[i] = true;
			}
			else //this option will remain or become deselected
			{
				SettingsMenu.m_bMenuOptionsEnabled[i] = false;
			}
		}
		break;

	case 4:
		
		for (int i = 0; i < CreditsMenu.m_iNumberOfOptions; i++)
		{
			if (i == CreditsMenu.m_iSelectedOptionIndex) //this option will be selected
			{
				CreditsMenu.m_bMenuOptionsEnabled[i] = true;
			}
			else //this option will remain or become deselected
			{
				CreditsMenu.m_bMenuOptionsEnabled[i] = false;
			}
		}
		break;
	}

}

void StartScreen::UpdateAnimations()
{
	if (!m_bStarsAnimationFinished)
	{
		m_fStarsAnimationTimer += m_tTimer->DeltaTime();
		UpdateStarsAnimation();
	}
	else
	{
		m_fStarsAnimationTimer = 0.0f;
		m_bStarsAnimationFinished = false;
	}

	if (!m_bTitleAnimationFinished)
	{
		m_fTitleAnimationTimer += m_tTimer->DeltaTime();
		UpdateTitleAnimation();
	}
	else
	{
		m_fTitleAnimationTimer = 0.0f;
		m_bTitleAnimationFinished = false;
	}

	if (!m_bSpaceshipAnimationFinished)
	{
		m_fSpaceshipEngineAnimationTimer += m_tTimer->DeltaTime();
		UpdateSpaceshipAnimation();
	}
	else
	{
		m_fSpaceshipEngineAnimationTimer = 0.0f;
		m_bSpaceshipAnimationFinished = false;
	}
}

void StartScreen::UpdateStarsAnimation()
{
	if (m_fStarsAnimationTimer > m_fStarsTotalAnimationTime)
	{
		for (int i = 0; i <= m_iNumberOfStars; i++)
		{
			if (m_iStarsStates[i] <= 6) //if at index 6 it will not draw for this rotation
			{
				m_iStarsStates[i] += 1;
			}
			else
			{
				m_iStarsStates[i] = 1;
			}

			if (m_iStarsStates[i] == 1) m_sStarPath = "Sprites/Special/Background/star1.png";
			else if (m_iStarsStates[i] == 2) m_sStarPath = "Sprites/Special/Background/star2.png";
			else if (m_iStarsStates[i] == 3) m_sStarPath = "Sprites/Special/Background/star3.png";
			else if (m_iStarsStates[i] == 4) m_sStarPath = "Sprites/Special/Background/star4.png";
			else if (m_iStarsStates[i] == 5) m_sStarPath = "Sprites/Special/Background/star5.png";

			m_tStars[i + 1] = new Texture(m_sStarPath, m_vStarsPositions[i], m_vStarsSizes[i].x, m_vStarsSizes[i].y, m_fStarsRotations[i]);
		}
		m_bStarsAnimationFinished = true;
	}
}

void StartScreen::UpdateSpaceshipAnimation()
{
	if (m_fSpaceshipEngineAnimationTimer < (m_fSpaceshipEngineTotalAnimationTime / 2.0f))
	{
		m_tSpaceshipEngine = Texture("Sprites/Special/Background/spaceshipengine-1.png", m_vSpaceshipEngineAnimationStartPos, m_vSpaceshipEngineSize.x, m_vSpaceshipEngineSize.y, 0.0f);
		m_tSpaceship = Texture("Sprites/Special/Background/spaceshipflyingnoengine.png", m_vSpaceshipPos, m_vSpaceshipSize.x, m_vSpaceshipSize.y, 0.0f);
	}
	else
	{
		m_tSpaceshipEngine = Texture("Sprites/Special/Background/spaceshipengine-2.png", m_vSpaceshipEngineAnimationStartPos, m_vSpaceshipEngineSize.x, m_vSpaceshipEngineSize.y, 0.0f);
		m_tSpaceship = Texture("Sprites/Special/Background/spaceshipflyingnoengine.png", m_vSpaceshipPos, m_vSpaceshipSize.x, m_vSpaceshipSize.y, 0.0f);
	}

	//set flag to reset timer
	if (m_fSpaceshipEngineAnimationTimer > m_fSpaceshipEngineTotalAnimationTime) m_bSpaceshipAnimationFinished = true;
}

void StartScreen::UpdateTitleAnimation()
{
#pragma region Title Animation
	//phase 1
	if (m_fTitleAnimationTimer <= 3.0f)
	{
		if (m_fTitleAnimationTimer < 0.5f) m_tTitle = Texture("RooseSally.ttf", "^", m_iTitleTextSize, m_cColors->Gold);
		else if (m_fTitleAnimationTimer > 0.5f && m_fTitleAnimationTimer <= 1.0f) m_tTitle = Texture("RooseSally.ttf", "^^", m_iTitleTextSize, m_cColors->Gold);
		else if (m_fTitleAnimationTimer > 1.0f && m_fTitleAnimationTimer <= 1.5f) m_tTitle = Texture("RooseSally.ttf", "^^^", m_iTitleTextSize, m_cColors->Gold);
		else if (m_fTitleAnimationTimer > 1.5f && m_fTitleAnimationTimer <= 2.0f) m_tTitle = Texture("RooseSally.ttf", "^^^^", m_iTitleTextSize, m_cColors->Gold);
		else if (m_fTitleAnimationTimer > 2.0f && m_fTitleAnimationTimer <= 2.5f) m_tTitle = Texture("RooseSally.ttf", "^^^^^", m_iTitleTextSize, m_cColors->Gold);
		else if (m_fTitleAnimationTimer > 2.5f && m_fTitleAnimationTimer <= 3.0f) m_tTitle = Texture("RooseSally.ttf", "^^^^^^", m_iTitleTextSize, m_cColors->Gold);
	}
	else if (m_fTitleAnimationTimer > 3.0f && m_fTitleAnimationTimer <= 4.5f)
	{
		if (m_fTitleAnimationTimer > 3.0f && m_fTitleAnimationTimer <= 3.3f) m_tTitle = Texture("RooseSally.ttf", "^^^^^", m_iTitleTextSize, m_cColors->Gold);
		else if (m_fTitleAnimationTimer > 3.3f && m_fTitleAnimationTimer <= 3.6f) m_tTitle = Texture("RooseSally.ttf", "^^^^", m_iTitleTextSize, m_cColors->Gold);
		else if (m_fTitleAnimationTimer > 3.6f && m_fTitleAnimationTimer <= 3.9f) m_tTitle = Texture("RooseSally.ttf", "^^^", m_iTitleTextSize, m_cColors->Gold);
		else if (m_fTitleAnimationTimer > 3.9f && m_fTitleAnimationTimer <= 4.2f) m_tTitle = Texture("RooseSally.ttf", "^^", m_iTitleTextSize, m_cColors->Gold);
		else if (m_fTitleAnimationTimer > 4.2f && m_fTitleAnimationTimer <= 4.5f) m_tTitle = Texture("RooseSally.ttf", "^", m_iTitleTextSize, m_cColors->Gold);
	}

	//phase 2
	else if (m_fTitleAnimationTimer > 4.5f && m_fTitleAnimationTimer <= 8.0f)
	{
		if (m_fTitleAnimationTimer > 4.5f && m_fTitleAnimationTimer <= 5.0f) m_tTitle = Texture("RooseSally.ttf", " ", m_iTitleTextSize, m_cColors->Purple);
		else if (m_fTitleAnimationTimer > 5.0f && m_fTitleAnimationTimer <= 5.5f) m_tTitle = Texture("RooseSally.ttf", "^", m_iTitleTextSize, m_cColors->Purple);
		else if (m_fTitleAnimationTimer > 5.5f && m_fTitleAnimationTimer <= 6.0f) m_tTitle = Texture("RooseSally.ttf", "^^", m_iTitleTextSize, m_cColors->Purple);
		else if (m_fTitleAnimationTimer > 6.0f && m_fTitleAnimationTimer <= 6.5f) m_tTitle = Texture("RooseSally.ttf", "^^^", m_iTitleTextSize, m_cColors->Purple);
		else if (m_fTitleAnimationTimer > 6.5f && m_fTitleAnimationTimer <= 7.0f) m_tTitle = Texture("RooseSally.ttf", "^^^^", m_iTitleTextSize, m_cColors->Purple);
		else if (m_fTitleAnimationTimer > 7.0f && m_fTitleAnimationTimer <= 7.5f) m_tTitle = Texture("RooseSally.ttf", "^^^^^", m_iTitleTextSize, m_cColors->Purple);
		else if (m_fTitleAnimationTimer > 7.5f && m_fTitleAnimationTimer <= 8.0f) m_tTitle = Texture("RooseSally.ttf", "^^^^^^", m_iTitleTextSize, m_cColors->Purple);

	}
	else if (m_fTitleAnimationTimer > 8.0f && m_fTitleAnimationTimer <= 9.5f)
	{
		if (m_fTitleAnimationTimer > 8.0f && m_fTitleAnimationTimer <= 8.3f) m_tTitle = Texture("RooseSally.ttf", "^^^^^", m_iTitleTextSize, m_cColors->Purple);
		else if (m_fTitleAnimationTimer > 8.3f && m_fTitleAnimationTimer <= 8.6f) m_tTitle = Texture("RooseSally.ttf", "^^^^", m_iTitleTextSize, m_cColors->Purple);
		else if (m_fTitleAnimationTimer > 8.6f && m_fTitleAnimationTimer <= 8.9f) m_tTitle = Texture("RooseSally.ttf", "^^^", m_iTitleTextSize, m_cColors->Purple);
		else if (m_fTitleAnimationTimer > 8.9f && m_fTitleAnimationTimer <= 9.2f) m_tTitle = Texture("RooseSally.ttf", "^^", m_iTitleTextSize, m_cColors->Purple);
		else if (m_fTitleAnimationTimer > 9.2f && m_fTitleAnimationTimer <= 9.5f) m_tTitle = Texture("RooseSally.ttf", "^", m_iTitleTextSize, m_cColors->Purple);

	}

	//phase 3
	else if (m_fTitleAnimationTimer > 9.5f && m_fTitleAnimationTimer <= 13.0f)
	{
		if (m_fTitleAnimationTimer > 9.5f && m_fTitleAnimationTimer <= 10.0f) m_tTitle = Texture("RooseSally.ttf", " ", m_iTitleTextSize, m_cColors->DarkGreen);
		else if (m_fTitleAnimationTimer > 10.0f && m_fTitleAnimationTimer <= 10.5f) m_tTitle = Texture("RooseSally.ttf", "^", m_iTitleTextSize, m_cColors->DarkGreen);
		else if (m_fTitleAnimationTimer > 10.5f && m_fTitleAnimationTimer <= 11.0f) m_tTitle = Texture("RooseSally.ttf", "^^", m_iTitleTextSize, m_cColors->DarkGreen);
		else if (m_fTitleAnimationTimer > 11.0f && m_fTitleAnimationTimer <= 11.5f) m_tTitle = Texture("RooseSally.ttf", "^^^", m_iTitleTextSize, m_cColors->DarkGreen);
		else if (m_fTitleAnimationTimer > 11.5f && m_fTitleAnimationTimer <= 12.0f) m_tTitle = Texture("RooseSally.ttf", "^^^^", m_iTitleTextSize, m_cColors->DarkGreen);
		else if (m_fTitleAnimationTimer > 12.0f && m_fTitleAnimationTimer <= 12.5f) m_tTitle = Texture("RooseSally.ttf", "^^^^^", m_iTitleTextSize, m_cColors->DarkGreen);
		else if (m_fTitleAnimationTimer > 12.5f && m_fTitleAnimationTimer <= 13.0f) m_tTitle = Texture("RooseSally.ttf", "^^^^^^", m_iTitleTextSize, m_cColors->DarkGreen);

	}
	else if (m_fTitleAnimationTimer > 13.0f && m_fTitleAnimationTimer <= 14.5f)
	{
		if (m_fTitleAnimationTimer > 13.0f && m_fTitleAnimationTimer <= 13.3f) m_tTitle = Texture("RooseSally.ttf", "^^^^^", m_iTitleTextSize, m_cColors->DarkGreen);
		else if (m_fTitleAnimationTimer > 13.3f && m_fTitleAnimationTimer <= 13.6f) m_tTitle = Texture("RooseSally.ttf", "^^^^", m_iTitleTextSize, m_cColors->DarkGreen);
		else if (m_fTitleAnimationTimer > 13.6f && m_fTitleAnimationTimer <= 13.9f) m_tTitle = Texture("RooseSally.ttf", "^^^", m_iTitleTextSize, m_cColors->DarkGreen);
		else if (m_fTitleAnimationTimer > 13.9f && m_fTitleAnimationTimer <= 14.2f) m_tTitle = Texture("RooseSally.ttf", "^^", m_iTitleTextSize, m_cColors->DarkGreen);
		else if (m_fTitleAnimationTimer > 14.2f && m_fTitleAnimationTimer <= 14.5f) m_tTitle = Texture("RooseSally.ttf", "^", m_iTitleTextSize, m_cColors->DarkGreen);

	}

#pragma endregion

	if (m_fTitleAnimationTimer > 14.5f && m_fTitleAnimationTimer <= 15.0f) m_tTitle = Texture("RooseSally.ttf", " ", m_iTitleTextSize, m_cColors->DarkGreen);

	//setting position
	if (m_fTitleAnimationTimer < 9.5f) m_tTitle.Pos(m_vTitleAnimationStartPosNormal);
	if (m_fTitleAnimationTimer > 9.5f) m_tTitle.Pos(m_vTitleAnimationStartPosExtended);

	//set flag to reset timer
	if (m_fTitleAnimationTimer > m_fTitleTotalAnimationTime) m_bTitleAnimationFinished = true;
}

void StartScreen::Render()
{
	//render stars
	for (int i = 1; i <= m_iNumberOfStars; i++)
	{
		if (m_iStarsStates[i - 1] < 6) m_tStars[i]->Render(); //dont render if at state 6
	}

	//render menu options
	switch (m_iCurrentMenu)
	{
	case 1:
		for (int i = 1; i <= MainMenu.m_iNumberOfOptions; i++)
		{
			if (MainMenu.m_bMenuOptionsEnabled[i - 1]) //this option is not selected
			{
				MainMenu.m_tMenuOptions[i + MainMenu.m_iNumberOfOptions]->Render();
			}
			else //this open has been selected
			{
				MainMenu.m_tMenuOptions[i]->Render();
			}
		}
		break;

	case 2:
		for (int i = 1; i <= PlayMenu.m_iNumberOfOptions; i++)
		{
			if (PlayMenu.m_bMenuOptionsEnabled[i - 1]) //this option is not selected
			{
				PlayMenu.m_tMenuOptions[i + PlayMenu.m_iNumberOfOptions]->Render();
			}
			else //this open has been selected
			{
				PlayMenu.m_tMenuOptions[i]->Render();
			}
		}
		break;

	case 3:
		for (int i = 1; i <= SettingsMenu.m_iNumberOfOptions; i++)
		{
			if (SettingsMenu.m_bMenuOptionsEnabled[i - 1]) //this option is not selected
			{
				SettingsMenu.m_tMenuOptions[i + SettingsMenu.m_iNumberOfOptions]->Render();
			}
			else //this open has been selected
			{
				SettingsMenu.m_tMenuOptions[i]->Render();
			}
		}
		break;

	case 4:
		for (int i = 1; i <= CreditsMenu.m_iNumberOfOptions; i++)
		{
			if (CreditsMenu.m_bMenuOptionsEnabled[i - 1]) //this option is not selected
			{
				CreditsMenu.m_tMenuOptions[i + CreditsMenu.m_iNumberOfOptions]->Render();
			}
			else //this open has been selected
			{
				CreditsMenu.m_tMenuOptions[i]->Render();
			}
		}
		for (int i = 1; i <= m_iNumOfCreditsLines; i++)
		{
			m_tCreditsScreen[i]->Render();
		}
		break;
	}

	m_tTitle.Render(); //render the title

	m_tSpaceship.Render(); //render the spaceship

	m_tSpaceshipEngine.Render(); //render the spaceship engine
}

int StartScreen::CheckChangedScene()
{
	return m_iSceneToOpen;
}

void StartScreen::InitialiseStars()
{
#pragma region Set Arrays
	m_vStarsPositions[0] = { Vector2(50, 50) };
	m_vStarsPositions[1] = { Vector2(100, 250) };
	m_vStarsPositions[2] = { Vector2(600, 800) };
	m_vStarsPositions[3] = { Vector2(550, 650) };
	m_vStarsPositions[4] = { Vector2(700, 850) };
	m_vStarsPositions[5] = { Vector2(750, 50) };
	m_vStarsPositions[6] = { Vector2(850, 520) };
	m_vStarsPositions[7] = { Vector2(450, 500) };
	m_vStarsPositions[8] = { Vector2(700, 550) };
	m_vStarsPositions[9] = { Vector2(150, 850) };
	m_vStarsPositions[10] = { Vector2(900, 370) };
	m_vStarsPositions[11] = { Vector2(350, 600) };
	m_vStarsPositions[12] = { Vector2(150, 500) };
	m_vStarsPositions[13] = { Vector2(70, 750) };
	m_vStarsPositions[14] = { Vector2(30, 450) };
	m_vStarsPositions[15] = { Vector2(950, 750) };
	m_vStarsPositions[16] = { Vector2(550, 150) };
	m_vStarsPositions[17] = { Vector2(350, 240) };
	m_vStarsPositions[18] = { Vector2(250, 140) };
	m_vStarsPositions[19] = { Vector2(800, 700) };

	m_vStarsSizes[0] = { Vector2(40, 40) };
	m_vStarsSizes[1] = { Vector2(20, 20) };
	m_vStarsSizes[2] = { Vector2(20, 20) };
	m_vStarsSizes[3] = { Vector2(30, 30) };
	m_vStarsSizes[4] = { Vector2(40, 40) };
	m_vStarsSizes[5] = { Vector2(40, 40) };
	m_vStarsSizes[6] = { Vector2(20, 20) };
	m_vStarsSizes[7] = { Vector2(30, 30) };
	m_vStarsSizes[8] = { Vector2(40, 40) };
	m_vStarsSizes[9] = { Vector2(40, 40) };
	m_vStarsSizes[10] = { Vector2(40, 40) };
	m_vStarsSizes[11] = { Vector2(30, 30) };
	m_vStarsSizes[12] = { Vector2(40, 40) };
	m_vStarsSizes[13] = { Vector2(30, 30) };
	m_vStarsSizes[14] = { Vector2(30, 30) };
	m_vStarsSizes[15] = { Vector2(40, 40) };
	m_vStarsSizes[16] = { Vector2(20, 20) };
	m_vStarsSizes[17] = { Vector2(30, 30) };
	m_vStarsSizes[18] = { Vector2(40, 40) };
	m_vStarsSizes[19] = { Vector2(20, 20) };

	m_fStarsRotations[0] = { 0.0f };
	m_fStarsRotations[1] = { 45.0f };
	m_fStarsRotations[2] = { 30.0f };
	m_fStarsRotations[3] = { 80.0f };
	m_fStarsRotations[4] = { 10.0f };
	m_fStarsRotations[5] = { 0.0f };
	m_fStarsRotations[6] = { 20.0f };
	m_fStarsRotations[7] = { 30.0f };
	m_fStarsRotations[8] = { 35.0f };
	m_fStarsRotations[9] = { 85.0f };
	m_fStarsRotations[10] = { 25.0f };
	m_fStarsRotations[11] = { 65.0f };
	m_fStarsRotations[12] = { 75.0f };
	m_fStarsRotations[13] = { 30.0f };
	m_fStarsRotations[14] = { 0.0f };
	m_fStarsRotations[15] = { 20.0f };
	m_fStarsRotations[16] = { 50.0f };
	m_fStarsRotations[17] = { 85.0f };
	m_fStarsRotations[18] = { 15.0f };
	m_fStarsRotations[19] = { 55.0f };

	m_iStarsStates[0] = { 1 };
	m_iStarsStates[1] = { 4 };
	m_iStarsStates[2] = { 3 };
	m_iStarsStates[3] = { 2 };
	m_iStarsStates[4] = { 1 };
	m_iStarsStates[5] = { 5 };
	m_iStarsStates[6] = { 3 };
	m_iStarsStates[7] = { 1 };
	m_iStarsStates[8] = { 4 };
	m_iStarsStates[9] = { 5 };
	m_iStarsStates[10] = { 3 };
	m_iStarsStates[11] = { 2 };
	m_iStarsStates[12] = { 5 };
	m_iStarsStates[13] = { 1 };
	m_iStarsStates[14] = { 2 };
	m_iStarsStates[15] = { 4 };
	m_iStarsStates[16] = { 1 };
	m_iStarsStates[17] = { 3 };
	m_iStarsStates[18] = { 5 };
	m_iStarsStates[19] = { 2 };

#pragma endregion

	m_sStarPath = "Sprites/Special/Background/star1.png";
	for (int i = 0; i < m_iNumberOfStars; i++)
	{
		if (m_iStarsStates[i] == 1) m_sStarPath = "Sprites/Special/Background/star1.png";
		else if (m_iStarsStates[i] == 2) m_sStarPath = "Sprites/Special/Background/star2.png";
		else if (m_iStarsStates[i] == 3) m_sStarPath = "Sprites/Special/Background/star3.png";
		else if (m_iStarsStates[i] == 4) m_sStarPath = "Sprites/Special/Background/star4.png";
		else if (m_iStarsStates[i] == 5) m_sStarPath = "Sprites/Special/Background/star5.png";

		m_tStars[i + 1] = new Texture(m_sStarPath, m_vStarsPositions[i], m_vStarsSizes[i].x, m_vStarsSizes[i].y, m_fStarsRotations[i]);
	}

	m_fStarsTotalAnimationTime = 0.1f;
}

void StartScreen::InitialiseMenu()
{
	//main menu
	//setting button count and states
	MainMenu.m_iNumberOfOptions = 4;
	MainMenu.m_bMenuOptionsEnabled = { {1, true,}, {2, false,}, {3, false,}, {4, false,} };

	//set the MenuOptions map values
	MainMenu.m_tMenuOptions = {	//normal
					  {1, new Texture("RooseSally.ttf", "Play", m_iTextSize, m_cColors->White),},
					  {2, new Texture("RooseSally.ttf", "Settings", m_iTextSize, m_cColors->White),},
					  {3, new Texture("RooseSally.ttf", "Credits", m_iTextSize, m_cColors->White),},
					  {4, new Texture("RooseSally.ttf", "Quit Game", m_iTextSize, m_cColors->White),},
					   //selected
					  {5, new Texture("RooseSally.ttf", "> Play", m_iTextSelectedSize, m_cColors->Cream),},
					  {6, new Texture("RooseSally.ttf", "> Settings", m_iTextSelectedSize, m_cColors->Cream),},
					  {7, new Texture("RooseSally.ttf", "> Credits", m_iTextSelectedSize, m_cColors->Cream),},
					  {8, new Texture("RooseSally.ttf", "> Quit Game", m_iTextSelectedSize, m_cColors->Cream),}
	};

	//set the position of each MenuOptions map values
	MainMenu.m_tMenuOptions[1]->Pos(Vector2(Graphics::SCREEN_WIDTH / 7 + (0 * m_iTextIndent),
		(7 * Graphics::SCREEN_HEIGHT) / 10 - MainMenu.m_tMenuOptions[1]->m_iHeight + (0 * m_iLineGap)));

	MainMenu.m_tMenuOptions[2]->Pos(Vector2(Graphics::SCREEN_WIDTH / 7 + (1 * m_iTextIndent),
		(7 * Graphics::SCREEN_HEIGHT) / 10 - MainMenu.m_tMenuOptions[2]->m_iHeight + (1 * m_iLineGap)));

	MainMenu.m_tMenuOptions[3]->Pos(Vector2(Graphics::SCREEN_WIDTH / 7 + (2 * m_iTextIndent),
		(7 * Graphics::SCREEN_HEIGHT) / 10 - MainMenu.m_tMenuOptions[3]->m_iHeight + (2 * m_iLineGap)));

	MainMenu.m_tMenuOptions[4]->Pos(Vector2(Graphics::SCREEN_WIDTH / 7 + (3 * m_iTextIndent),
		(7 * Graphics::SCREEN_HEIGHT) / 10 - MainMenu.m_tMenuOptions[4]->m_iHeight + (3 * m_iLineGap)));

	MainMenu.m_tMenuOptions[5]->Pos(Vector2(Graphics::SCREEN_WIDTH / 7 + (0 * m_iTextIndent) + (MainMenu.m_tMenuOptions[1]->m_iWidth - MainMenu.m_tMenuOptions[5]->m_iWidth),
		(7 * Graphics::SCREEN_HEIGHT) / 10 - MainMenu.m_tMenuOptions[5]->m_iHeight + (0 * m_iLineGap)));

	MainMenu.m_tMenuOptions[6]->Pos(Vector2(Graphics::SCREEN_WIDTH / 7 + (1 * m_iTextIndent) + (MainMenu.m_tMenuOptions[2]->m_iWidth - MainMenu.m_tMenuOptions[6]->m_iWidth),
		(7 * Graphics::SCREEN_HEIGHT) / 10 - MainMenu.m_tMenuOptions[6]->m_iHeight + (1 * m_iLineGap)));

	MainMenu.m_tMenuOptions[7]->Pos(Vector2(Graphics::SCREEN_WIDTH / 7 + (2 * m_iTextIndent) + (MainMenu.m_tMenuOptions[3]->m_iWidth - MainMenu.m_tMenuOptions[7]->m_iWidth),
		(7 * Graphics::SCREEN_HEIGHT) / 10 - MainMenu.m_tMenuOptions[7]->m_iHeight + (2 * m_iLineGap)));

	MainMenu.m_tMenuOptions[8]->Pos(Vector2(Graphics::SCREEN_WIDTH / 7 + (3 * m_iTextIndent) + (MainMenu.m_tMenuOptions[4]->m_iWidth - MainMenu.m_tMenuOptions[8]->m_iWidth),
		(7 * Graphics::SCREEN_HEIGHT) / 10 - MainMenu.m_tMenuOptions[8]->m_iHeight + (3 * m_iLineGap)));


	//play menu
	//setting button count and states
	PlayMenu.m_iNumberOfOptions = 3;
	PlayMenu.m_bMenuOptionsEnabled = { {1, true,}, {2, false,}, {3, false,} };

	//set the MenuOptions map values
	PlayMenu.m_tMenuOptions = {	//normal
				  {1, new Texture("RooseSally.ttf", "Stage 1", m_iTextSize, m_cColors->White),},
				  {2, new Texture("RooseSally.ttf", "Stage 2", m_iTextSize, m_cColors->Grey),},
				  {3, new Texture("RooseSally.ttf", "Back", m_iTextSize, m_cColors->White),},
				  //selected
				  {4, new Texture("RooseSally.ttf", "> Stage 1", m_iTextSelectedSize, m_cColors->Cream),},
				  {5, new Texture("RooseSally.ttf", "> Stage 2", m_iTextSelectedSize, m_cColors->Grey),},
				  {6, new Texture("RooseSally.ttf", "> Back", m_iTextSelectedSize, m_cColors->Cream),},
	};

	//set the position of each MenuOptions map values
	PlayMenu.m_tMenuOptions[1]->Pos(Vector2(Graphics::SCREEN_WIDTH / 7 + (0 * m_iTextIndent),
		(7 * Graphics::SCREEN_HEIGHT) / 10 - PlayMenu.m_tMenuOptions[1]->m_iHeight + (0 * m_iLineGap)));

	PlayMenu.m_tMenuOptions[2]->Pos(Vector2(Graphics::SCREEN_WIDTH / 7 + (1 * m_iTextIndent),
		(7 * Graphics::SCREEN_HEIGHT) / 10 - PlayMenu.m_tMenuOptions[2]->m_iHeight + (1 * m_iLineGap)));

	PlayMenu.m_tMenuOptions[3]->Pos(Vector2(Graphics::SCREEN_WIDTH / 7 + (3 * m_iTextIndent),
		(7 * Graphics::SCREEN_HEIGHT) / 10 - PlayMenu.m_tMenuOptions[3]->m_iHeight + (3 * m_iLineGap)));

	PlayMenu.m_tMenuOptions[4]->Pos(Vector2(Graphics::SCREEN_WIDTH / 7 + (0 * m_iTextIndent) + (PlayMenu.m_tMenuOptions[1]->m_iWidth - PlayMenu.m_tMenuOptions[4]->m_iWidth),
		(7 * Graphics::SCREEN_HEIGHT) / 10 - PlayMenu.m_tMenuOptions[4]->m_iHeight + (0 * m_iLineGap)));

	PlayMenu.m_tMenuOptions[5]->Pos(Vector2(Graphics::SCREEN_WIDTH / 7 + (1 * m_iTextIndent) + (PlayMenu.m_tMenuOptions[2]->m_iWidth - PlayMenu.m_tMenuOptions[5]->m_iWidth),
		(7 * Graphics::SCREEN_HEIGHT) / 10 - PlayMenu.m_tMenuOptions[5]->m_iHeight + (1 * m_iLineGap)));

	PlayMenu.m_tMenuOptions[6]->Pos(Vector2(Graphics::SCREEN_WIDTH / 7 + (3 * m_iTextIndent) + (PlayMenu.m_tMenuOptions[3]->m_iWidth - PlayMenu.m_tMenuOptions[6]->m_iWidth),
		(7 * Graphics::SCREEN_HEIGHT) / 10 - PlayMenu.m_tMenuOptions[6]->m_iHeight + (3 * m_iLineGap)));


	//settings menu
	//setting button count and states
	SettingsMenu.m_iNumberOfOptions = 4;
	SettingsMenu.m_bMenuOptionsEnabled = { {1, true,}, {2, false,}, {3, false,}, {4, false,} };

	//set the MenuOptions map values
	SettingsMenu.m_tMenuOptions = {	//normal
					  {1, new Texture("RooseSally.ttf", "Music Off", m_iTextSize / 2, m_cColors->White),},
					  {2, new Texture("RooseSally.ttf", "Music 50 %", m_iTextSize / 2, m_cColors->White),},
					  {3, new Texture("RooseSally.ttf", "Music 100 %", m_iTextSize / 2, m_cColors->White),},
					  {4, new Texture("RooseSally.ttf", "Back", m_iTextSize, m_cColors->White),},
					  //selected
					  {5, new Texture("RooseSally.ttf", "> Music Off", m_iTextSelectedSize / 2, m_cColors->Cream),},
					  {6, new Texture("RooseSally.ttf", "> Music 50 %", m_iTextSelectedSize / 2, m_cColors->Cream),},
					  {7, new Texture("RooseSally.ttf", "> Music 100 %", m_iTextSelectedSize / 2, m_cColors->Cream),},
					  {8, new Texture("RooseSally.ttf", "> Back", m_iTextSelectedSize, m_cColors->Cream),}
	};

	//set the position of each MenuOptions map values
	SettingsMenu.m_tMenuOptions[1]->Pos(Vector2(Graphics::SCREEN_WIDTH / 7 + (0 * m_iTextIndent),
		(7 * Graphics::SCREEN_HEIGHT) / 10 - SettingsMenu.m_tMenuOptions[1]->m_iHeight + (0 * m_iLineGap)));

	SettingsMenu.m_tMenuOptions[2]->Pos(Vector2(Graphics::SCREEN_WIDTH / 7 + (0 * m_iTextIndent),
		(7 * Graphics::SCREEN_HEIGHT) / 10 - SettingsMenu.m_tMenuOptions[2]->m_iHeight + (1 * m_iLineGap)));

	SettingsMenu.m_tMenuOptions[3]->Pos(Vector2(Graphics::SCREEN_WIDTH / 7 + (0 * m_iTextIndent),
		(7 * Graphics::SCREEN_HEIGHT) / 10 - SettingsMenu.m_tMenuOptions[3]->m_iHeight + (2 * m_iLineGap)));

	SettingsMenu.m_tMenuOptions[4]->Pos(Vector2(Graphics::SCREEN_WIDTH / 7 + (3 * m_iTextIndent),
		(7 * Graphics::SCREEN_HEIGHT) / 10 - SettingsMenu.m_tMenuOptions[4]->m_iHeight + (3 * m_iLineGap)));

	SettingsMenu.m_tMenuOptions[5]->Pos(Vector2(Graphics::SCREEN_WIDTH / 7 + (0 * m_iTextIndent) + (SettingsMenu.m_tMenuOptions[1]->m_iWidth - SettingsMenu.m_tMenuOptions[5]->m_iWidth),
		(7 * Graphics::SCREEN_HEIGHT) / 10 - SettingsMenu.m_tMenuOptions[5]->m_iHeight + (0 * m_iLineGap)));

	SettingsMenu.m_tMenuOptions[6]->Pos(Vector2(Graphics::SCREEN_WIDTH / 7 + (0 * m_iTextIndent) + (SettingsMenu.m_tMenuOptions[2]->m_iWidth - SettingsMenu.m_tMenuOptions[6]->m_iWidth),
		(7 * Graphics::SCREEN_HEIGHT) / 10 - SettingsMenu.m_tMenuOptions[6]->m_iHeight + (1 * m_iLineGap)));

	SettingsMenu.m_tMenuOptions[7]->Pos(Vector2(Graphics::SCREEN_WIDTH / 7 + (0 * m_iTextIndent) + (SettingsMenu.m_tMenuOptions[3]->m_iWidth - SettingsMenu.m_tMenuOptions[7]->m_iWidth),
		(7 * Graphics::SCREEN_HEIGHT) / 10 - SettingsMenu.m_tMenuOptions[7]->m_iHeight + (2 * m_iLineGap)));

	SettingsMenu.m_tMenuOptions[8]->Pos(Vector2(Graphics::SCREEN_WIDTH / 7 + (3 * m_iTextIndent) + (SettingsMenu.m_tMenuOptions[4]->m_iWidth - SettingsMenu.m_tMenuOptions[8]->m_iWidth),
		(7 * Graphics::SCREEN_HEIGHT) / 10 - SettingsMenu.m_tMenuOptions[8]->m_iHeight + (3 * m_iLineGap)));


	//credits menu
	//setting button count and states
	CreditsMenu.m_iNumberOfOptions = 1;
	CreditsMenu.m_bMenuOptionsEnabled = { {1, true,} };

	//set the MenuOptions map values
	CreditsMenu.m_tMenuOptions = {	//normal
					  {1, new Texture("RooseSally.ttf", "Back", m_iTextSize, m_cColors->White),},
					  //selected
					  {2, new Texture("RooseSally.ttf", "> Back", m_iTextSelectedSize, m_cColors->Cream),}
	};

	//set the position of each MenuOptions map values
	CreditsMenu.m_tMenuOptions[1]->Pos(Vector2(Graphics::SCREEN_WIDTH / 2 - (CreditsMenu.m_tMenuOptions[1]->m_iWidth / 2),
		(7 * Graphics::SCREEN_HEIGHT) / 10 - CreditsMenu.m_tMenuOptions[1]->m_iHeight + (3 * m_iLineGap)));

	CreditsMenu.m_tMenuOptions[2]->Pos(Vector2(Graphics::SCREEN_WIDTH / 2 - (CreditsMenu.m_tMenuOptions[1]->m_iWidth / 2 - CreditsMenu.m_tMenuOptions[2]->m_iWidth),
		(7 * Graphics::SCREEN_HEIGHT) / 10 - CreditsMenu.m_tMenuOptions[2]->m_iHeight + (3 * m_iLineGap)));


	m_tCreditsScreen = {
		{1, new Texture("RooseSally.ttf", "Audio :", m_iCreditsTextSize, m_cColors->White),},
		{2, new Texture("RooseSally.ttf", " ", m_iCreditsTextSize, m_cColors->White),},
		{3, new Texture("RooseSally.ttf", "'Puzzle Dreams'", m_iCreditsTextSize, m_cColors->White),},
		{4, new Texture("RooseSally.ttf", " ", m_iCreditsTextSize, m_cColors->White),},
		{5, new Texture("RooseSally.ttf", "By Eric Matyas", m_iCreditsTextSize, m_cColors->White),},
		{6, new Texture("RooseSally.ttf", "www.soundimage.org", m_iCreditsTextSize, m_cColors->White),},
		{7, new Texture("RooseSally.ttf", " ", m_iCreditsTextSize, m_cColors->White),},
		{8, new Texture("RooseSally.ttf", "'Child's Nightmare'", m_iCreditsTextSize, m_cColors->White),},
		{9, new Texture("RooseSally.ttf", "'Interplanetary Odyssey'", m_iCreditsTextSize, m_cColors->White),},
		{10, new Texture("RooseSally.ttf", "'Markalo goes to the disco'", m_iCreditsTextSize, m_cColors->White),},
		{11, new Texture("RooseSally.ttf", "'Heroic Intrusion'", m_iCreditsTextSize, m_cColors->White),},
		{12, new Texture("RooseSally.ttf", " ", m_iCreditsTextSize, m_cColors->White),},
		{13, new Texture("RooseSally.ttf", "By Patrick de Arteaga", m_iCreditsTextSize, m_cColors->White),},
		{14, new Texture("RooseSally.ttf", "https://patrickdearteaga.com", m_iCreditsTextSize, m_cColors->White),},
	};

	m_tCreditsScreen[1]->Pos(Vector2(Graphics::SCREEN_WIDTH / 3 - (m_tCreditsScreen[1]->m_iWidth / 2),
		(3 * Graphics::SCREEN_HEIGHT) / 5 - m_tCreditsScreen[1]->m_iHeight + (-1 * (m_iLineGap / 3))));

	m_tCreditsScreen[2]->Pos(Vector2(Graphics::SCREEN_WIDTH / 3 - (m_tCreditsScreen[2]->m_iWidth / 2),
		(3 * Graphics::SCREEN_HEIGHT) / 5 - m_tCreditsScreen[2]->m_iHeight + (0 * (m_iLineGap / 3))));

	m_tCreditsScreen[3]->Pos(Vector2(Graphics::SCREEN_WIDTH / 3 - (m_tCreditsScreen[3]->m_iWidth / 2),
		(3 * Graphics::SCREEN_HEIGHT) / 5 - m_tCreditsScreen[3]->m_iHeight + (1 * (m_iLineGap / 3))));

	m_tCreditsScreen[4]->Pos(Vector2(Graphics::SCREEN_WIDTH / 3 - (m_tCreditsScreen[4]->m_iWidth / 2),
		(3 * Graphics::SCREEN_HEIGHT) / 5 - m_tCreditsScreen[4]->m_iHeight + (2 * (m_iLineGap / 3))));

	m_tCreditsScreen[5]->Pos(Vector2(Graphics::SCREEN_WIDTH / 3 - (m_tCreditsScreen[5]->m_iWidth / 2),
		(3 * Graphics::SCREEN_HEIGHT) / 5 - m_tCreditsScreen[5]->m_iHeight + (3 * (m_iLineGap / 3))));

	m_tCreditsScreen[6]->Pos(Vector2(Graphics::SCREEN_WIDTH / 3 - (m_tCreditsScreen[6]->m_iWidth / 2),
		(3 * Graphics::SCREEN_HEIGHT) / 5 - m_tCreditsScreen[6]->m_iHeight + (4 * (m_iLineGap / 3))));

	m_tCreditsScreen[7]->Pos(Vector2(Graphics::SCREEN_WIDTH / 3 - (m_tCreditsScreen[7]->m_iWidth / 2),
		(3 * Graphics::SCREEN_HEIGHT) / 5 - m_tCreditsScreen[7]->m_iHeight + (5 * (m_iLineGap / 3))));

	m_tCreditsScreen[8]->Pos(Vector2(Graphics::SCREEN_WIDTH / 3 - (m_tCreditsScreen[8]->m_iWidth / 2),
		(3 * Graphics::SCREEN_HEIGHT) / 5 - m_tCreditsScreen[8]->m_iHeight + (6 * (m_iLineGap / 3))));

	m_tCreditsScreen[9]->Pos(Vector2(Graphics::SCREEN_WIDTH / 3 - (m_tCreditsScreen[9]->m_iWidth / 2),
		(3 * Graphics::SCREEN_HEIGHT) / 5 - m_tCreditsScreen[9]->m_iHeight + (7 * (m_iLineGap / 3))));

	m_tCreditsScreen[10]->Pos(Vector2(Graphics::SCREEN_WIDTH / 3 - (m_tCreditsScreen[10]->m_iWidth / 2),
		(3 * Graphics::SCREEN_HEIGHT) / 5 - m_tCreditsScreen[10]->m_iHeight + (8 * (m_iLineGap / 3))));

	m_tCreditsScreen[11]->Pos(Vector2(Graphics::SCREEN_WIDTH / 3 - (m_tCreditsScreen[11]->m_iWidth / 2),
		(3 * Graphics::SCREEN_HEIGHT) / 5 - m_tCreditsScreen[11]->m_iHeight + (9 * (m_iLineGap / 3))));

	m_tCreditsScreen[12]->Pos(Vector2(Graphics::SCREEN_WIDTH / 3 - (m_tCreditsScreen[12]->m_iWidth / 2),
		(3 * Graphics::SCREEN_HEIGHT) / 5 - m_tCreditsScreen[12]->m_iHeight + (10 * (m_iLineGap / 3))));

	m_tCreditsScreen[13]->Pos(Vector2(Graphics::SCREEN_WIDTH / 3 - (m_tCreditsScreen[13]->m_iWidth / 2),
		(3 * Graphics::SCREEN_HEIGHT) / 5 - m_tCreditsScreen[13]->m_iHeight + (11 * (m_iLineGap / 3))));

	m_tCreditsScreen[14]->Pos(Vector2(Graphics::SCREEN_WIDTH / 3 - (m_tCreditsScreen[14]->m_iWidth / 2),
		(3 * Graphics::SCREEN_HEIGHT) / 5 - m_tCreditsScreen[14]->m_iHeight + (12 * (m_iLineGap / 3))));
}

StartScreen::StartScreen()
{
	//instance of m_cColors
	m_cColors = Colors::Instance();
	//instance of m_tTimer
	m_tTimer = Timer::Instance();
	//instance of input manager
	m_iInputManager = InputManager::Instance();
	//instance of audio manager
	m_aAudioManager = AudioManager::Instance();

	m_aAudioManager->PlayMusic("menutrack.wav", -1);
	m_aAudioManager->SetVolume(75.0f);


	InitialiseMenu();
	InitialiseStars();


	//setting title animation variables
	m_vTitleAnimationStartPosNormal = Vector2(Graphics::SCREEN_WIDTH / 20, Graphics::SCREEN_HEIGHT / 15);
	m_vTitleAnimationStartPosExtended = Vector2(Graphics::SCREEN_WIDTH / 2, Graphics::SCREEN_HEIGHT / 15);

	//3 seconds draw left to right, 1.5 second clear right to left, 0.5 second gap
	//3 seconds draw left to right, 1.5 second clear right to left, 0.5 second gap
	//3 seconds draw left to right at extended pos, 1.5 second clear right to left, 0.5 second gap
	m_fTitleTotalAnimationTime = 15.0f;
	m_fTitleAnimationTimer = 0.0f;

	m_bTitleAnimationFinished = false;


	//setting spaceship variables
	m_vSpaceshipSize = Vector2(800, 320);
	m_vSpaceshipPos = Vector2((9 * Graphics::SCREEN_WIDTH) / 20 - m_vSpaceshipSize.x / 2, (2 * Graphics::SCREEN_HEIGHT) / 9);

	//setting spaceship animation variables
	m_vSpaceshipEngineSize = Vector2(107, 64);
	m_vSpaceshipEngineAnimationStartPos = Vector2(m_vSpaceshipPos.x + m_vSpaceshipSize.x, m_vSpaceshipPos.y);

	m_fSpaceshipEngineTotalAnimationTime = 0.4f;
	m_fSpaceshipEngineAnimationTimer = 0.0f;

	m_bSpaceshipAnimationFinished = false;
}

StartScreen::~StartScreen()
{
	Colors::Release();
	m_cColors = NULL;

	Timer::Release();
	m_tTimer = NULL;

	InputManager::Release();
	m_iInputManager = NULL;

	for (int i = 1; i <= MainMenu.m_iNumberOfOptions; i++)
	{
		if (MainMenu.m_tMenuOptions[i] != NULL)
		{
			delete MainMenu.m_tMenuOptions[i];
			MainMenu.m_tMenuOptions[i] = NULL;
		}
	}

	for (int i = 1; i <= PlayMenu.m_iNumberOfOptions; i++)
	{
		if (PlayMenu.m_tMenuOptions[i] != NULL)
		{
			delete PlayMenu.m_tMenuOptions[i];
			PlayMenu.m_tMenuOptions[i] = NULL;
		}
	}

	for (int i = 1; i <= SettingsMenu.m_iNumberOfOptions; i++)
	{
		if (SettingsMenu.m_tMenuOptions[i] != NULL)
		{
			delete SettingsMenu.m_tMenuOptions[i];
			SettingsMenu.m_tMenuOptions[i] = NULL;
		}
	}

	for (int i = 1; i <= CreditsMenu.m_iNumberOfOptions; i++)
	{
		if (CreditsMenu.m_tMenuOptions[i] != NULL)
		{
			delete CreditsMenu.m_tMenuOptions[i];
			CreditsMenu.m_tMenuOptions[i] = NULL;
		}
	}
}