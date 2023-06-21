#ifndef _LEVELS_H_
#define _LEVELS_H_

#include "Graphics.h"

#include <string>
#include <fstream>
#include <iostream>

class Levels
{
public:
	static const int m_iNumOfScreens = 3; // 9 - 9 - 3
	//29 mid & foreground space, 2 for border around map
	static const int m_iLevelWidth = 31;
	static const int m_iLevelDepth = 31;

	static const int m_iNumOfMidGroundAssets = 25;

	//arrays that are changed to represent the required level
	std::string m_sLevelLayout[m_iLevelDepth][m_iLevelWidth];
	int m_iLevelRotations[m_iLevelDepth][m_iLevelWidth];


private:
	static Levels* m_sInstance;

	//variables for file reading

	std::string m_sLevelFromFile[m_iLevelDepth];

	std::string m_sLineText = "";
	int m_iLineCount = 0;

	//variables for managing data from file 

	//X/Y counter for sprite path array
	int m_i2DArrayXCounterSprite, m_i2DArrayYCounterSprite = 0;
	//X/Y counter for sprite rotations array
	int m_i2DArrayXCounterRotation, m_i2DArrayYCounterRotation = 0;
	//boolean indicating end of line
	bool m_bEndOfLine = false;
	//counters for spliting line of data into substrings
	int m_iStringIndexCounter, m_iSubStringIndexCounter = 0;

	std::string m_sAssetPaths[m_iNumOfMidGroundAssets] =
	{
		//yellow blocks
		"Sprites/Midground objects/yellowblockempty.png", //0
		"Sprites/Midground objects/yellowblockN.png",
		"Sprites/Midground objects/yellowblockNE.png",
		"Sprites/Midground objects/yellowblockNS.png",
		"Sprites/Midground objects/yellowblockNES.png",
		"Sprites/Midground objects/yellowblockNESW.png",
		"Sprites/Midground objects/yellowblockcorner.png",

		//red blocks
		"Sprites/Midground objects/redblockempty.png", //7
		"Sprites/Midground objects/redblockN.png",
		"Sprites/Midground objects/redblockNE.png",
		"Sprites/Midground objects/redblockNS.png",
		"Sprites/Midground objects/redblockNES.png",
		"Sprites/Midground objects/redblockNESW.png",
		"Sprites/Midground objects/redblockcorner.png",

		//grey blocks
		"Sprites/Midground objects/greyblockempty.png", //14
		"Sprites/Midground objects/greyblockN.png",
		"Sprites/Midground objects/greyblockNE.png",
		"Sprites/Midground objects/greyblockNS.png",
		"Sprites/Midground objects/greyblockNES.png",
		"Sprites/Midground objects/greyblockNESW.png",
		"Sprites/Midground objects/greyblockcorner.png",

		//spikes
		"Sprites/Foreground objects/spikes/greenspike.png", //21
		"Sprites/Foreground objects/spikes/yellowspike.png",
		"Sprites/Foreground objects/spikes/bluespike.png",
		"Sprites/Foreground objects/spikes/redspike.png"
	};


public:
	static Levels* Instance();
	static void Release();

	void GetLevel(std::string level);


private:
	Levels();
	~Levels();

};

#endif // ! _LEVELS_H_
