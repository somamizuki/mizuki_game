#pragma once
#include "level/Level.h"
#include "Player.h"
#include"m_camera.h"
#include"Enemy.h"
#include"Light/CDirectionLight.h"
#include"Light/CPointLight.h"
#include"graphics/sky.h"

class Class_of_NewGO:public GameObject
{
public:
	Class_of_NewGO(int No, const char* obj_name);
	~Class_of_NewGO();
	bool Start() { return true; }				//スタート関数
	void Update();								//アップデート関数
	void Draw();								//描画関数
	std::vector<Enemy*>& GetEnemy()				//エネミーの配列を渡す
	{
		return m_enemy;
	}

private:
	
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
};

