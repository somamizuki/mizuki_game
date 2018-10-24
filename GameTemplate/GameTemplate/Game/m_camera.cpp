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
	g_camera3D.SetFar(5000.0f);
	g_camera3D.SetNear(1.0f);
	player_pos = player->Getpos();
	camera_Target = player_pos + player->Getup()*100.0f;
	camera_Pos = camera_Target - CVector3::AxisZ()*500.0f;
	
	target_to_pos = camera_Pos - camera_Target;
	camera_forward = target_to_pos*-1.0f;
	camera_forward.Normalize();
	g_camera3D.SetPosition(camera_Pos);
	g_camera3D.SetTarget(camera_Target);
	g_camera3D.SetUp(camera_Up);

	return true;
}

void m_camera::Update()
{
	pad_X = g_pad[0].GetRStickXF()*2.0f;
	pad_Y = g_pad[0].GetRStickYF()*2.0f;
	camrotX.SetRotationDeg(CVector3::AxisY(), pad_X);
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
	}


	g_camera3D.SetPosition(camera_Pos);
	g_camera3D.SetTarget(camera_Target);
	//カメラの更新。
	g_camera3D.Update();
}