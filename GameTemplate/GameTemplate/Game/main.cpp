#include "stdafx.h"
#include "system/system.h"
#include "level/Level.h"
#include "GameObject/GameObjectManajer.h"
#include "Player.h"
#include"Game.h"


///////////////////////////////////////////////////////////////////
// �E�B���h�E�v���O�����̃��C���֐��B
///////////////////////////////////////////////////////////////////
GameObjectManajer* game_obj;
LightManager *Light_obj;
int WINAPI wWinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPWSTR lpCmdLine, int nCmdShow)
{
	//�Q�[���̏������B
	InitGame(hInstance, hPrevInstance, lpCmdLine, nCmdShow, "Game");

	game_obj = new GameObjectManajer;
	Light_obj = new LightManager;
	Game game(0, "game");


	//::_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
	//_CrtSetReportMode(_CRT_ERROR, _CRTDBG_MODE_DEBUG);
	//::_CrtSetReportMode(_CRT_ERROR, _CRTDBG_MODE_DEBUG);
	//�Q�[�����[�v�B
	while (DispatchWindowMessage() == true)
	{
		//�`��J�n�B
		g_graphicsEngine->BegineRender();
		//�Q�[���p�b�h�̍X�V�B	
		for (auto& pad : g_pad) {
			pad.Update();
		}
		//�����G���W���̍X�V�B
		g_physics.Update();
		Light_obj->LightExecute();
		game_obj->Execute();



		//�`��I���B
		g_graphicsEngine->EndRender();
	}
	delete game_obj;
	delete Light_obj;
	delete g_graphicsEngine;
}