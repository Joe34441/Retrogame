#include "Levels.h"

Levels* Levels::m_sInstance = NULL;

Levels* Levels::Instance() {

	if (m_sInstance == NULL)
	{
		m_sInstance = new Levels();
	}

	return m_sInstance;
}

void Levels::Release()
{
	delete m_sInstance;
	m_sInstance = NULL;
}

void Levels::GetLevel(std::string level)
{
	//File layout:
	//		1st <number> - reference index to asset
	//		: - end of reference index
	//		2nd <number> - rotation of asset
	//		"," - end of rotation value
	//		"." - end of line
	//		" " in place of number - no image for this space


	std::string sPath = SDL_GetBasePath();
	sPath.append("Assets/Levels/" + level + ".txt");

	std::ifstream file;
	file.open(sPath);

	if (file.is_open())
	{
		m_iLineCount = 0;
		m_sLineText = "";

		while (std::getline(file, m_sLineText))
		{
			m_sLevelFromFile[m_iLineCount] = m_sLineText;
			m_iLineCount++;
		}

		file.close();

		
		//go through each m_slevelfromfile, seperate into asset index and rotations
		//for index, use number in asset array (levellayout = assetpaths[number])

		m_i2DArrayXCounterSprite = -1;
		m_i2DArrayXCounterRotation = -1;
		for (std::string tempString : m_sLevelFromFile)
		{
			//increment 2D array counter in Y
			m_i2DArrayXCounterSprite++;
			m_i2DArrayXCounterRotation++;

			m_bEndOfLine = false;

			m_iStringIndexCounter = 0;
			m_iSubStringIndexCounter = 0;

			m_i2DArrayYCounterSprite = 0;
			m_i2DArrayYCounterRotation = 0;

			while (!m_bEndOfLine)
			{
				if (tempString[m_iStringIndexCounter] == ':')
				{
					//create a substring which contains the asset index
					std::string assetIndex = tempString.substr(m_iSubStringIndexCounter, m_iStringIndexCounter - m_iSubStringIndexCounter);
					//if the asset index is not a whitespace (indicating empty space in world pos)
					if (assetIndex != " ")
					{
						//convert asset index string to an integer, then use this integer to find the asset path,
						//then add the asset path to the LevelLayout 2D array
						m_sLevelLayout[m_i2DArrayXCounterSprite][m_i2DArrayYCounterSprite] = m_sAssetPaths[std::stoi(assetIndex)];
					}
					else //the asset index is a whitespace (indicating empty space in world pos)
					{
						//add text "empty" to the LevelLayout 2D array to indicate to skip drawing a sprite here
						m_sLevelLayout[m_i2DArrayXCounterSprite][m_i2DArrayYCounterSprite] = "empty";
					}
					//increment main counter
					m_iStringIndexCounter++;
					//set substring counter to equal main coutner
					m_iSubStringIndexCounter = m_iStringIndexCounter;
					//increment 2D Sprite array counter in Y
					m_i2DArrayYCounterSprite++;
				}
				else if (tempString[m_iStringIndexCounter] == ',')
				{
					//create a substring which contains the asset rotation
					std::string assetRotation = tempString.substr(m_iSubStringIndexCounter, m_iStringIndexCounter - m_iSubStringIndexCounter);
					//if the asset rotation is not a whitespace (indicating no sprite to be drawn here)
					if (assetRotation != " ")
					{
						//convert asset rotation string to an integer and add it to the LevelRotations 2D array
						m_iLevelRotations[m_i2DArrayXCounterRotation][m_i2DArrayYCounterRotation] = std::stoi(assetRotation);
					}
					else //the asset rotation is a whitespace (indicating no sprite to be drawn here)
					{
						//add NULL to the LevelLayout 2D array
						m_iLevelRotations[m_i2DArrayXCounterRotation][m_i2DArrayYCounterRotation] = NULL;
					}
					//increment main counter
					m_iStringIndexCounter++;
					//set substring counter to equal main coutner
					m_iSubStringIndexCounter = m_iStringIndexCounter;
					//increment 2D Rotation array counter in Y
					m_i2DArrayYCounterRotation++;
				}
				else if (tempString[m_iStringIndexCounter] == '.')
				{
					m_bEndOfLine = true;
				}
				else
				{
					m_iStringIndexCounter++;
				}
			}
		}
	}
	else
	{
		file.close();
		printf("Cannot find level:\n");
	}
}

Levels::Levels()
{

}

Levels::~Levels()
{

}
