#include "stdafx.h"
#include "system/system.h"
#include "level/Level.h"
#include "GameObject/GameObjectManajer.h"
#include "Player.h"
#include "Class_of_NewGO.h"

///////////////////////////////////////////////////////////////////
// ウィンドウプログラムのメイン関数。
///////////////////////////////////////////////////////////////////

GameObjectManajer* game_obj;
int WINAPI wWinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPWSTR lpCmdLine, int nCmdShow)
{
	//ゲームの初期化。
	InitGame(hInstance, hPrevInstance, lpCmdLine, nCmdShow, "Game");

	//カメラを初期化。
	/*g_camera3D.SetPosition({ 0.0f, 100.0f, 300.0f });
	g_camera3D.SetTarget({ 0.0f, 100.0f, 0.0f });
	g_camera3D.SetFar(10000.0f);*/

	game_obj = new GameObjectManajer;

	Class_of_NewGO *newObject = new Class_of_NewGO(0,"newObject");

	

	
	
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
		game_obj->Execute();

		
		//描画終了。
		g_graphicsEngine->EndRender();
	}

}