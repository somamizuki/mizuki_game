#pragma once
class Result
{
public:
	Result();
	~Result();
	void Init();
	void Update();
	void Draw();
	void SetKnockDownEnemySUM()
	{
		KnockDownEnemySUM++;
	}
	void SetRemHP(int HP)
	{
		RemHP = HP;
	}
	void SetRemMIN(int Min)
	{
		RemMIN = Min;
	}
	void SetRemSEC(float Sec)
	{
		RemSEC = Sec;
	}
	void SetGameClear(bool flag)
	{
		GameClear = flag;
		if (GameClear)
		{
			ClearBonus = 100;
		}
	}
	void SetTimeUP(bool timeup)
	{
		isTimeUP = timeup;
	}
private:
	Font m_font[7];
	int KnockDownEnemySUM = 0;
	int RemHP = 0;
	int RemMIN = 0;
	float RemSEC = 0.0f;
	bool GameClear = false;
	bool isTimeUP = false;
	int ClearBonus = 0;
	int ResultPoint = 0;
};

