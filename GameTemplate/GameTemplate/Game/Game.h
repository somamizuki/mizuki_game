#pragma once
#include "game_start.h"
class Class_of_NewGO;
class Game:public GameObject
{
public:
	/// <summary>
	/// コンストラクタ
	/// </summary>
	/// <param name="No"></param>
	/// <param name="obj_name"></param>
	Game(int No, char* obj_name);
	~Game();
	/// <summary>
	/// スタート関数
	/// </summary>
	/// <returns>bool</returns>
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
	/// UI描画関数
	/// </summary>
	void UIDraw();
	/// <summary>
	/// Delete時に呼ばれる関数
	/// </summary>
	void OnDestroy();
private:
	/*ゲームのステート*/
	enum gamestate {
		title,
		start,
		stop,
		end
	};
	gamestate state = end;					//ゲームステート
	CSoundEngine m_soundEngine;				//サウンドエンジン。
	Class_of_NewGO *newObject = nullptr;	//Class_of_NewGOのポインター
	game_start* gamestart = nullptr;		//game_startのポインター
	ShadowMap shadowMap;					//ShadowMapのインスタンス
	bool stopflag = false;					//停止フラグ
};

