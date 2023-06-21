#ifndef _INPUTMANAGER_H_
#define _INPUTMANAGER_H_

#include <SDL.h>
#include <string>
#include "MathUtility.h"

class InputManager
{
private:
	static InputManager* m_sInstance;

	Uint8* m_iPreviousKeyboardState;
	const Uint8* m_iKeyboardState;

	int m_iKeyLength;

public:
	static InputManager* Instance();
	static void Release();

	bool KeyDown(SDL_Scancode scanCode);
	bool KeyPressed(SDL_Scancode scanCode);
	bool KeyReleased(SDL_Scancode scanCode);

	void UpdatePreviousInput();

private:
	InputManager();
	~InputManager();
};

#endif // !_INPUTMANAGER_H_
