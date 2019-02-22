#include "stdafx.h"

#include "Game.h"
#include "Class_of_NewGO.h"


Game::Game(int No, char* obj_name) :GameObject(No, obj_name)
{
}


Game::~Game()
{
}

bool Game::Start()
{
	g_graphicsEngine->SetShadowMap(&shadowMap);
	gamestart = new game_start(0, "game_start");
	
	

	return true;
}

void Game::Update()
{
	
	
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
			gamestart=new game_start(0, "game_start");

		}
	}
	

	
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
