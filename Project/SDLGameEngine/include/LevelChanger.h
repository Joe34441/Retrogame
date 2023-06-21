#ifndef _LEVELCHANGER_H_
#define _LEVELCHANGER_H_

#include <string>
#include "MathUtility.h"

class LevelChanger
{
private:
	static LevelChanger* m_sInstance;


	int m_iActiveCheckpoint;
	
public:
	Vector2 m_vLevelChangersNext[12];
	Vector2 m_vLevelChangersExit[12];
	bool m_bVerticalLevelChanger[12];

	int m_iStageRoute[12];

	Vector2 m_vCheckpointLocations[6];
	Vector2 m_vCheckPointWorldLocations[6];
	int m_iLevelsWithCheckpoint[6];

private:


public:
	LevelChanger();
	~LevelChanger();

	void SetActiveCheckpoint(int checkIndex);
	int GetActiveCheckpoint();

	static LevelChanger* Instance();
	static void Release();
};


#endif