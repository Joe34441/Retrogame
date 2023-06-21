#include "PlayScreen.h"


void PlayScreen::Update()
{
	m_iSceneToOpen = 1;

	GetInputs(m_vPlayerTranslationLeft, m_vPlayerTranslationRight);

	if (!m_bStage1TimeOver)
	{
		UpdateTimer();

		if (!PlayerAnimationFlags.dead)
		{
			CheckCollisions();
			ApplyInputs();
			UpdateSpecialObjects();
		}
		else
		{
			ApplyPlayerDeath();
		}

		AnimatePlayer();
	}
	else
	{
		GameOver();
	}

}

void PlayScreen::Render()
{
	m_tBackgroundTexture->Render();

	m_tLevelTitleTexture->Render();

	m_tTimerTexture1->Render();
	m_tTimerTexture2->Render();
	m_tTimerTexture3->Render();

	for (int i = 0; i < Levels::m_iLevelDepth; ++i)
	{
		for (int j = 0; j < Levels::m_iLevelWidth; ++j)
		{
			if (m_tLevelLayoutTextures[i][j] != NULL) m_tLevelLayoutTextures[i][j]->Render();
		}
	}

	for (int i = 0; i < m_iMaxNumOfSpeicalObjects; i++)
	{
		if (m_bSpecialObjectsEnabled[i]) m_tSpecialObjectsTextures[i]->Render();
	}

	m_tPlayerTexture->Render();

	if (m_bGameOver) m_tGameOverTexture->Render();
}

int PlayScreen::CheckChangedScene()
{
	return m_iSceneToOpen;
}

void PlayScreen::CheckCollisions()
{
	m_iCollisionState = 0;
	m_iCollisionState = m_cCollisionManager->CheckCollision(m_sLevel, m_tPlayerTexture->m_vPos, m_vPlayerSize, m_vPlaySpace, m_iStandardTextureSize, 1);

	if (m_iCollisionState == 1)
	{
		if (m_cCollisionManager->m_bDead)
		{
			PlayerAnimationFlags.dead = true;
		}
		else
		{
			PlayerAnimationFlags.dead = false;
		}
	}
	else
	{
		PlayerAnimationFlags.dead = false;
	}

	m_cCollisionManager->CheckCollision(m_sLevel, m_tPlayerTexture->m_vPos, m_vPlayerSize, m_vPlaySpace, m_iStandardTextureSize, 2);

	m_cCollisionManager->SetLevelChangers(m_lLevelChanger->m_vLevelChangersNext[m_iCurrentLevelIndex], m_lLevelChanger->m_vLevelChangersExit[m_iCurrentLevelIndex],
										  m_lLevelChanger->m_bVerticalLevelChanger[m_iCurrentLevelIndex]);

	m_iCollisionState = m_cCollisionManager->CheckCollision(m_sLevel, m_tPlayerTexture->m_vPos, m_vPlayerSize, m_vPlaySpace, m_iStandardTextureSize, 3);

	if (m_iCollisionState == 3)
	{
		ChangeNextLevel();
	}
	else
	{
		m_cCollisionManager->SetLevelChangers(m_lLevelChanger->m_vLevelChangersNext[m_iCurrentLevelIndex], m_lLevelChanger->m_vLevelChangersExit[m_iCurrentLevelIndex - 1],
											  m_lLevelChanger->m_bVerticalLevelChanger[m_iCurrentLevelIndex - 1]);

		m_iCollisionState = m_cCollisionManager->CheckCollision(m_sLevel, m_tPlayerTexture->m_vPos, m_vPlayerSize, m_vPlaySpace, m_iStandardTextureSize, 3);
	}

	if (m_iCollisionState == 4) ChangeBackLevel();

	int m_iCurrentLevel = std::stoi(m_sLevel.substr(2, 2));
	for (int i = 0; i < 6; i++)
	{
		if (m_lLevelChanger->m_iLevelsWithCheckpoint[i] == m_iCurrentLevel - 1)
		{
			if (m_lLevelChanger->GetActiveCheckpoint() != i)
			{
				m_cCollisionManager->SetSpecialObjectParams(m_lLevelChanger->m_vCheckpointLocations[i],
															Vector2(m_tSpecialObjectsTextures[0]->m_iHeight, m_tSpecialObjectsTextures[0]->m_iWidth),
															m_tPlayerTexture->m_vPos, Vector2(m_tPlayerTexture->m_iHeight, m_tPlayerTexture->m_iWidth));
				m_iCollisionState = m_cCollisionManager->CheckCollision(m_sLevel, m_tPlayerTexture->m_vPos, m_vPlayerSize, m_vPlaySpace, m_iStandardTextureSize, 4);

				if (m_iCollisionState == 5)
				{
					m_lLevelChanger->SetActiveCheckpoint(i);
					m_iActiveCheckpointIndex = m_iCurrentLevelIndex;
				}
			}
		}
	}

}

