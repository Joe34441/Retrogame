#ifndef _TIMER_H_
#define _TIMER_H_

#include <SDL.h>

class Timer
{
private:
	static Timer* m_sInstance;

	unsigned int m_uiStartTicks;
	unsigned int m_uiElapsedTicks;

	float m_fDeltaTime;
	float m_fTimeScale;

public:
	static Timer* Instance();
	static void Release();
	float DeltaTime();

	void SetTimeScale(float a_fScale);
	float GetTimeScale();

	void Update();
	void Reset();

private:
	Timer();
	~Timer();
};

#endif // !_TIMER_H_

