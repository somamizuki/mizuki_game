#include "stdafx.h"
#include "Timer.h"


Timer::Timer()
{
}


Timer::~Timer()
{
}

void Timer::Update()
{
	if (StopTimer)
	{
		m_seconds = max(0.0f, m_seconds-1.0f*deltaTime);
	}
	if (m_minits>0&&m_seconds <= 0.0f)
	{
		m_seconds = 60.0f;
		m_minits -= 1;
	}
}

void Timer::Draw()
{
	wchar_t font[256];
	swprintf(font,L"%d.%05.2f", m_minits, m_seconds );
	m_font.BeginDraw();
	m_font.Draw(font, { -920.0f,500.0f }, {0.0f,1.0f,0.0f,0.5f},0.0f,0.2f);
	m_font.EndDraw();
}
