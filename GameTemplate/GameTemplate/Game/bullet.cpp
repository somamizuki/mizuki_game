#include "stdafx.h"
#include "bullet.h"



bullet::bullet(int No, const char* obj_name) : GameObject(No, obj_name)
{
}


bullet::~bullet()
{

}

bool bullet::Start()
{
	m_tama.Init(L"Assets/modelData/kyutai.cmo");
	m_player = game_obj->FindGO<Player>("player");
	CoN = game_obj->FindGO<Class_of_NewGO>("newObject");

	tamadir = m_player->Getforward();
	bulletpos = m_player->Getpos();
	bulletspeed = m_player->Get_PlayerMove().Length()+10000.0f;
	bulletpos = m_player->Getpos() + m_player->Getforward()*500.0f;
	return true;
}

void bullet::Update()
{
	bulletpos += tamadir * (bulletspeed*(1.0f / 60.0f));
	CVector3 e_to_b = CVector3::Zero();
	for (auto& enemy : CoN->GetEnemy())
	{
		e_to_b = bulletpos - enemy->Getpos();
		if (e_to_b.Length() < 300.0f)
		{
			game_obj->DeleteGO(enemy);
			CoN->GetEnemy().erase(std::remove(CoN->GetEnemy().begin(),
								CoN->GetEnemy().end(), enemy),
								CoN->GetEnemy().end());
			dead = true;
		}
	}
	m_tama.UpdateWorldMatrix(bulletpos, CQuaternion::Identity(), { 0.05f,0.05f,0.05f });
}

void bullet::Draw()
{
	m_tama.Draw(
		g_camera3D.GetViewMatrix(),
		g_camera3D.GetProjectionMatrix()
	);
}