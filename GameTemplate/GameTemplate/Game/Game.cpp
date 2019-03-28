#include "stdafx.h"

#include "Game.h"
#include "Class_of_NewGO.h"


Game::Game(int No, char* obj_name) :GameObject(No, obj_name)
{
}


Game::~Game()
{
	m_soundEngine.Release();
}

bool Game::Start()
{
	g_graphicsEngine->SetShadowMap(&shadowMap);
	gamestart = new game_start(0, "game_start");
	m_soundEngine.Init();
	return true;
}

void Game::Update()
{
	//デバッグコード
	if (g_pad[0].IsTrigger(enButtonStart))
	{
		if (stopflag)
		{
			game_obj->alltomarunjanee();
			stopflag = false;
		}
		else
		{
			game_obj->allStop(this);
			stopflag = true;
			
		}
	}


	if (gamestart != nullptr)
	{
		if (gamestart->GetGameStartflag())
		{
			game_obj->DeleteGO(gamestart);
			gamestart = nullptr;
			newObject = new Class_of_NewGO(0, "newObject");
		}
	}
	if (newObject != nullptr)
	{
		if (newObject->GameClear())
		{
			game_obj->DeleteGO(newObject);
			newObject = nullptr;
			gamestart = new game_start(0, "game_start");
		}
	}
	m_soundEngine.Update();
}

void Game::Draw()
{


}

void Game::UIDraw()
{

}


void Game::OnDestroy()
{
}
