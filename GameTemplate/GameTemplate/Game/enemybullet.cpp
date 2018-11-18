#include "stdafx.h"
#include "enemybullet.h"


enemybullet::enemybullet(int No, const char* obj_name) : GameObject(No, obj_name)
{
}


enemybullet::~enemybullet()
{
}

bool enemybullet::Start()
{
	m_tama.Init(L"Assets/modelData/kyutai.cmo");
	//m_enemy = game_obj->FindGO<Enemy>("enemy");
	tamadir = m_enemy->Getforward();
	bulletpos = m_enemy->Getpos();
	bulletspeed = m_enemy->Getmovespeed().Length() + 10000.0f;
	bulletpos = m_enemy->Getpos() + m_enemy->Getforward()*500.0f;
	return true;
}

void enemybullet::Update()
{
	if (game_obj->FindGO(m_enemy)==NULL)
	{
		game_obj->DeleteGO(this);
	}
	bulletpos += tamadir * (bulletspeed / 60.0f);
	m_tama.UpdateWorldMatrix(bulletpos, CQuaternion::Identity(), {0.05f,0.05f,0.05f});
}

void enemybullet::Draw()
{
	m_tama.Draw(
		g_camera3D.GetViewMatrix(),
		g_camera3D.GetProjectionMatrix()
	);
}