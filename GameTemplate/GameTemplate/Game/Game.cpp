#include "stdafx.h"
#include "Game.h"


Game::Game(int No, char* obj_name) :GameObject(No, obj_name)
{
}


Game::~Game()
{
}

bool Game::Start()
{
	shaderResource.CreateFromDDSTextureFromFile(L"Resource/sprite/menue.dds");
	m_sprite.InitScreen2D(shaderResource, 0.0f, 0.0f, 1.0f);
	return true;
}

void Game::Update()
{
	if (state == end && g_pad[0].IsTrigger(enButtonA))
	{
		newObject = new Class_of_NewGO(0, "newObject");
		state = start;
	}
	if (state == start && g_pad[0].IsTrigger(enButtonStart))
	{
		game_obj->allStop(this);
		
		state = stop;
	}
	if (state == stop)
	{
		if (g_pad[0].IsTrigger(enButtonA))
		{
			game_obj->DeleteGO(newObject);
			state = end;
		}
		if (g_pad[0].IsTrigger(enButtonB))
		{
			game_obj->alltomarunjanee();
			state = start;
		}
	}
}

void Game::Draw()
{
	
	
}

void Game::UIDraw()
{
	if (state == stop)
	{
		m_sprite.Draw(
			*g_graphicsEngine->GetD3DDeviceContext()
		);
	}
}