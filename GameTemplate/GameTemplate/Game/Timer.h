#pragma once
class Timer//:public GameObject
{
public:
	Timer();
	~Timer();
	bool Start();
	void Update();
	void UIDraw();
private:
	bool StopTimer = false;
	float m_seconds = 0.0f;
	int m_minits = 0;
};

