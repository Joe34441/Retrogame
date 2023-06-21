#ifndef _SPECIALOBJECTS_H_
#define _SPECIALOBJECTS_H_

#include <string>

class SpecialObjects
{
protected:
	std::string m_sObjectPath = "";
	std::string m_sObjectName = "";
	float m_fHeight = 0.0f;
	float m_fWidth = 0.0f;
	float m_fXPos = 0.0f;
	float m_fYPos = 0.0f;
	float m_fRotation = 0.0f;

public:
	virtual SpecialObjects* clone() = 0;

	std::string GetPath()
	{
		return m_sObjectPath;
	}

	std::string GetName()
	{
		return m_sObjectName;
	}

	float GetHeight()
	{
		return m_fHeight;
	}

	float GetWidth()
	{
		return m_fWidth;
	}

	float GetXPos()
	{
		return m_fXPos;
	}

	float GetYPos()
	{
		return m_fYPos;
	}

	float GetRotation()
	{
		return m_fRotation;
	}
};

class HorizontalMover : public SpecialObjects
{
public:
	HorizontalMover(std::string name, float width, float height, float xPos, float yPos, float rotation)
	{
		m_sObjectPath = "Sprites/Foreground objects/Blocks/horizontalmover.png";
		m_sObjectName = name;
		m_fWidth = width;
		m_fHeight = height;
		m_fXPos = xPos;
		m_fYPos = yPos;
		m_fRotation = rotation;
	}

	SpecialObjects* clone()
	{
		return new HorizontalMover(*this);
	}
};

class VerticalMover : public SpecialObjects
{
public:
	VerticalMover(std::string name, float width, float height, float xPos, float yPos, float rotation)
	{
		m_sObjectPath = "Sprites/Foreground objects/Blocks/verticalmover.png";
		m_sObjectName = name;
		m_fWidth = width;
		m_fHeight = height;
		m_fXPos = xPos;
		m_fYPos = yPos;
		m_fRotation = rotation;
	}

	SpecialObjects* clone()
	{
		return new VerticalMover(*this);
	}
};

class TrapBlock : public SpecialObjects
{
public:
	TrapBlock(std::string name, float width, float height, float xPos, float yPos, float rotation)
	{
		m_sObjectPath = "Sprites/Foreground objects/Blocks/trap1.png";
		m_sObjectName = name;
		m_fWidth = width;
		m_fHeight = height;
		m_fXPos = xPos;
		m_fYPos = yPos;
		m_fRotation = rotation;
	}

	SpecialObjects* clone()
	{
		return new TrapBlock(*this);
	}
};

class GravityBeam : public SpecialObjects
{
public:
	GravityBeam(std::string name, float width, float height, float xPos, float yPos, float rotation)
	{
		m_sObjectPath = "Sprites/Foreground objects/Blocks/gravitybeam2.png";
		m_sObjectName = name;
		m_fWidth = width;
		m_fHeight = height;
		m_fXPos = xPos;
		m_fYPos = yPos;
		m_fRotation = rotation;
	}

	SpecialObjects* clone()
	{
		return new GravityBeam(*this);
	}
};

class Checkpoint : public SpecialObjects
{
public:
	Checkpoint(std::string name, float width, float height, float xPos, float yPos, float rotation)
	{
		m_sObjectPath = "Sprites/Special/Checkpoints/checkpointinactive.png";
		m_sObjectName = name;
		m_fWidth = 45;
		m_fHeight = 65;
		m_fXPos = xPos;
		m_fYPos = yPos;
		m_fRotation = rotation;

	}

	SpecialObjects* clone()
	{
		return new Checkpoint(*this);
	}
};

class SpecialObjectsFactory
{
	SpecialObjects* HoriMover;
	SpecialObjects* VertMover;
	SpecialObjects* GravBeam;
	SpecialObjects* Trap;
	SpecialObjects* Check;

public:
	void InitializeHorizontal(float width, float height, float xPos, float yPos, float rotation)
	{
		HoriMover = new HorizontalMover("Horizontal Mover", width, height, xPos, yPos, rotation);
	}

	void InitializeVertical(float width, float height, float xPos, float yPos, float rotation)
	{
		VertMover = new VerticalMover("Vertical Mover", width, height, xPos, yPos, rotation);
	}

	void InitializeGravBeam(float width, float height, float xPos, float yPos, float rotation)
	{
		GravBeam = new GravityBeam("Gravity Beam", width, height, xPos, yPos, rotation);
	}

	void InitializeTrapBlock(float width, float height, float xPos, float yPos, float rotation)
	{
		Trap = new TrapBlock("Trap", width, height, xPos, yPos, rotation);
	}

	void InitializeCheckpoint(float width, float height, float xPos, float yPos, float rotation)
	{
		Check = new Checkpoint("Check", width, height, xPos, yPos, rotation);
	}

	SpecialObjects* GetHoriMover()
	{
		return HoriMover->clone();
	}

	SpecialObjects* GetVertMover()
	{
		return VertMover->clone();
	}

	SpecialObjects* GetGravBeam()
	{
		return GravBeam->clone();
	}

	SpecialObjects* GetTrap()
	{
		return Trap->clone();
	}

	SpecialObjects* GetCheck()
	{
		return Check->clone();
	}
};

#endif