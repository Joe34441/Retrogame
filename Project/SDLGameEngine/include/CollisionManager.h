#ifndef _COLLISIONMANAGER_H_
#define _COLLISIONMANAGER_H_

#include "Levels.h"

class CollisionManager
{
public:
	bool m_bCollidedUp = false;
	bool m_bCollidedDown = false;
	bool m_bCollidedLeft = false;
	bool m_bCollidedRight = false;

	bool m_bCollidedTopLeft = false;
	bool m_bCollidedBottomLeft = false;
	bool m_bCollidedTopRight = false;
	bool m_bCollidedBottomRight = false;

	bool m_bDead = false;

private:
	static CollisionManager* m_sInstance;

	Levels* m_lLevels;

	std::string m_sCurrentLevel;

	int m_iLevelLayoutIndexX = 1;
	int m_iLevelLayoutIndexY = 1;

	static const int m_iNumOfBlocks = 21;
	std::string m_sBlocks[m_iNumOfBlocks] =
	{
		//yellow blocks
		"Sprites/Midground objects/yellowblockempty.png",
		"Sprites/Midground objects/yellowblockN.png",
		"Sprites/Midground objects/yellowblockNE.png",
		"Sprites/Midground objects/yellowblockNS.png",
		"Sprites/Midground objects/yellowblockNES.png",
		"Sprites/Midground objects/yellowblockNESW.png",
		"Sprites/Midground objects/yellowblockcorner.png",

		//red blocks
		"Sprites/Midground objects/redblockempty.png",
		"Sprites/Midground objects/redblockN.png",
		"Sprites/Midground objects/redblockNE.png",
		"Sprites/Midground objects/redblockNS.png",
		"Sprites/Midground objects/redblockNES.png",
		"Sprites/Midground objects/redblockNESW.png",
		"Sprites/Midground objects/redblockcorner.png",

		//grey blocks
		"Sprites/Midground objects/greyblockempty.png",
		"Sprites/Midground objects/greyblockN.png",
		"Sprites/Midground objects/greyblockNE.png",
		"Sprites/Midground objects/greyblockNS.png",
		"Sprites/Midground objects/greyblockNES.png",
		"Sprites/Midground objects/greyblockNESW.png",
		"Sprites/Midground objects/greyblockcorner.png",
	};

	static const int m_iNumOfSpikes = 4;
	std::string m_sSpikes[m_iNumOfSpikes] = 
	{
		"Sprites/Foreground objects/spikes/greenspike.png",
		"Sprites/Foreground objects/spikes/yellowspike.png",
		"Sprites/Foreground objects/spikes/bluespike.png",
		"Sprites/Foreground objects/spikes/redspike.png"
	};

	Vector2 m_vLevelExit;
	Vector2 m_vLevelNext;
	bool m_bVerticalLevelChangerNext = true;
	bool m_bVerticalLevelChangerExit = true;

	Vector2 m_vPlayerWorldLocation;
	Vector2 m_vPlayerWorldSize;
	Vector2 m_vCheckpointLocation;
	Vector2 m_vCheckpointSize;

public:
	static CollisionManager* Instance();
	static void Release();

	int CheckCollision(std::string m_sLevelNum, Vector2 m_vPlayerPos, Vector2 m_vPlayerSize, Vector2 m_vPlaySpace, int m_iTextureSize, int m_iCheckMode);

	void SetLevelChangers(Vector2 m_vNext, Vector2 m_vExit, bool m_vVLC);

	void SetSpecialObjectParams(Vector2 m_vCheckLocation, Vector2 m_vCheckSize, Vector2 m_vPlayerLocation, Vector2 m_vPlayerSize);

private:
	CollisionManager();
	~CollisionManager();

};

#endif