void PlayScreen::ApplyPlayerDeath()
{
	if (!m_bPlayerDeathFinished)
	{
		m_fPlayerDeathTimer += m_tTimer->DeltaTime();
		if (m_fPlayerDeathTimer >= m_fPlayerDeathTime) m_bPlayerDeathFinished = true;
	}
	else
	{
		m_fPlayerDeathTimer = 0.0f;
		m_bPlayerDeathFinished = false;
	
		m_iCurrentLevelIndex = m_iActiveCheckpointIndex;


		m_tPlayerTexture->m_vPos = m_lLevelChanger->m_vCheckPointWorldLocations[m_lLevelChanger->GetActiveCheckpoint()];

		m_sLevel = m_sLevel.substr(0, 2) + std::to_string(m_lLevelChanger->m_iStageRoute[m_iCurrentLevelIndex]);
		SetTextureMap(m_sLevel);

		m_tLevelTitleTexture = new Texture("RooseSally.ttf", m_sLevel, m_iTitleTextSize, m_cColors->White);
		m_tLevelTitleTexture->Pos(Vector2(Graphics::SCREEN_WIDTH / 2 - static_cast<float>(m_tLevelTitleTexture->m_iWidth) / 2,
			Graphics::SCREEN_HEIGHT / 2 - m_vPlaySpace.y / 2 - static_cast<float>(m_tLevelTitleTexture->m_iHeight)));

		m_bFalling = true;
		PlayerAnimationFlags.dead = false;
		PlayerAnimationFlags.falling = true;
		PlayerAnimationFlags.jumping = false;
	}
}

void PlayScreen::GameOver()
{
	if (!m_bGameOver)
	{
		m_bGameOver = true;
		m_tGameOverTexture;

		m_tGameOverTexture = new Texture("RooseSally.ttf", "GAME OVER", 200, m_cColors->DarkRed);
		m_tGameOverTexture->Pos(Vector2(Graphics::SCREEN_WIDTH / 2 - static_cast<float>(m_tGameOverTexture->m_iWidth) / 2,
			Graphics::SCREEN_HEIGHT / 2 - static_cast<float>(m_tGameOverTexture->m_iHeight) / 2));
	}
	else
	{
		m_fGameOverScreenTimer += m_tTimer->DeltaTime();
		if (m_fGameOverScreenTimer > m_fGameOverScreenTotalTime)
		{
			m_iSceneToOpen = 0;
			m_aAudioManager->PauseMusic();
			m_aAudioManager->PlayMusic("menutrack.wav", 1);
			m_aAudioManager->SetVolume(75.0f);

			RestartScene();
			m_iCurrentLevelIndex = 0;
		}
	}
}

