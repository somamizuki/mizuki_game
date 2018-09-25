#include "stdafx.h"
#include "system/system.h"
#include "level/Level.h"
#include "GameObject/GameObjectManajer.h"
#include "Player.h"
#include "Class_of_NewGO.h"

///////////////////////////////////////////////////////////////////
// �E�B���h�E�v���O�����̃��C���֐��B
///////////////////////////////////////////////////////////////////

GameObjectManajer* game_obj;
int WINAPI wWinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPWSTR lpCmdLine, int nCmdShow)
{
	//�Q�[���̏������B
	InitGame(hInstance, hPrevInstance, lpCmdLine, nCmdShow, "Game");

	//�J�������������B
	/*g_camera3D.SetPosition({ 0.0f, 100.0f, 300.0f });
	g_camera3D.SetTarget({ 0.0f, 100.0f, 0.0f });
	g_camera3D.SetFar(10000.0f);*/

	game_obj = new GameObjectManajer;

	Class_of_NewGO *newObject = new Class_of_NewGO(0,"newObject");

	

	
	
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
		game_obj->Execute();

		
		//�`��I���B
		g_graphicsEngine->EndRender();
	}

}