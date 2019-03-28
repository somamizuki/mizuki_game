#pragma once
class Result
{
public:
	/// <summary>
	/// コンストラクタ
	/// </summary>
	Result();
	/// <summary>
	/// デストラクタ
	/// </summary>
	~Result();
	/// <summary>
	/// 初期化関数
	/// </summary>
	void Init();
	/// <summary>
	/// アップデート関数
	/// </summary>
	void Update();
	/// <summary>
	/// 描画関数
	/// </summary>
	void Draw();
	/// <summary>
	/// エネミーが死んだ数をセット
	/// </summary>
	void SetKnockDownEnemySUM()
	{
		KnockDownEnemySUM++;
	}
	/// <summary>
	/// 残りHPをセット
	/// </summary>
	/// <param name="HP"></param>
	void SetRemHP(int HP)
	{
		RemHP = HP;
	}
	/// <summary>
	/// 残り分をセット
	/// </summary>
	/// <param name="Min">分(int)</param>
	void SetRemMIN(int Min)
	{
		RemMIN = Min;
	}
	/// <summary>
	/// 残り秒をセット
	/// </summary>
	/// <param name="Sec">秒(float)</param>
	void SetRemSEC(float Sec)
	{
		RemSEC = Sec;
	}
	/// <summary>
	/// ゲームクリアフラグをセット
	/// </summary>
	/// <param name="flag">bool</param>
	void SetGameClear(bool flag)
	{
		GameClear = flag;
		if (GameClear)
		{
			ClearBonus = 100;
		}
	}
	/// <summary>
	/// タイムアップフラグをセット
	/// </summary>
	/// <param name="timeup">bool</param>
	void SetTimeUP(bool timeup)
	{
		isTimeUP = timeup;
	}
private:
	Font m_font[7];					//フォント
	int KnockDownEnemySUM = 0;		//エネミーが死んだ数をセット
	int RemHP = 0;					//残りのHPをセット
	int RemMIN = 0;					//残りの分をセット
	float RemSEC = 0.0f;			//残りの秒
	bool GameClear = false;			//ゲームクリアフラグ
	bool isTimeUP = false;			//タイムアップフラグ
	int ClearBonus = 0;				//クリアボーナス
	int ResultPoint = 0;			//合計得点
};