void PlayScreen::UpdateTimer()
{
	m_fStage1Timer += m_tTimer->DeltaTime();
	if (m_fStage1Timer > m_fStage1TotalTime) m_bStage1TimeOver = true;
	
	//for the timer, have 3 different textures for each part (xyz = 1: 5 9) so that it
	//doesn't render a new text 191 times for each combination of 3:20 --> 3:19 etc to 0:00
	//and instead renders 23 new variations

	static bool playingTrack2 = false;
	if (m_fStage1TotalTime - m_fStage1Timer <= 110 && !playingTrack2)
	{
		m_aAudioManager->PlayMusic("track1-2.wav", 0);
		playingTrack2 = true;
	}

	if (m_fStage1TotalTime - m_fStage1Timer > 180)
	{
		m_tTimerTexture1 = new Texture("RooseSally.ttf", "3:", m_iTimerTextSize, m_cColors->White);
		m_tTimerTexture1->Pos(Vector2(Graphics::SCREEN_WIDTH / 2 + m_vPlaySpace.x / 4 - static_cast<float>(m_tTimerTexture1->m_iWidth) / 2,
			Graphics::SCREEN_HEIGHT / 2 - m_vPlaySpace.y / 2 - static_cast<float>(m_tTimerTexture1->m_iHeight)));
		
		int a = m_fStage1TotalTime - m_fStage1Timer - 180;
		std::string b = std::to_string(a);
		std::string c = b.substr(0, 1);
		std::string d = b.substr(1, 1);
		if (c == "") c = "0";
		if (d == "") d = "0";
		if (a < 10)
		{
			d = c;
			c = "0";
		}

		m_tTimerTexture2 = new Texture("RooseSally.ttf", c, m_iTimerTextSize, m_cColors->White);
		m_tTimerTexture2->Pos(Vector2(Graphics::SCREEN_WIDTH / 2 + m_vPlaySpace.x / 4 + static_cast<float>(m_tTimerTexture1->m_iWidth - m_tTimerTexture2->m_iWidth / 2),
			Graphics::SCREEN_HEIGHT / 2 - m_vPlaySpace.y / 2 - m_tTimerTexture2->m_iHeight));

		m_tTimerTexture3 = new Texture("RooseSally.ttf", d, m_iTimerTextSize, m_cColors->White);
		m_tTimerTexture3->Pos(Vector2(Graphics::SCREEN_WIDTH / 2 + m_vPlaySpace.x / 4 + static_cast<float>(m_tTimerTexture1->m_iWidth + m_tTimerTexture2->m_iWidth),
			Graphics::SCREEN_HEIGHT / 2 - m_vPlaySpace.y / 2 - m_tTimerTexture3->m_iHeight));
	}
	else if (m_fStage1TotalTime - m_fStage1Timer > 120)
	{
		m_tTimerTexture1 = new Texture("RooseSally.ttf", "2:", m_iTimerTextSize, m_cColors->White);
		m_tTimerTexture1->Pos(Vector2(Graphics::SCREEN_WIDTH / 2 + m_vPlaySpace.x / 4 - static_cast<float>(m_tTimerTexture1->m_iWidth) / 2,
			Graphics::SCREEN_HEIGHT / 2 - m_vPlaySpace.y / 2 - static_cast<float>(m_tTimerTexture1->m_iHeight)));

		int a = m_fStage1TotalTime - m_fStage1Timer - 120;
		std::string b = std::to_string(a);
		std::string c = b.substr(0, 1);
		std::string d = b.substr(1, 1);
		if (c == "") c = "0";
		if (d == "") d = "0";
		if (a < 10)
		{
			d = c;
			c = "0";
		}

		m_tTimerTexture2 = new Texture("RooseSally.ttf", c, m_iTimerTextSize, m_cColors->White);
		m_tTimerTexture2->Pos(Vector2(Graphics::SCREEN_WIDTH / 2 + m_vPlaySpace.x / 4 + static_cast<float>(m_tTimerTexture1->m_iWidth - m_tTimerTexture2->m_iWidth / 2),
			Graphics::SCREEN_HEIGHT / 2 - m_vPlaySpace.y / 2 - m_tTimerTexture2->m_iHeight));

		m_tTimerTexture3 = new Texture("RooseSally.ttf", d, m_iTimerTextSize, m_cColors->White);
		m_tTimerTexture3->Pos(Vector2(Graphics::SCREEN_WIDTH / 2 + m_vPlaySpace.x / 4 + static_cast<float>(m_tTimerTexture1->m_iWidth + m_tTimerTexture2->m_iWidth),
			Graphics::SCREEN_HEIGHT / 2 - m_vPlaySpace.y / 2 - m_tTimerTexture3->m_iHeight));
	}
	else if (m_fStage1TotalTime - m_fStage1Timer > 60)
	{
		m_tTimerTexture1 = new Texture("RooseSally.ttf", "1:", m_iTimerTextSize, m_cColors->White);
		m_tTimerTexture1->Pos(Vector2(Graphics::SCREEN_WIDTH / 2 + m_vPlaySpace.x / 4 - static_cast<float>(m_tTimerTexture1->m_iWidth) / 2,
			Graphics::SCREEN_HEIGHT / 2 - m_vPlaySpace.y / 2 - static_cast<float>(m_tTimerTexture1->m_iHeight)));

		int a = m_fStage1TotalTime - m_fStage1Timer - 60;
		std::string b = std::to_string(a);
		std::string c = b.substr(0, 1);
		std::string d = b.substr(1, 1);
		if (c == "") c = "0";
		if (d == "") d = "0";
		if (a < 10)
		{
			d = c;
			c = "0";
		}

		m_tTimerTexture2 = new Texture("RooseSally.ttf", c, m_iTimerTextSize, m_cColors->White);
		m_tTimerTexture2->Pos(Vector2(Graphics::SCREEN_WIDTH / 2 + m_vPlaySpace.x / 4 + static_cast<float>(m_tTimerTexture1->m_iWidth - m_tTimerTexture2->m_iWidth / 2),
			Graphics::SCREEN_HEIGHT / 2 - m_vPlaySpace.y / 2 - m_tTimerTexture2->m_iHeight));

		m_tTimerTexture3 = new Texture("RooseSally.ttf", d, m_iTimerTextSize, m_cColors->White);
		m_tTimerTexture3->Pos(Vector2(Graphics::SCREEN_WIDTH / 2 + m_vPlaySpace.x / 4 + static_cast<float>(m_tTimerTexture1->m_iWidth + m_tTimerTexture2->m_iWidth),
			Graphics::SCREEN_HEIGHT / 2 - m_vPlaySpace.y / 2 - m_tTimerTexture3->m_iHeight));
	}
	else if (m_fStage1TotalTime - m_fStage1Timer > 10)
	{
		m_tTimerTexture1 = new Texture("RooseSally.ttf", "0:", m_iTimerTextSize, m_cColors->White);
		m_tTimerTexture1->Pos(Vector2(Graphics::SCREEN_WIDTH / 2 + m_vPlaySpace.x / 4 - static_cast<float>(m_tTimerTexture1->m_iWidth) / 2,
			Graphics::SCREEN_HEIGHT / 2 - m_vPlaySpace.y / 2 - static_cast<float>(m_tTimerTexture1->m_iHeight)));

		int a = m_fStage1TotalTime - m_fStage1Timer;
		std::string b = std::to_string(a);
		std::string c = b.substr(0, 1);
		std::string d = b.substr(1, 1);
		if (c == "") c = "0";
		if (d == "") d = "0";
		if (a < 10)
		{
			d = c;
			c = "0";
		}

		m_tTimerTexture2 = new Texture("RooseSally.ttf", c, m_iTimerTextSize, m_cColors->White);
		m_tTimerTexture2->Pos(Vector2(Graphics::SCREEN_WIDTH / 2 + m_vPlaySpace.x / 4 + static_cast<float>(m_tTimerTexture1->m_iWidth - m_tTimerTexture2->m_iWidth / 2),
			Graphics::SCREEN_HEIGHT / 2 - m_vPlaySpace.y / 2 - m_tTimerTexture2->m_iHeight));

		m_tTimerTexture3 = new Texture("RooseSally.ttf", d, m_iTimerTextSize, m_cColors->White);
		m_tTimerTexture3->Pos(Vector2(Graphics::SCREEN_WIDTH / 2 + m_vPlaySpace.x / 4 + static_cast<float>(m_tTimerTexture1->m_iWidth + m_tTimerTexture2->m_iWidth),
			Graphics::SCREEN_HEIGHT / 2 - m_vPlaySpace.y / 2 - m_tTimerTexture3->m_iHeight));
	}
	else if (m_fStage1TotalTime - m_fStage1Timer <= 10)
	{
		m_tTimerTexture1 = new Texture("RooseSally.ttf", "0:", m_iTimerTextSize, m_cColors->Red);
		m_tTimerTexture1->Pos(Vector2(Graphics::SCREEN_WIDTH / 2 + m_vPlaySpace.x / 4 - static_cast<float>(m_tTimerTexture1->m_iWidth) / 2,
			Graphics::SCREEN_HEIGHT / 2 - m_vPlaySpace.y / 2 - static_cast<float>(m_tTimerTexture1->m_iHeight)));

		int a = m_fStage1TotalTime - m_fStage1Timer;
		std::string b = std::to_string(a);
		std::string c = b.substr(0, 1);
		std::string d = b.substr(1, 1);
		if (c == "") c = "0";
		if (d == "") d = "0";
		if (a < 10)
		{
			d = c;
			c = "0";
		}

		m_tTimerTexture2 = new Texture("RooseSally.ttf", c, m_iTimerTextSize, m_cColors->Red);
		m_tTimerTexture2->Pos(Vector2(Graphics::SCREEN_WIDTH / 2 + m_vPlaySpace.x / 4 + static_cast<float>(m_tTimerTexture1->m_iWidth - m_tTimerTexture2->m_iWidth / 2),
			Graphics::SCREEN_HEIGHT / 2 - m_vPlaySpace.y / 2 - m_tTimerTexture2->m_iHeight));

		m_tTimerTexture3 = new Texture("RooseSally.ttf", d, m_iTimerTextSize, m_cColors->Red);
		m_tTimerTexture3->Pos(Vector2(Graphics::SCREEN_WIDTH / 2 + m_vPlaySpace.x / 4 + static_cast<float>(m_tTimerTexture1->m_iWidth + m_tTimerTexture2->m_iWidth),
			Graphics::SCREEN_HEIGHT / 2 - m_vPlaySpace.y / 2 - m_tTimerTexture3->m_iHeight));
	}
}

