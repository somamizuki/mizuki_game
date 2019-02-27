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

private:
	Font m_font;
	bool StopTimer = false;
	float m_seconds = 60.0f;
	int m_minits = 2;
};

