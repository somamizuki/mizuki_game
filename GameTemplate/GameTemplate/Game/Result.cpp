#include "stdafx.h"
#include "Result.h"

Result::Result()
{
}


Result::~Result()
{
}

void Result::Init()
{
}

void Result::Update()
{
}

void Result::Draw()
{
	wchar_t font[256];
	m_font[0].BeginDraw();
	swprintf(font, L"KILL_ENEMY          %d", KnockDownEnemySUM);
	m_font[0].Draw(font, { -700.0f,300.0f }, { 0.0f,1.0f,0.0f,0.5f }, 0.0f, 0.4f);
	m_font[0].EndDraw();
	m_font[1].BeginDraw();
	swprintf(font, L"REMAINING_HP     %d", RemHP);
	m_font[1].Draw(font, { -700.0f,200.0f }, { 0.0f,1.0f,0.0f,0.5f }, 0.0f, 0.4f);
	m_font[1].EndDraw();
	m_font[2].BeginDraw();
	swprintf(font, L"REMAINING_MIN   %d", RemMIN);
	m_font[2].Draw(font, { -700.0f,100.0f }, { 0.0f,1.0f,0.0f,0.5f }, 0.0f, 0.4f);
	m_font[2].EndDraw();
	m_font[3].BeginDraw();
	swprintf(font, L"REMAINING_SEC  %05.2f", RemSEC);
	m_font[3].Draw(font, { -700.0f,0.0f }, { 0.0f,1.0f,0.0f,0.5f }, 0.0f, 0.4f);
	m_font[3].EndDraw();
	m_font[4].BeginDraw();
	swprintf(font, L"CLEARBONUS         %d", ClearBonus);
	m_font[4].Draw(font, { -700.0f,-100.0f }, { 0.0f,1.0f,0.0f,0.5f }, 0.0f, 0.4f);
	m_font[4].EndDraw();
	int totalpoint = KnockDownEnemySUM + RemHP + (RemMIN * 60) + RemSEC + ClearBonus;
	m_font[5].BeginDraw();
	swprintf(font, L"TOTALPOINT          %d", totalpoint);
	m_font[5].Draw(font, { -700.0f,-200.0f }, { 0.0f,1.0f,0.0f,0.5f }, 0.0f, 0.4f);
	m_font[5].EndDraw();

	
}