void PlayScreen::ChangeNextLevel()
{
	m_iCurrentLevelIndex++;
	m_sLevel = m_sLevel.substr(0, 2) + std::to_string(m_lLevelChanger->m_iStageRoute[m_iCurrentLevelIndex]);
	SetTextureMap(m_sLevel);
	
	m_tLevelTitleTexture = new Texture("RooseSally.ttf", m_sLevel, m_iTitleTextSize, m_cColors->White);
	m_tLevelTitleTexture->Pos(Vector2(Graphics::SCREEN_WIDTH / 2 - static_cast<float>(m_tLevelTitleTexture->m_iWidth) / 2,
		Graphics::SCREEN_HEIGHT / 2 - m_vPlaySpace.y / 2 - static_cast<float>(m_tLevelTitleTexture->m_iHeight)));

	if (m_lLevelChanger->m_bVerticalLevelChanger[m_iCurrentLevelIndex - 1])
	{
		float setback = 0.0f;
		if (m_bFalling) setback = -m_fPlayerFallingSpeed;
		if (!m_bFalling) setback = m_fPlayerFallingSpeed;
		m_tPlayerTexture->Pos(Vector2(150.0f, m_tPlayerTexture->m_vPos.y + setback));
	}
	else
	{
		if (m_tPlayerTexture->m_vPos.y < Graphics::SCREEN_HEIGHT / 2)
		{
			m_tPlayerTexture->Pos(Vector2(m_tPlayerTexture->m_vPos.x, 775.0f));
		}
		else
		{
			m_tPlayerTexture->Pos(Vector2(m_tPlayerTexture->m_vPos.x, 150.0f));
		}
	}
}

void PlayScreen::ChangeBackLevel()
{
	m_iCurrentLevelIndex--;
	m_sLevel = m_sLevel.substr(0, 2) + std::to_string(m_lLevelChanger->m_iStageRoute[m_iCurrentLevelIndex]);
	SetTextureMap(m_sLevel);

	m_tLevelTitleTexture = new Texture("RooseSally.ttf", m_sLevel, m_iTitleTextSize, m_cColors->White);
	m_tLevelTitleTexture->Pos(Vector2(Graphics::SCREEN_WIDTH / 2 - static_cast<float>(m_tLevelTitleTexture->m_iWidth) / 2,
		Graphics::SCREEN_HEIGHT / 2 - m_vPlaySpace.y / 2 - static_cast<float>(m_tLevelTitleTexture->m_iHeight)));

	if (m_lLevelChanger->m_bVerticalLevelChanger[m_iCurrentLevelIndex])
	{
		float setback = 0.0f;
		if (m_bFalling) setback = -m_fPlayerFallingSpeed;
		if (!m_bFalling) setback = m_fPlayerFallingSpeed;
		m_tPlayerTexture->Pos(Vector2(825.0f, m_tPlayerTexture->m_vPos.y));
	}
	else
	{
		if (m_tPlayerTexture->m_vPos.y > Graphics::SCREEN_HEIGHT / 2)
		{
			m_tPlayerTexture->Pos(Vector2(m_tPlayerTexture->m_vPos.x, 150.0f));
		}
		else
		{
			m_tPlayerTexture->Pos(Vector2(m_tPlayerTexture->m_vPos.x, 775.0f));
		}
	}
}

