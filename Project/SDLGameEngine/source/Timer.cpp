#include "..\include\Timer.h"

Timer* Timer::m_sInstance = NULL;

Timer* Timer::Instance()
{
	if (m_sInstance == NULL)
	{
		m_sInstance = new Timer();
	}
	return m_sInstance;
}

void Timer::Release()
{
	delete m_sInstance;
	m_sInstance = NULL;
}

float Timer::DeltaTime()
{
	return m_fDeltaTime;
}

void Timer::SetTimeScale(float a_fScale)
{
	m_fTimeScale = a_fScale;
}

float Timer::GetTimeScale()
{
	return m_fTimeScale;
}

void Timer::Update()
{
	m_uiElapsedTicks = SDL_GetTicks() - m_uiStartTicks;
	m_fDeltaTime = m_uiElapsedTicks * 0.001f; //convert from ms
}

void Timer::Reset()
{
	m_uiStartTicks = SDL_GetTicks();
	m_uiElapsedTicks = 0;
	m_fDeltaTime = 0.0f;
}

Timer::Timer()
{
	Reset();
	m_fTimeScale = 1.0f;
}

Timer::~Timer()
{
}
