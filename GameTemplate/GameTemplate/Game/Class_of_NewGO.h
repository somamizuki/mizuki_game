#pragma once
#include "level/Level.h"
#include "Player.h"
#include"m_camera.h"
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
	Class_of_NewGO(int No, const char* obj_name);
	~Class_of_NewGO();
	bool Start();				//スタート関数
	void Update();								//アップデート関数
	void Draw();								//描画関数
	void EffectDraw();			 //エフェクトの描画
	void UIDraw();
	void OnDestroy();
	std::vector<Enemy*>& GetEnemy()				//エネミーの配列を渡す
	{
		return *&m_enemy;
	}

	CSoundSource* GetHitSE()
	{
		return &m_HitSE;
	}


	CSoundSource* GetlockonSE()
	{
		return &m_lockonSE;
	}

	CSoundSource* GetfireSE()
	{
		return &m_fireSE;
	}

	bool GameClear()
	{
		return gameClear;
	}

	void SetGameMain(Game* game)
	{
		m_game = game;
	}
	Result* GetResult()
	{
		return &m_result;
	}

	Effect* GetEffect()
	{
		return &m_effect;
	}
	/*ボスのゲッター*/
	BossEnemy* GetBossEnemy()
	{
		return m_bossenemy;
	}
	int GetWaveCounter()
	{
		return WaveCounter;
	}
private:

	CSoundSource m_bgm;						//BGM
	CSoundSource m_bgmendwave;
	CSoundSource m_HitSE;
	CSoundSource m_lockonSE;
	CSoundSource m_fireSE;


	Player* player = nullptr;					//プレイヤーのポインター
	std::vector<Enemy*> m_enemy;				//エネミーの配列
	Level level;								//レベルのインスタンス
	CDirectionLight m_dirlig;					//ディレクションライトのインスタンス
	CPointLight m_pointlig;						//ポイントライト
	m_camera* camera = nullptr;					//カメラのポインター
	sky* map = nullptr;
	SkinModel Sun;
	CVector3 SCamDir = CVector3::Zero();
	SPointLight spoint;			//ポイントライトの構造体
	Game* m_game = nullptr;
	Timer m_timer;
	bool gameClear = false;		//クリアしたかどうかのフラグ
	int WaveCounter = 1;
	Result m_result;
	bool ResultDrawFlag = false;
	CVector3 pos;
	Effect m_effect;
	BossEnemy* m_bossenemy = nullptr;
};