void PlayScreen::UpdateSpecialObjects()
{
	//checkpoint
	m_bSpecialObjectsEnabled[0] = false;
	m_bSpecialObjectsEnabled[1] = false;

	int m_iCurrentLevel = std::stoi(m_sLevel.substr(2, 2));

	for (int i = 0; i < 6; i++)
	{
		if (m_lLevelChanger->m_iLevelsWithCheckpoint[i] == m_iCurrentLevel - 1)
		{
			if (m_lLevelChanger->GetActiveCheckpoint() == i)
			{
				m_bSpecialObjectsEnabled[0] = false;
				m_bSpecialObjectsEnabled[1] = true;
				m_tSpecialObjectsTextures[1]->m_vPos = m_lLevelChanger->m_vCheckPointWorldLocations[i];
			}
			else
			{
				m_bSpecialObjectsEnabled[0] = true;
				m_bSpecialObjectsEnabled[1] = false;
				m_tSpecialObjectsTextures[0]->m_vPos = m_lLevelChanger->m_vCheckPointWorldLocations[i];
			}
		}
	}
}

void PlayScreen::ApplyInputs()
{
	//moving left input XOR moving right input
	if ((m_vPlayerTranslationLeft.x != 0 || m_vPlayerTranslationRight.x != 0) &&
		(-1 * m_vPlayerTranslationLeft.x) != m_vPlayerTranslationRight.x)
	{
		if (m_vPlayerTranslationLeft.x == -1)
		{
			if (!m_cCollisionManager->m_bCollidedLeft)
			{
				m_tPlayerTexture->TranslatePos(m_vPlayerTranslationLeft.x * m_fPlayerMovementSpeed, m_vPlayerTranslationLeft.y);
				PlayerAnimationFlags.movingLeft = true;
			}
			else
			{
				PlayerAnimationFlags.movingLeft = false;
			}
		}
		else
		{
			PlayerAnimationFlags.movingLeft = false;
		}
		if (m_vPlayerTranslationRight.x == 1)
		{
			if (!m_cCollisionManager->m_bCollidedRight)
			{
				m_tPlayerTexture->TranslatePos(m_vPlayerTranslationRight.x * m_fPlayerMovementSpeed, m_vPlayerTranslationRight.y);
				PlayerAnimationFlags.movingRight = true;
			}
			else
			{
				PlayerAnimationFlags.movingRight = false;
			}
		}
		else
		{
			PlayerAnimationFlags.movingRight = false;
		}
	}
	else
	{
		PlayerAnimationFlags.movingLeft = false;
		PlayerAnimationFlags.movingRight = false;
	}

	if (m_bFalling)
	{
		if (!m_cCollisionManager->m_bCollidedDown && !m_cCollisionManager->m_bCollidedBottomLeft && !m_cCollisionManager->m_bCollidedBottomRight)
		{
			m_tPlayerTexture->TranslatePos(0.0f, -m_fPlayerFallingSpeed);
			PlayerAnimationFlags.falling = true;
		}
		else if (m_cCollisionManager->m_bCollidedBottomLeft && m_cCollisionManager->m_bCollidedLeft && !m_cCollisionManager->m_bCollidedDown ||
			m_cCollisionManager->m_bCollidedBottomRight && m_cCollisionManager->m_bCollidedRight && !m_cCollisionManager->m_bCollidedDown)
		{
			m_tPlayerTexture->TranslatePos(0.0f, -m_fPlayerFallingSpeed);
			PlayerAnimationFlags.falling = true;
		}
		else
		{
			PlayerAnimationFlags.falling = false;
		}
	}
	else
	{
		if (!m_cCollisionManager->m_bCollidedUp && !m_cCollisionManager->m_bCollidedTopLeft && !m_cCollisionManager->m_bCollidedTopRight)
		{
			m_tPlayerTexture->TranslatePos(0.0f, m_fPlayerFallingSpeed);
			PlayerAnimationFlags.jumping = true;
		}
		else if (m_cCollisionManager->m_bCollidedTopLeft && m_cCollisionManager->m_bCollidedLeft && !m_cCollisionManager->m_bCollidedUp ||
				 m_cCollisionManager->m_bCollidedTopRight && m_cCollisionManager->m_bCollidedRight && !m_cCollisionManager->m_bCollidedUp)
		{
			m_tPlayerTexture->TranslatePos(0.0f, m_fPlayerFallingSpeed);
			PlayerAnimationFlags.jumping = true;
		}
		else
		{
			PlayerAnimationFlags.jumping = false;
		}
	}
}

