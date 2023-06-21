#include "Colors.h"

Colors* Colors::m_sInstance = NULL;

Colors* Colors::Instance() {

	if (m_sInstance == NULL)
	{
		m_sInstance = new Colors();
	}

	return m_sInstance;
}

void Colors::Release()
{
	delete m_sInstance;
	m_sInstance = NULL;
}

Colors::Colors()
{

}

Colors::~Colors()
{

}