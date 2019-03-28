#include "stdafx.h"
#include "Player.h"
#include"Class_of_NewGO.h"
#include "GameCamera.h"
#include"math/kMath.h"

GameCamera::GameCamera(int No, char* obj_name) :GameObject(No, obj_name)
{
}


GameCamera::~GameCamera()
{
}

bool GameCamera::Start()
{
	player = game_obj->FindGO<Player>("player");
	player->AddMyPointer<Player, GameCamera>(&player, this);
	CoN = game_obj->FindGO<Class_of_NewGO>("newObject");
	CoN->AddMyPointer<Class_of_NewGO, GameCamera>(&CoN, this);

	camera_rite = player->GetRite();
	g_camera3D.SetFar(2000000.0f);
	g_camera3D.SetNear(1.0f);
	player_pos = player->GetPosition();
	camera_Target = player_pos + player->GetUp()*100.0f;
	camera_Pos = camera_Target - player->GetForward()*500.0f;

	target_to_pos = camera_Pos - camera_Target;
	camera_forward = target_to_pos * -1.0f;
	camera_forward.Normalize();
	camera_Up = player->GetUp();

	g_camera3D.SetPosition(camera_Pos);
	g_camera3D.SetTarget(camera_Target);
	g_camera3D.SetUp(camera_Up);

	return true;
}

void GameCamera::CameraMove()
{
	pad_Y = g_pad[0].GetLStickYF();
	pad_X = g_pad[0].GetLStickXF();
	rotYmax = pad_Y * 5.0f;
	rotXmax = pad_X * 10.0f;
	m_angleY += (rotYmax - m_angleY) * (1.0f / 15.0f);
	m_angleX += (rotXmax - m_angleX) * (1.0f / 15.0f);
	/*if (rotYmax > m_angleY || rotYmax < m_angleY)
	{
		m_angleY += (rotYmax - m_angleY)*(1.0f / 15.0f);
	}
	if (rotYmax < m_angleY)
	{
		m_angleY += (rotYmax - m_angleY)*(1.0f / 15.0f);
	}
	rotXmax = pad_X * 5.0f;
	if (rotXmax > m_angleX)
	{
		m_angleX += (rotXmax - m_angleX)*(1.0f / 15.0f);
	}
	if (rotXmax < m_angleX)
	{
		m_angleX += (rotXmax - m_angleX)*(1.0f / 15.0f);
	}*/


	/*rotXmax = (pad_X * 10.0f)*abs(pad_Y);
	if (rotXmax > m_angleX)
	{
		m_angleX += (rotXmax - m_angleX)*(1.0f / 10.0f);
	}
	if (rotXmax < m_angleX)
	{
		m_angleX += (rotXmax - m_angleX)*(1.0f / 10.0f);
	}*/



	camera_rite = player->GetRite();
	player_pos = player->GetPosition();
	camera_Target = player_pos + player->GetUp()*100.0f;
	if (g_pad[0].IsPress(enButtonRB2))
	{
		CamLen = min(600.0f, CamLen + 50.0f*(1.0f / 60.0f));
	}
	else
	{
		CamLen = max(500.0f, CamLen - 50.0f*(1.0f / 60.0f));
	}

	CVector3 vec = player->GetForward()*CamLen;
	CQuaternion rotY = CQuaternion::Identity();
	rotY.SetRotationDeg(player->GetRite(), -m_angleY);
	rotY.Multiply(vec);

	CQuaternion rotX = CQuaternion::Identity();
	rotX.SetRotationDeg(player->GetForward(), m_angleX);
	rotX.Multiply(camera_Up);

	if (g_pad[0].IsTrigger(enButtonLB2))
	{
		vec *= -1.0f;
	}
	camera_Pos = camera_Target - vec;
}

void GameCamera::bossfightCameraMove()
{
	/*pad_X = g_pad[0].GetLStickXF();
	rotXmax = pad_X * 10.0f;
	m_angleX += (rotXmax - m_angleX) * (1.0f / 15.0f);
	CQuaternion rotX = CQuaternion::Identity();
	rotX.SetRotationDeg(player->Getforward(), m_angleX);
	rotX.Multiply(camera_Up);*/

	camera_rite = player->GetRite();
	player_pos = player->GetPosition();
	camera_Target = player_pos + player->GetUp()*100.0f;
	CamLen = max(500.0f, CamLen - 50.0f*(1.0f / 60.0f));
	CVector3 vec = player->GetForward()*CamLen;
	camera_Pos = camera_Target - vec;
}

void GameCamera::Update()
{
	if (player != nullptr)
	{
		camera_Up = player->GetUp();
		if (CoN != nullptr)
		{
			if (CoN->GetWaveCounter() < 5)
			{
				CameraMove();
			}
			else
			{
				bossfightCameraMove();
			}

		}
	}


	target_to_pos = camera_Pos - camera_Target;
	camera_forward = target_to_pos * -1.0f;
	camera_forward.Normalize();



	ligParam ligp;
	ligp.eyepos = camera_Pos;
	ligp.specPow = 50.0f;
	Light_obj->SetLightParam(ligp);

	g_camera3D.SetPosition(camera_Pos);
	g_camera3D.SetTarget(camera_Target);
	g_camera3D.SetUp(camera_Up);
	//カメラの更新。
	g_camera3D.Update();
}