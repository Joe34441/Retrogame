#include "InputManager.h"

InputManager* InputManager::m_sInstance = NULL;

InputManager* InputManager::Instance()
{
	if (m_sInstance == NULL)
	{
		m_sInstance = new InputManager();
	}
	return m_sInstance;
}

void InputManager::Release()
{
	delete m_sInstance;
	m_sInstance = NULL;
}

bool InputManager::KeyDown(SDL_Scancode scanCode)
{
	return m_iKeyboardState[scanCode];
}

bool InputManager::KeyPressed(SDL_Scancode scanCode)
{
	return !m_iPreviousKeyboardState[scanCode] && m_iKeyboardState[scanCode];
}

bool InputManager::KeyReleased(SDL_Scancode scanCode)
{
	return m_iPreviousKeyboardState[scanCode] && !m_iKeyboardState[scanCode];
}

void InputManager::UpdatePreviousInput()
{
	memcpy(m_iPreviousKeyboardState, m_iKeyboardState, m_iKeyLength);
}

InputManager::InputManager()
{
	m_iKeyboardState = SDL_GetKeyboardState(&m_iKeyLength);
	m_iPreviousKeyboardState = new Uint8[m_iKeyLength];
	memcpy(m_iPreviousKeyboardState, m_iKeyboardState, m_iKeyLength);
}

InputManager::~InputManager()
{
	delete[] m_iPreviousKeyboardState;
	m_iPreviousKeyboardState = NULL;
}