void PlayScreen::AnimatePlayer()
{
	PlayerAnimationFlags.fallingRight = false;
	PlayerAnimationFlags.fallingLeft = false;
	PlayerAnimationFlags.jumpingRight = false;
	PlayerAnimationFlags.jumpingLeft = false;

	if (m_bFalling && PlayerAnimationFlags.movingRight) PlayerAnimationFlags.fallingRight = true;
	if (m_bFalling && PlayerAnimationFlags.movingLeft) PlayerAnimationFlags.fallingLeft = true;
	if (!m_bFalling && PlayerAnimationFlags.movingRight) PlayerAnimationFlags.jumpingRight = true;
	if (!m_bFalling && PlayerAnimationFlags.movingLeft) PlayerAnimationFlags.jumpingLeft = true;

	if (PlayerAnimationFlags.movingRight)
	{
		if (m_bFalling)
		{
			m_tPlayerTexture = new Texture("Sprites/Character/Idle/characteridleright.png", m_tPlayerTexture->m_vPos,
				static_cast<int>(m_vPlayerSize.x), static_cast<int>(m_vPlayerSize.y), 0.0f);
			PlayerAnimationFlags.facingRight = true;
		}
		else
		{
			m_tPlayerTexture = new Texture("Sprites/Character/Idle/characteridleleft.png", m_tPlayerTexture->m_vPos,
				static_cast<int>(m_vPlayerSize.x), static_cast<int>(m_vPlayerSize.y), 180.0f);
			PlayerAnimationFlags.facingRight = true;
		}
	}
	else if (PlayerAnimationFlags.movingLeft)
	{
		if (m_bFalling)
		{
			m_tPlayerTexture = new Texture("Sprites/Character/Idle/characteridleleft.png", m_tPlayerTexture->m_vPos,
				static_cast<int>(m_vPlayerSize.x), static_cast<int>(m_vPlayerSize.y), 0.0f);
			PlayerAnimationFlags.facingRight = false;
		}
		else
		{
			m_tPlayerTexture = new Texture("Sprites/Character/Idle/characteridleright.png", m_tPlayerTexture->m_vPos,
				static_cast<int>(m_vPlayerSize.x), static_cast<int>(m_vPlayerSize.y), 180.0f);
			PlayerAnimationFlags.facingRight = false;
		}
	}

	if (PlayerAnimationFlags.falling && PlayerAnimationFlags.facingRight)
	{
		m_tPlayerTexture = new Texture("Sprites/Character/Jumping/characterjumpingright.png", m_tPlayerTexture->m_vPos,
			static_cast<int>(m_vPlayerSize.x), static_cast<int>(m_vPlayerSize.y), 0.0f);
	}
	else if (PlayerAnimationFlags.falling && !PlayerAnimationFlags.facingRight)
	{
		m_tPlayerTexture = new Texture("Sprites/Character/Jumping/characterjumpingleft.png", m_tPlayerTexture->m_vPos,
			static_cast<int>(m_vPlayerSize.x), static_cast<int>(m_vPlayerSize.y), 0.0f);
	}

	if (PlayerAnimationFlags.jumping && PlayerAnimationFlags.facingRight)
	{
		m_tPlayerTexture = new Texture("Sprites/Character/Jumping/characterjumpingleft.png", m_tPlayerTexture->m_vPos,
			static_cast<int>(m_vPlayerSize.x), static_cast<int>(m_vPlayerSize.y), 180.0f);
	}
	else if (PlayerAnimationFlags.jumping && !PlayerAnimationFlags.facingRight)
	{
		m_tPlayerTexture = new Texture("Sprites/Character/Jumping/characterjumpingright.png", m_tPlayerTexture->m_vPos,
			static_cast<int>(m_vPlayerSize.x), static_cast<int>(m_vPlayerSize.y), 180.0f);
	}

	if (PlayerAnimationFlags.dead)
	{
		if (PlayerAnimationFlags.facingRight)
		{
			if (m_bFalling)
			{
				m_tPlayerTexture = new Texture("Sprites/Character/Dead/characterdeadright2.png", m_tPlayerTexture->m_vPos,
					static_cast<int>(m_vPlayerSize.x), static_cast<int>(m_vPlayerSize.y), 0.0f);
			}
			else
			{
				m_tPlayerTexture = new Texture("Sprites/Character/Dead/characterdeadleft2.png", m_tPlayerTexture->m_vPos,
					static_cast<int>(m_vPlayerSize.x), static_cast<int>(m_vPlayerSize.y), 180.0f);
			}
		}
		else
		{
			if (m_bFalling)
			{
				m_tPlayerTexture = new Texture("Sprites/Character/Dead/characterdeadleft2.png", m_tPlayerTexture->m_vPos,
					static_cast<int>(m_vPlayerSize.x), static_cast<int>(m_vPlayerSize.y), 0.0f);
			}
			else
			{
				m_tPlayerTexture = new Texture("Sprites/Character/Dead/characterdeadright2.png", m_tPlayerTexture->m_vPos,
					static_cast<int>(m_vPlayerSize.x), static_cast<int>(m_vPlayerSize.y), 180.0f);
			}

		}
	}
}

