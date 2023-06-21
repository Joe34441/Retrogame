#ifndef _COLORS_H_
#define _COLORS_H_

#include <SDL_ttf.h>

class Colors
{
public:
	//white / black
	const SDL_Color White = { 255, 255 , 255 };
	const SDL_Color Black = { 0, 0, 0 };
	//rgb
	const SDL_Color Red = { 255, 0, 0 };
	const SDL_Color Green = { 0, 255, 0};
	const SDL_Color Blue = { 0, 0, 255};
	//light rgb
	const SDL_Color LightRed = { 255, 75, 75 };
	const SDL_Color LightGreen = { 125, 255, 125 };
	const SDL_Color LightBlue = { 60, 60, 255 };
	//dark rgb
	const SDL_Color DarkRed = { 140, 0, 0 };
	const SDL_Color DarkGreen = { 0, 140, 0 };
	const SDL_Color DarkBlue = { 0, 0, 140 };
	//common colors
	const SDL_Color Grey = { 55, 55, 55 };
	const SDL_Color Yellow = { 255, 255, 0 };
	const SDL_Color Orange = { 200, 65, 0 };
	const SDL_Color Brown = { 200, 100, 0 };
	const SDL_Color Purple = { 120, 0, 120 };
	const SDL_Color Cream = { 255, 240, 180 };
	const SDL_Color Gold = { 255, 190, 0 };


private:
	static Colors* m_sInstance;

public:
	static Colors* Instance();
	static void Release();

private:
	Colors();
	~Colors();
};



#endif