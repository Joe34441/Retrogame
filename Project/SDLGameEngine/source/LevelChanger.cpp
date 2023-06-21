#include "LevelChanger.h"

LevelChanger* LevelChanger::m_sInstance = NULL;

LevelChanger* LevelChanger::Instance()
{
	if (m_sInstance == NULL)
	{
		m_sInstance = new LevelChanger();
	}
	return m_sInstance;
}

void LevelChanger::Release()
{
	delete m_sInstance;
	m_sInstance = NULL;
}

void LevelChanger::SetActiveCheckpoint(int checkIndex)
{
	m_iActiveCheckpoint = checkIndex;
}

int LevelChanger::GetActiveCheckpoint()
{
	return m_iActiveCheckpoint;
}

LevelChanger::LevelChanger()
{
	//progression of each level through the stage if always moved forwards; if moved to next level, the next
	//value in this array is used. If moving to previous level, the previous value in this aray is used.
	m_iStageRoute[0] = 1;
	m_iStageRoute[1] = 2;
	m_iStageRoute[2] = 3;
	m_iStageRoute[3] = 2;
	m_iStageRoute[4] = 4;
	m_iStageRoute[5] = 5;
	m_iStageRoute[6] = 6;
	m_iStageRoute[7] = 7;
	m_iStageRoute[8] = 6;
	m_iStageRoute[9] = 7;
	m_iStageRoute[10] = 8;
	m_iStageRoute[11] = 9;

	//m_vLevelChangersNext/Exit is the vector2 index position of the start of an end point of each screen
	//m_bVerticalLevelChanger is true if progression to the next screen is vertical
	//(e.g. left to right = true, top to middle = false)
	m_vLevelChangersNext[0] = Vector2(29, 15);
	m_vLevelChangersExit[0] = Vector2(0, 15);
	m_bVerticalLevelChanger[0] = true;

	m_vLevelChangersNext[1] = Vector2(9, 29);
	m_vLevelChangersExit[1] = Vector2(9, 0);
	m_bVerticalLevelChanger[1] = false;

	m_vLevelChangersNext[2] = Vector2(17, 0);
	m_vLevelChangersExit[2] = Vector2(17, 29);
	m_bVerticalLevelChanger[2] = false;

	m_vLevelChangersNext[3] = Vector2(29, 15);
	m_vLevelChangersExit[3] = Vector2(0, 15);
	m_bVerticalLevelChanger[3] = true;

	m_vLevelChangersNext[4] = Vector2(9, 29);
	m_vLevelChangersExit[4] = Vector2(9, 0);
	m_bVerticalLevelChanger[4] = false;



	//levels with a checkpoint and their vec2 location
	m_iLevelsWithCheckpoint[0] = 0;
	m_iLevelsWithCheckpoint[1] = 2;
	m_iLevelsWithCheckpoint[2] = 3;
	//to add
	m_iLevelsWithCheckpoint[3] = 5;
	//m_iLevelsWithCheckpoint[4] = ;
	//m_iLevelsWithCheckpoint[5] = ;


	m_vCheckpointLocations[0] = Vector2(2, 17);
	m_vCheckpointLocations[1] = Vector2(9, 10);
	m_vCheckpointLocations[2] = Vector2(4, 17);
	//to add
	m_vCheckpointLocations[3] = Vector2(0, 0);
	m_vCheckpointLocations[4] = Vector2(0, 0);
	m_vCheckpointLocations[5] = Vector2(0, 0);


	m_vCheckPointWorldLocations[0] = Vector2(175, 502);
	m_vCheckPointWorldLocations[1] = Vector2(350, 327);
	m_vCheckPointWorldLocations[2] = Vector2(225, 502);


	m_iActiveCheckpoint = 0;

}

LevelChanger::~LevelChanger()
{

}