void PlayScreen::GetInputs(Vector2& m_vPlayerTranslationLeft, Vector2& m_vPlayerTranslationRight)
{
	if (m_iInputManager->KeyPressed(SDL_SCANCODE_W) ||
		m_iInputManager->KeyPressed(SDL_SCANCODE_UP) ||
		m_iInputManager->KeyPressed(SDL_SCANCODE_SPACE) ||
		m_iInputManager->KeyPressed(SDL_SCANCODE_S) ||
		m_iInputManager->KeyPressed(SDL_SCANCODE_DOWN))
	{
		//invert gravity
		if (m_bFalling && m_cCollisionManager->m_bCollidedDown ||
			(m_bFalling && m_cCollisionManager->m_bCollidedBottomLeft && !m_cCollisionManager->m_bCollidedLeft ||
			m_bFalling && m_cCollisionManager->m_bCollidedBottomRight && !m_cCollisionManager->m_bCollidedRight))
		{
			m_bFalling = false;
		}
		else if (!m_bFalling && m_cCollisionManager->m_bCollidedUp ||
				(!m_bFalling && m_cCollisionManager->m_bCollidedTopLeft && !m_cCollisionManager->m_bCollidedLeft ||
				!m_bFalling && m_cCollisionManager->m_bCollidedTopRight && !m_cCollisionManager->m_bCollidedRight))
		{
			m_bFalling = true;
		}
		
	}

	if (m_iInputManager->KeyPressed(SDL_SCANCODE_A) ||
		m_iInputManager->KeyPressed(SDL_SCANCODE_LEFT))
	{
		m_vPlayerTranslationLeft.x = -1;
	}
	if (m_iInputManager->KeyReleased(SDL_SCANCODE_A) ||
		m_iInputManager->KeyReleased(SDL_SCANCODE_LEFT))
	{
		m_vPlayerTranslationLeft.x = 0;
	}

	if (m_iInputManager->KeyPressed(SDL_SCANCODE_D) ||
		m_iInputManager->KeyPressed(SDL_SCANCODE_RIGHT))
	{
		m_vPlayerTranslationRight.x = 1;
	}
	if (m_iInputManager->KeyReleased(SDL_SCANCODE_D) ||
		m_iInputManager->KeyReleased(SDL_SCANCODE_RIGHT))
	{
		m_vPlayerTranslationRight.x = 0;
	}


	if (m_iInputManager->KeyPressed(SDL_SCANCODE_ESCAPE))
	{
		m_iSceneToOpen = 0;
		m_aAudioManager->PauseMusic();
		m_aAudioManager->PlayMusic("menutrack.wav", 1);
		m_aAudioManager->SetVolume(75.0f);

		RestartScene();
		m_iCurrentLevelIndex = 0;
	}
}

void PlayScreen::SetTextureMap(std::string level)
{
	//get the level data from the file
	m_lLevels->GetLevel(level);

	//use the level data from the file to layout the screen
	//get the m_sLevelLayout[m_iLevelDepth][m_iLevelWidth] and m_iLevelRotations[m_iLevelDepth][m_iLevelWidth]

	Vector2 vTempPosArr = Vector2(Graphics::SCREEN_WIDTH / 2 - m_vPlaySpace.x / 2, Graphics::SCREEN_HEIGHT / 2 - m_vPlaySpace.y / 2);

	//decrease position array by standard texture size initially so the first row will be in the correct space
	vTempPosArr.y -= m_iStandardTextureSize;

	for (int i = 0; i < Levels::m_iLevelDepth; ++i)
	{
		//increment y by standard texture size so that the next textures will be rendered below the previous row
		vTempPosArr.y += m_iStandardTextureSize;
		//reset x to the leftmost playspace location
		vTempPosArr.x = Graphics::SCREEN_WIDTH / 2 - m_vPlaySpace.x / 2;

		for (int j = 0; j < Levels::m_iLevelWidth; ++j)
		{
			if (m_lLevels->m_sLevelLayout[i][j] != "empty") //if the spirte path wasn't set to "empty"
			{
				//set the 2D array Texture using position array, then m_sLevelLayout and m_iLevelRotations in the Levels instance
				m_tLevelLayoutTextures[i][j] = new Texture(m_lLevels->m_sLevelLayout[i][j], vTempPosArr, m_iStandardTextureSize,
														   m_iStandardTextureSize, static_cast<float>(m_lLevels->m_iLevelRotations[i][j]));
			}
			else
			{
				m_tLevelLayoutTextures[i][j] = NULL; //sprite path set to "empty", set the 2D array Texture to NULL so nothing is rendered
			}
			//increment x by standard texture size so that the next texture will be rendered in front of the previous one
			vTempPosArr.x += m_iStandardTextureSize;
		}
	}
}

void PlayScreen::SetLevel(std::string sLevel)
{
	m_sLevel = sLevel;
}

