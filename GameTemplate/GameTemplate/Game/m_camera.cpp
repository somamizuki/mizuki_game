#include "stdafx.h"
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
	g_camera3D.SetFar(50000.0f);
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

void m_camera::Update()
{
	float Abs = 150.0f;
	float amount = 10.0f;
	pad_Y += g_pad[0].GetLStickYF()*amount;
	pad_Y = min(pad_Y, Abs);
	pad_Y = max(pad_Y, -Abs);
	if (g_pad[0].GetLStickYF()==0.0f)
	{
		if (pad_Y > 0.0f)
		{
			pad_Y -= amount;
			pad_Y = max(pad_Y, 0.0f);
		}
		if (pad_Y < 0.0f)
		{
			pad_Y += amount;
			pad_Y = min(pad_Y, 0.0f);
		}
	}

	camera_rite = player->Getrite();
	player_pos = player->Getpos();
	camera_Target = player_pos + player->Getup()*100.0f;
	camera_Pos = camera_Target - player->Getforward()*500.0f + player->Getup()*-pad_Y;
	if (g_pad[0].IsPress(enButtonLB2))
	{
		camera_Pos = camera_Target + player->Getforward()*500.0f + player->Getup()*-pad_Y;
	}

	target_to_pos = camera_Pos - camera_Target;
	camera_forward = target_to_pos * -1.0f;
	camera_forward.Normalize();



	/*pad_X = g_pad[0].GetRStickXF()*2.0f;
	pad_Y = g_pad[0].GetRStickYF()*2.0f;
	camrotX.SetRotationDeg(player->Getup(), pad_X);
	camrotX.Multiply(target_to_pos);
	camrotX.Multiply(camera_rite);
	camrotY.SetRotationDeg(camera_rite, -pad_Y);
	camrotY.Multiply(target_to_pos);


	player_pos = player->Getpos();
	camera_Target = player_pos + player->Getup()*100.0f;
	camera_Pos = camera_Target+target_to_pos;

	target_to_pos = camera_Pos - camera_Target;
	camera_forward = target_to_pos * -1.0f;
	camera_forward.Normalize();
	cameraXZ = camera_forward;
	cameraXZ.y = 0.0f;
	cameraXZ.Normalize();
	float Y_angle = 0.0f;
	Y_angle = CMath::RadToDeg(acosf(cameraXZ.Dot(camera_forward)));
	if (Y_angle >= 80.0f)
	{
		camrotY.SetRotationDeg(camera_rite, pad_Y);
		camrotY.Multiply(target_to_pos);

		camera_Pos = camera_Target + target_to_pos;
		target_to_pos = camera_Pos - camera_Target;
		camera_forward = target_to_pos * -1.0f;
		camera_forward.Normalize();
		cameraXZ = camera_forward;
		cameraXZ.y = 0.0f;
		cameraXZ.Normalize();
	}*/


	camera_Up = player->Getup();

	g_camera3D.SetPosition(camera_Pos);
	g_camera3D.SetTarget(camera_Target);
	g_camera3D.SetUp(camera_Up);
	//カメラの更新。
	g_camera3D.Update();
}