#pragma once
#include "level/Level.h"
#include "Player.h"
#include"GameCamera.h"
#include"Enemy.h"
#include"Light/CDirectionLight.h"
#include"Light/CPointLight.h"
#include"graphics/sky.h"
#include "Timer.h"
#include "Result.h"
#include "Game.h"
#include "Effect.h"
#include "BossEnemy.h"

class Class_of_NewGO :public GameObject
{
public:
	/// <summary>
	/// クラスオブニューゴーのコンストラクタ
	/// </summary>
	/// <param name="No">優先度</param>
	/// <param name="obj_name">名前</param>
	Class_of_NewGO(int No, const char* obj_name);
	/// <summary>
	/// クラスオブニューゴーのコンストラクタ
	/// </summary>
	~Class_of_NewGO();
	/// <summary>
	/// スタート関数
	/// </summary>
	bool Start();
	/// <summary>
	/// アップデート関数
	/// </summary>
	void Update();
	/// <summary>
	/// 描画関数
	/// </summary>
	void Draw();
	/// <summary>
	/// エフェクト描画関数
	/// </summary>
	void EffectDraw();
	/// <summary>
	/// UI描画関数
	/// </summary>
	void UIDraw();
	/// <summary>
	/// Delete時に呼ばれる関数
	/// </summary>
	void OnDestroy();
	/// <summary>
	/// エネミーの配列のゲッター
	/// </summary>
	/// <returns>エネミーの配列</returns>
	std::vector<Enemy*>& GetEnemy()				//エネミーの配列を渡す
	{
		return *&m_enemy;
	}
	/// <summary>
	/// HitSEのゲッター
	/// </summary>
	/// <returns>CSoundSource</returns>
	CSoundSource* GetHitSE()
	{
		return &m_hitSE;
	}

	/// <summary>
	/// lockonSEのゲッター
	/// </summary>
	/// <returns>CSoundSource</returns>
	CSoundSource* GetLockOnSE()
	{
		return &m_lockonSE;
	}
	/// <summary>
	/// fireSEのゲッター
	/// </summary>
	/// <returns>CSoundSource</returns>
	CSoundSource* GetFireSE()
	{
		return &m_fireSE;
	}
	/// <summary>
	/// ゲームクリアフラグのゲッター
	/// </summary>
	/// <returns>bool</returns>
	bool GameClear()
	{
		return m_gameclearflag;
	}
	/// <summary>
	/// 使用していない
	/// </summary>
	/// <param name="game"></param>
	void SetGameMain(Game* game)
	{
		m_game = game;
	}
	/// <summary>
	/// Resultのゲッター
	/// </summary>
	/// <returns>Result*</returns>
	Result* GetResult()
	{
		return &m_result;
	}
	/// <summary>
	/// Effectのゲッター
	/// </summary>
	/// <returns>Effect*</returns>
	Effect* GetEffect()
	{
		return &m_effect;
	}
	/// <summary>
	/// ボスのゲッター
	/// </summary>
	/// <returns>BossEnemy*</returns>
	BossEnemy* GetBossEnemy()
	{
		return m_bossenemy;
	}
	/// <summary>
	/// WaveCounterのゲッター
	/// </summary>
	/// <returns>int</returns>
	int GetWaveCounter()
	{
		return m_wavecounter;
	}
private:

	CSoundSource			m_bgm;									//BGM
	CSoundSource			m_bgmendwave;							//最終Wave用のBGM
	CSoundSource			m_hitSE;								//ミサイルが当たった時のSE
	CSoundSource			m_lockonSE;								//ロックオン時のSE
	CSoundSource			m_fireSE;								//ミサイル発射時のSE


	Player*					m_player = nullptr;						//プレイヤーのポインター
	std::vector<Enemy*>		m_enemy;								//エネミーの配列
	Level					m_level;								//レベルのインスタンス
	CDirectionLight			m_dirlig;								//ディレクションライトのインスタンス
	CPointLight				m_pointlig;								//ポイントライト
	GameCamera*				m_camera = nullptr;						//カメラのポインター
	sky*					m_cubemap = nullptr;					//キューブマップクラスのポインター
	SkinModel				m_sun;									//恒星のスキンモデル
	CVector3				m_lightcameradir = CVector3::Zero();	//シャドウマップ用カメラのディレクション
	SPointLight				m_spointlight;							//ポイントライトの構造体
	Game*					m_game = nullptr;						//Gameクラスのポインター
	Timer					m_timer;								//Timerクラスのポインター
	bool					m_gameclearflag = false;				//クリアしたかどうかのフラグ
	int						m_wavecounter = 1;
	Result					m_result;								//Resultクラスのインスタンス
	bool					m_resultdrawflag = false;				//リザルトを描画するフラグ
	CVector3				m_playerposition;						//プレイヤーのポジション
	Effect					m_effect;								//エフェクトのインスタンス
	BossEnemy*				m_bossenemy = nullptr;					//ボスのポインター
};