void PlayScreen::RestartScene()
{
	Vector2 vTempPos = Vector2(210, 498);
	m_tPlayerTexture = new Texture("Sprites/Character/Idle/characteridleright.png", vTempPos,
		static_cast<int>(m_vPlayerSize.x), static_cast<int>(m_vPlayerSize.y), 0.0f);


	Vector2 vTempPos2 = Vector2(Graphics::SCREEN_WIDTH / 2 - m_vPlaySpace.x / 2, Graphics::SCREEN_HEIGHT / 2 - m_vPlaySpace.y / 2);
	m_tBackgroundTexture = new Texture("Sprites/Backgrounds/mainbackground.png", vTempPos2,
		static_cast<int>(m_vPlaySpace.x), static_cast<int>(m_vPlaySpace.y), 0.0f);


	m_tLevelTitleTexture = new Texture("RooseSally.ttf", "1-1", m_iTitleTextSize, m_cColors->White);
	m_tLevelTitleTexture->Pos(Vector2(Graphics::SCREEN_WIDTH / 2 - static_cast<float>(m_tLevelTitleTexture->m_iWidth) / 2,
		Graphics::SCREEN_HEIGHT / 2 - m_vPlaySpace.y / 2 - static_cast<float>(m_tLevelTitleTexture->m_iHeight)));

	m_tTimerTexture1 = new Texture("RooseSally.ttf", "3:", m_iTimerTextSize, m_cColors->White);
	m_tTimerTexture1->Pos(Vector2(Graphics::SCREEN_WIDTH / 2 + m_vPlaySpace.x / 4 - static_cast<float>(m_tTimerTexture1->m_iWidth) / 2,
		Graphics::SCREEN_HEIGHT / 2 - m_vPlaySpace.y / 2 - static_cast<float>(m_tTimerTexture1->m_iHeight)));

	m_tTimerTexture2 = new Texture("RooseSally.ttf", "2", m_iTimerTextSize, m_cColors->White);
	m_tTimerTexture2->Pos(Vector2(Graphics::SCREEN_WIDTH / 2 + m_vPlaySpace.x / 4 + static_cast<float>(m_tTimerTexture1->m_iWidth - m_tTimerTexture2->m_iWidth / 2),
		Graphics::SCREEN_HEIGHT / 2 - m_vPlaySpace.y / 2 - m_tTimerTexture2->m_iHeight));

	m_tTimerTexture3 = new Texture("RooseSally.ttf", "0", m_iTimerTextSize, m_cColors->White);
	m_tTimerTexture3->Pos(Vector2(Graphics::SCREEN_WIDTH / 2 + m_vPlaySpace.x / 4 + static_cast<float>(m_tTimerTexture1->m_iWidth + m_tTimerTexture2->m_iWidth - m_tTimerTexture3->m_iWidth / 2),
		Graphics::SCREEN_HEIGHT / 2 - m_vPlaySpace.y / 2 - m_tTimerTexture3->m_iHeight));


	SpecialObjectsFactory instance1;
	instance1.InitializeCheckpoint(45, 65, 175, 502, 0);
	SpecialObjects* object1;

	object1 = instance1.GetCheck();

	vTempPos = Vector2(object1->GetXPos(), object1->GetYPos());
	m_tSpecialObjectsTextures[0] = new Texture(object1->GetPath(), vTempPos, object1->GetWidth(), object1->GetHeight(), object1->GetRotation());
	m_bSpecialObjectsEnabled[0] = false;

	SpecialObjectsFactory instance2;
	instance2.InitializeCheckpoint(45, 65, 175, 502, 0);
	SpecialObjects* object2;

	object2 = instance2.GetCheck();

	vTempPos = Vector2(object2->GetXPos(), object2->GetYPos());
	m_tSpecialObjectsTextures[1] = new Texture("Sprites/Special/Checkpoints/checkpointactive.png", vTempPos, object2->GetWidth(), object2->GetHeight(), object2->GetRotation());
	m_bSpecialObjectsEnabled[1] = false;


	m_bGameOver = false;
	m_fStage1Timer = 0.0f;
	m_fPlayerDeathTimer = 0.0f;
	m_fGameOverScreenTimer = 0.0f;
	m_bFalling = true;
	PlayerAnimationFlags.dead = false;
	PlayerAnimationFlags.facingRight = true;
	m_lLevelChanger->SetActiveCheckpoint(0);
	m_iCurrentLevelIndex = 0;
	m_sLevel = "1-1";
	SetTextureMap(m_sLevel);
}

PlayScreen::PlayScreen()
{
	//instances
	m_tTimer = Timer::Instance();
	m_iInputManager = InputManager::Instance();
	m_lLevels = Levels::Instance();
	m_aAudioManager = AudioManager::Instance();
	m_cCollisionManager = CollisionManager::Instance();
	m_cColors = Colors::Instance();
	m_lLevelChanger = LevelChanger::Instance();

	RestartScene();
}

PlayScreen::~PlayScreen()
{
	m_tTimer = NULL;

	m_iInputManager = NULL;

	delete m_tPlayerTexture;
	m_tPlayerTexture = NULL;

	delete m_tBackgroundTexture;
	m_tBackgroundTexture = NULL;

	delete m_tLevelTitleTexture;
	m_tLevelTitleTexture = NULL;

	delete m_tTimerTexture1;
	m_tTimerTexture1 = NULL;

	delete m_tTimerTexture2;
	m_tTimerTexture2 = NULL;

	delete m_tTimerTexture3;
	m_tTimerTexture3 = NULL;

	delete m_lLevelChanger;
	m_lLevelChanger = NULL;


	for (int i = 0; i < Levels::m_iLevelDepth; ++i)
	{
		for (int j = 0; j < Levels::m_iLevelWidth; ++j)
		{
			if (m_tLevelLayoutTextures[i][j] != NULL)
			{
				delete m_tLevelLayoutTextures[i][j];
				m_tLevelLayoutTextures[i][j] = NULL;
			}
		}
	}

	for (int i = 0; i < m_iMaxNumOfSpeicalObjects; i++)
	{
		if (m_tSpecialObjectsTextures[i] != NULL)
		{
			delete m_tSpecialObjectsTextures[i];
			m_tSpecialObjectsTextures[i] = NULL;
		}
	}
}