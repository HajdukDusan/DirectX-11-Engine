#include "timerclass.h"


TimerClass::TimerClass()
{
}


TimerClass::TimerClass(const TimerClass& other)
{
}


TimerClass::~TimerClass()
{
}

bool TimerClass::Initialize()
{
	// Check to see if this system supports high performance timers.
	QueryPerformanceFrequency((LARGE_INTEGER*)&m_frequency);
	if (m_frequency == 0)
	{
		return false;
	}

	// Find out how many times the frequency counter ticks every millisecond.
	m_ticksPerMs = (float)(m_frequency / 1000);

	QueryPerformanceCounter((LARGE_INTEGER*)&m_startTime);

	return true;
}


//called every loop execution by the main program
void TimerClass::Frame()
{
	INT64 currentTime;
	float timeDifference;


	QueryPerformanceCounter((LARGE_INTEGER*)&currentTime);

	timeDifference = (float)(currentTime - m_startTime);

	m_frameTime = timeDifference / m_ticksPerMs;

	m_startTime = currentTime;

	return;
}

void TimerClass::Start()
{
	QueryPerformanceCounter((LARGE_INTEGER*)&m_timerStart);
}

float TimerClass::End()
{
	INT64 currentTime;

	// get current time
	QueryPerformanceCounter((LARGE_INTEGER*)&currentTime);

	// get the elapsed time and divide by ticks
	return ((float)(currentTime - m_timerStart)) / m_ticksPerMs;
}

// most recent frame time calculated
float TimerClass::GetTime()
{
	return m_frameTime;
}