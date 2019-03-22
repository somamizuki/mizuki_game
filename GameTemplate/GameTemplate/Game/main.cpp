#include "stdafx.h"
#include "system/system.h"
#include "level/Level.h"
#include "GameObject/GameObjectManajer.h"
#include "Player.h"
#include"Game.h"


///////////////////////////////////////////////////////////////////
// ウィンドウプログラムのメイン関数。
///////////////////////////////////////////////////////////////////
GameObjectManajer* game_obj;
LightManager *Light_obj;
int WINAPI wWinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPWSTR lpCmdLine, int nCmdShow)
{
	//ゲームの初期化。
	InitGame(hInstance, hPrevInstance, lpCmdLine, nCmdShow, "Game");

	game_obj = new GameObjectManajer;
	Light_obj = new LightManager;
	Game game(0, "game");


	//::_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
	//_CrtSetReportMode(_CRT_ERROR, _CRTDBG_MODE_DEBUG);
	//::_CrtSetReportMode(_CRT_ERROR, _CRTDBG_MODE_DEBUG);
	//ゲームループ。
	while (DispatchWindowMessage() == true)
	{
		//描画開始。
		g_graphicsEngine->BegineRender();
		//ゲームパッドの更新。	
		for (auto& pad : g_pad) {
			pad.Update();
		}
		//物理エンジンの更新。
		g_physics.Update();
		Light_obj->LightExecute();
		game_obj->Execute();



		//描画終了。
		g_graphicsEngine->EndRender();
	}
	delete game_obj;
	delete Light_obj;
	delete g_graphicsEngine;
}