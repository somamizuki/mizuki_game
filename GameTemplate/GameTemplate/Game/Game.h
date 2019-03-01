#pragma once
#include "game_start.h"
class Class_of_NewGO;
class Game:public GameObject
{
public:
	Game(int No, char* obj_name);
	~Game();
	bool Start();
	void Update();
	void Draw();
	void UIDraw();								//UIとかの描画
	void OnDestroy();
private:
	enum gamestate {
		title,
		start,
		stop,
		end
	};
	gamestate state = end;
	CSoundEngine m_soundEngine;				//サウンドエンジン。
	Class_of_NewGO *newObject = nullptr;
	game_start* gamestart = nullptr;
	ShadowMap shadowMap;
};

