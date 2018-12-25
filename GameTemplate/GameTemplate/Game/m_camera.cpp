#include "stdafx.h"
#include "Player.h"
#include "m_camera.h"
#include"math/kMath.h"

m_camera::m_camera(int No, char* obj_name):GameObject(No, obj_name)
{
}


m_camera::~m_camera()
{
}

bool m_camera::Start()
{
	player = game_obj->FindGO<Player>("player");
	camera_rite = player->Getrite();
	g_camera3D.SetFar(100000.0f);
	g_camera3D.SetNear(1.0f);
	player_pos = player->Getpos();
	camera_Target = player_pos + player->Getup()*100.0f;
	camera_Pos = camera_Target - player->Getforward()*500.0f;
	
	target_to_pos = camera_Pos - camera_Target;
	camera_forward = target_to_pos*-1.0f;
	camera_forward.Normalize();
	camera_Up = player->Getup();

	g_camera3D.SetPosition(camera_Pos);
	g_camera3D.SetTarget(camera_Target);
	g_camera3D.SetUp(camera_Up);

	return true;
}

void m_camera::CameraMove()
{
	pad_Y = g_pad[0].GetLStickYF();
	pad_X = g_pad[0].GetLStickXF();
	rotYmax = pad_Y * 20.0f;
	if (rotYmax > m_angleY)
	{
		m_angleY += (rotYmax - m_angleY)*(1.0f / 15.0f);
	}
	if (rotYmax < m_angleY)
	{
		m_angleY += (rotYmax - m_angleY)*(1.0f / 15.0f);
	}
	/*rotXmax = (pad_X * 10.0f)*abs(pad_Y);
	if (rotXmax > m_angleX)
	{
		m_angleX += (rotXmax - m_angleX)*(1.0f / 10.0f);
	}
	if (rotXmax < m_angleX)
	{
		m_angleX += (rotXmax - m_angleX)*(1.0f / 10.0f);
	}*/



	camera_rite = player->Getrite();
	player_pos = player->Getpos();
	camera_Target = player_pos + player->Getup()*100.0f;
	if (g_pad[0].IsPress(enButtonB))
	{
		CamLen = min(800.0f, CamLen + 10.0f);
	}
	else {
		CamLen = max(500.0f, CamLen - 10.0f);
	}


	CVector3 vec = player->Getforward()*CamLen;
	CQuaternion rotY = CQuaternion::Identity();
	rotY.SetRotationDeg(player->Getrite(), -m_angleY);
	rotY.Multiply(vec);
	/*CQuaternion rotX = CQuaternion::Identity();
	rotX.SetRotationDeg(player->Getup(), -m_angleX);
	rotX.Multiply(vec);*/

	camera_Pos = camera_Target - vec;
	if (g_pad[0].IsPress(enButtonLB2))
	{
		camera_Pos = camera_Target + player->Getforward()*500.0f + player->Getup()*-pad_Y;
	}
}

void m_camera::Update()
{
	CameraMove();

	

	target_to_pos = camera_Pos - camera_Target;
	camera_forward = target_to_pos * -1.0f;
	camera_forward.Normalize();



	


	camera_Up = player->Getup();

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