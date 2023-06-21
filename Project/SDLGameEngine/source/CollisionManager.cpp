#include "CollisionManager.h"

CollisionManager* CollisionManager::m_sInstance = NULL;

CollisionManager* CollisionManager::Instance() {

	if (m_sInstance == NULL)
	{
		m_sInstance = new CollisionManager();
	}

	return m_sInstance;
}

void CollisionManager::Release()
{
	delete m_sInstance;
	m_sInstance = NULL;
}

int CollisionManager::CheckCollision(std::string m_sLevelNum, Vector2 m_vPlayerPos, Vector2 m_vPlayerSize, Vector2 m_vPlaySpace, int m_iTextureSize, int m_iCheckMode)
{
	if (m_sCurrentLevel != m_sLevelNum) //only reload level if its a new level
	{
		m_sCurrentLevel = m_sLevelNum;
		m_lLevels->GetLevel(m_sCurrentLevel);
	}

	//finding player pos in relation to the TextureMap
	Vector2 vTempPosArr = Vector2(Graphics::SCREEN_WIDTH / 2 - m_vPlaySpace.x / 2, Graphics::SCREEN_HEIGHT / 2 - m_vPlaySpace.y / 2);
	vTempPosArr.y -= m_iTextureSize;

	Vector2 m_vPlayerArrPos = m_vPlayerPos - vTempPosArr;

	//level index values are ArrPos values divided by texture size, Axis reversed
	m_iLevelLayoutIndexX = static_cast<int>(m_vPlayerArrPos.y / m_iTextureSize);
	m_iLevelLayoutIndexY = static_cast<int>(m_vPlayerArrPos.x / m_iTextureSize);

	std::string returnValue = "";

	if (m_iCheckMode == 1) //checking for spikes
	{
		m_bDead = false;

		for (int index = 0; index < m_iNumOfSpikes - 1; index++)
		{
			if (
				m_iLevelLayoutIndexX >= 0 && m_iLevelLayoutIndexY >= 0 &&
				m_iLevelLayoutIndexX < 29 && m_iLevelLayoutIndexY < 29 &&
				m_iLevelLayoutIndexX <= Levels::m_iLevelWidth && m_iLevelLayoutIndexY <= Levels::m_iLevelDepth
				)
			{
				if (
					//top
					m_lLevels->m_sLevelLayout[m_iLevelLayoutIndexX - 1][m_iLevelLayoutIndexY + 1] == m_sSpikes[index] ||

					//middle left
					m_lLevels->m_sLevelLayout[m_iLevelLayoutIndexX][m_iLevelLayoutIndexY] == m_sSpikes[index] ||
					m_lLevels->m_sLevelLayout[m_iLevelLayoutIndexX][m_iLevelLayoutIndexY + 1] == m_sSpikes[index] ||
					m_lLevels->m_sLevelLayout[m_iLevelLayoutIndexX][m_iLevelLayoutIndexY + 2] == m_sSpikes[index] ||

					//middle right
					m_lLevels->m_sLevelLayout[m_iLevelLayoutIndexX + 1][m_iLevelLayoutIndexY] == m_sSpikes[index] ||
					m_lLevels->m_sLevelLayout[m_iLevelLayoutIndexX + 1][m_iLevelLayoutIndexY + 1] == m_sSpikes[index] ||
					m_lLevels->m_sLevelLayout[m_iLevelLayoutIndexX + 1][m_iLevelLayoutIndexY + 2] == m_sSpikes[index] ||

					//bottom
					m_lLevels->m_sLevelLayout[m_iLevelLayoutIndexX + 2][m_iLevelLayoutIndexY + 1] == m_sSpikes[index]
					)
				{
					m_bDead = true;
					return 1;
				}
			}
		}
	}
	else if (m_iCheckMode == 2) //checking for normal blocks
	{
		m_bCollidedUp = false;
		m_bCollidedDown = false;
		m_bCollidedLeft = false;
		m_bCollidedRight = false;

		m_bCollidedTopLeft = false;
		m_bCollidedBottomLeft = false;
		m_bCollidedTopRight = false;
		m_bCollidedBottomRight = false;

		for (int index = 0; index < m_iNumOfBlocks - 1; index++)
		{
			if (m_iLevelLayoutIndexX >= 0 && m_iLevelLayoutIndexY >= 0 && //player will not collide if on the outer most layer, but will only be able to touch
				m_iLevelLayoutIndexX < 29 && m_iLevelLayoutIndexY < 29 && //the outer most layer when hitting the teleport area, so will not affect anything
				m_iLevelLayoutIndexX <= Levels::m_iLevelWidth && m_iLevelLayoutIndexY <= Levels::m_iLevelDepth)
			{
				//top left
				if (m_lLevels->m_sLevelLayout[m_iLevelLayoutIndexX - 1][m_iLevelLayoutIndexY] == m_sBlocks[index]) m_bCollidedTopLeft = true;
				//top
				if (m_lLevels->m_sLevelLayout[m_iLevelLayoutIndexX - 1][m_iLevelLayoutIndexY + 1] == m_sBlocks[index]) m_bCollidedUp = true;
				//top right
				if (m_lLevels->m_sLevelLayout[m_iLevelLayoutIndexX - 1][m_iLevelLayoutIndexY + 2] == m_sBlocks[index]) m_bCollidedTopRight = true;
				
				//middle left
				if (m_lLevels->m_sLevelLayout[m_iLevelLayoutIndexX][m_iLevelLayoutIndexY] == m_sBlocks[index] ||
					m_lLevels->m_sLevelLayout[m_iLevelLayoutIndexX + 1][m_iLevelLayoutIndexY] == m_sBlocks[index]) m_bCollidedLeft = true;
				//middle right
				if (m_lLevels->m_sLevelLayout[m_iLevelLayoutIndexX][m_iLevelLayoutIndexY + 2] == m_sBlocks[index] ||
					m_lLevels->m_sLevelLayout[m_iLevelLayoutIndexX + 1][m_iLevelLayoutIndexY + 2] == m_sBlocks[index]) m_bCollidedRight = true;

				//bottom left
				if (m_lLevels->m_sLevelLayout[m_iLevelLayoutIndexX + 2][m_iLevelLayoutIndexY] == m_sBlocks[index]) m_bCollidedBottomLeft = true;
				//bottom
				if (m_lLevels->m_sLevelLayout[m_iLevelLayoutIndexX + 2][m_iLevelLayoutIndexY + 1] == m_sBlocks[index]) m_bCollidedDown = true;
				//bottom right
				if (m_lLevels->m_sLevelLayout[m_iLevelLayoutIndexX + 2][m_iLevelLayoutIndexY + 2] == m_sBlocks[index]) m_bCollidedBottomRight = true;
			}
		}
	}
	else if (m_iCheckMode == 3)
	{
		if (m_bVerticalLevelChangerNext) //vertical next
		{
			if (m_iLevelLayoutIndexY == m_vLevelNext.x && (m_iLevelLayoutIndexX >= m_vLevelNext.y && m_iLevelLayoutIndexX <= m_vLevelNext.y + 4) ||
				m_iLevelLayoutIndexY == m_vLevelNext.x && (m_iLevelLayoutIndexX + 2 >= m_vLevelNext.y && m_iLevelLayoutIndexX + 2 <= m_vLevelNext.y + 4))
			{
				return 3;
			}
		}
		else if (!m_bVerticalLevelChangerNext)//horizontal next
		{
			if (m_iLevelLayoutIndexX == m_vLevelNext.y && (m_iLevelLayoutIndexY + 2 >= m_vLevelNext.x && m_iLevelLayoutIndexY + 2 <= m_vLevelNext.x + 4) ||
				m_iLevelLayoutIndexX == m_vLevelNext.y && (m_iLevelLayoutIndexY >= m_vLevelNext.x && m_iLevelLayoutIndexY <= m_vLevelNext.x + 4))
			{
				return 3;
			}
		}

		if (m_bVerticalLevelChangerExit) //vertical exit
		{
			if ((m_iLevelLayoutIndexX >= m_vLevelExit.y && m_iLevelLayoutIndexX <= m_vLevelExit.y + 4) && m_iLevelLayoutIndexY == m_vLevelExit.x ||
				(m_iLevelLayoutIndexX + 2 >= m_vLevelExit.y && m_iLevelLayoutIndexX + 2 <= m_vLevelExit.y + 4) && m_iLevelLayoutIndexY == m_vLevelExit.x)
			{
				return 4;
			}
		}
		else if (!m_bVerticalLevelChangerExit) //horizontal exit
		{
			if ((m_iLevelLayoutIndexY + 2 >= m_vLevelExit.x && m_iLevelLayoutIndexY + 2 <= m_vLevelExit.x + 4) && m_iLevelLayoutIndexX == m_vLevelExit.y ||
				(m_iLevelLayoutIndexY >= m_vLevelExit.x && m_iLevelLayoutIndexY <= m_vLevelExit.x + 4) && m_iLevelLayoutIndexX == m_vLevelExit.y)
			{
				return 4;
			}
		}
	}
	else if (m_iCheckMode == 4) // checking for special objects made using prototype pattern
	{
		if (m_iLevelLayoutIndexY <= m_vCheckpointLocation.x && m_iLevelLayoutIndexY + 3 >= m_vCheckpointLocation.x + 2.0f &&
			m_iLevelLayoutIndexX <= m_vCheckpointLocation.y && m_iLevelLayoutIndexX + 2 >= m_vCheckpointLocation.y + 2.0f)
		{
			return 5;
		}
	}

	if (m_bCollidedUp || m_bCollidedDown || m_bCollidedLeft || m_bCollidedRight ||
		m_bCollidedTopLeft || m_bCollidedTopRight || m_bCollidedBottomLeft || m_bCollidedBottomRight) return 2;

	return 0;
}

void CollisionManager::SetLevelChangers(Vector2 m_vNext, Vector2 m_vExit, bool m_vVLC)
{
	m_vLevelNext = m_vNext;
	m_vLevelExit = m_vExit;
	m_bVerticalLevelChangerNext = m_vVLC;
	m_bVerticalLevelChangerExit = m_vVLC;
}

void CollisionManager::SetSpecialObjectParams(Vector2 m_vCheckLocation, Vector2 m_vCheckSize, Vector2 m_vPlayerLocation, Vector2 m_vPlayerSize)
{
	m_vCheckpointLocation = m_vCheckLocation;
	m_vCheckpointSize = m_vCheckSize;
	m_vPlayerWorldLocation = m_vPlayerLocation;
	m_vPlayerWorldSize = m_vPlayerSize;
}

CollisionManager::CollisionManager()
{
	m_lLevels = Levels::Instance();
}

CollisionManager::~CollisionManager()
{
}
