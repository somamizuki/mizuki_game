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
	tamadir = m_enemy->GetForward();
	speed = m_enemy->GetMoveSpeed().Length() + bulletspeed;
	bulletpos = m_enemy->GetPosition() + tamadir * 500.0f;
	return true;
}

void enemybullet::Update()
{
	if (m_enemy->GetDeath_f())
	{
		game_obj->DeleteGO(this);
	}
	bulletpos += tamadir * (speed*(1.0f / 60.0f));
	m_tama.UpdateWorldMatrix(bulletpos, CQuaternion::Identity(), {0.05f,0.05f,0.05f});
}

void enemybullet::Draw()
{
	m_tama.Draw(
		Diffuse,
		g_camera3D.GetViewMatrix(),
		g_camera3D.GetProjectionMatrix()
	);
}