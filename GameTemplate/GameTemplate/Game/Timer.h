#pragma once
#include "Font.h"
class Timer//:public GameObject
{
public:
	Timer();
	~Timer();
	void Update();
	void Draw();
	void Stop()
	{
		StopTimer = true;
	}
	void Start()
	{
		StopTimer = false;
	}
	int GetMIN()
	{
		return m_minits;
	}
	float GetSEC()
	{
		return m_seconds;
	}
	bool IsTIMEUP()
	{
		return TimeUP;
	}

private:
	Font m_font;
	bool StopTimer = false;
	bool TimeUP = false;
	float m_seconds = 30.0f;
	int m_minits = 1;
};

