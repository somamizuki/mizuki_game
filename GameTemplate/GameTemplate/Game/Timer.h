#pragma once
#include "Font.h"
class Timer//:public GameObject
{
public:
	/// <summary>
	/// コンストラクタ
	/// </summary>
	Timer();
	/// <summary>
	/// デストラクタ
	/// </summary>
	~Timer();
	/// <summary>
	/// アップデート関数
	/// </summary>
	void Update();
	/// <summary>
	/// 描画関数
	/// </summary>
	void Draw();
	/// <summary>
	/// ストップ関数
	/// </summary>
	void Stop()
	{
		StopTimer = true;
	}
	/// <summary>
	/// スタート関数
	/// </summary>
	void Start()
	{
		StopTimer = false;
	}
	/// <summary>
	/// 分のゲッター
	/// </summary>
	/// <returns>int</returns>
	int GetMIN()
	{
		return m_minits;
	}
	/// <summary>
	/// 秒のゲッター
	/// </summary>
	/// <returns>float</returns>
	float GetSEC()
	{
		return m_seconds;
	}
	/// <summary>
	/// タイムアップした？
	/// </summary>
	/// <returns>bool</returns>
	bool IsTIMEUP()
	{
		return TimeUP;
	}

private:
	Font	m_font;					//フォント
	bool	StopTimer = false;		//タイマー停止フラグ
	bool	TimeUP = false;			//タイムアップフラグ
	float	m_seconds = 30.0f;		//秒
	int		m_minits = 1;			//分
};

