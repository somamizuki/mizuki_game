#pragma once
#include "level/Level.h"
#include "Player.h"
#include"m_camera.h"
#include"Enemy.h"
#include"Light/CDirectionLight.h"
#include"Light/CPointLight.h"
#include"graphics/sky.h"
#include "Game.h"
class Class_of_NewGO:public GameObject
{
public:
	Class_of_NewGO(int No, const char* obj_name);
	~Class_of_NewGO();
	bool Start();				//スタート関数
	void Update();								//アップデート関数
	void Draw();								//描画関数
	void OnDestroy();
	std::vector<Enemy*>& GetEnemy()				//エネミーの配列を渡す
	{
		return *&m_enemy;
	}

	CSoundSource* GetHitSE()
	{
		return &m_HitSE;
	}
	CSoundEngine* GetSoundEngine()
	{
		return &m_soundEngine;
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


private:
	CSoundEngine m_soundEngine;				//サウンドエンジン。
	CSoundSource m_bgm;						//BGM
	CSoundSource m_HitSE;						//BGM
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

	bool gameClear = false;		//クリアしたかどうかのフラグ

	CVector3 pos;
};

