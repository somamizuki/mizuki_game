#include "stdafx.h"
#include "m_camera.h"

m_camera::m_camera(int No, char* obj_name):GameObject(No, obj_name)
{
}


m_camera::~m_camera()
{
}

bool m_camera::Start()
{
	player = game_obj->FindGO<Player>("player");
	g_camera3D.SetFar(5000.0f);
	g_camera3D.SetNear(1.0f);
	player_pos = player->Getpos();
	player_pos.y += 100.0f;
	camera_Target = player_pos;
	target_to_pos = player->Getpos() - player->Getforward();
	target_to_pos.Normalize();
	camera_Pos = target_to_pos * 500.0f;
	camera_Pos.y += 100.0f;
	g_camera3D.SetPosition(camera_Pos);
	g_camera3D.SetTarget(camera_Target);
	g_camera3D.SetUp(camera_Up);

	return true;
}

void m_camera::Math_Vector()
{
	camera_forward = camera_Target - camera_Pos;
	camera_forward.y = 0.000000f;
	camera_forward.Normalize();
	camera_rite.Cross(camera_Up, camera_forward);
	camera_rite.Normalize();
}

void m_camera::Various_Getter()
{
	player_pos = player->Getpos();
	player_pos.y += 100.0f;
}

void m_camera::PadInput()
{
	pad_X = g_pad[0].GetRStickXF();
	pad_Y = g_pad[0].GetRStickYF();

	if (fabs(pad_X+ pad_Y) >= 0.00001f)
	{
		move_or_stop = move;
	}
	if (fabs(pad_X+ pad_Y) < 0.00001f)
	{
		move_or_stop = stop;
	}
}

void m_camera::camera_move()
{
	target_to_pos = camera_Pos - camera_Target;
	rot.SetRotationDeg(camera_Up, pad_X*5.0f);
	rot.Multiply(target_to_pos);
}

void m_camera::camera_stop()
{
	target_to_pos = camera_Pos - camera_Target;
	CVector3 pMove = player->Get_PlayerMove();
	pMove.y = 0.0f;
	if (pMove.Length() >= 0.00001f)
	{
		pMove.Normalize();
		float angle = acosf(camera_forward.Dot(pMove));
		angle = CMath::RadToDeg(angle);
		CVector3 cross = CVector3::Zero();
		cross.Cross(camera_forward, pMove);
		cross.Normalize();
		if (angle < 90.0f) {
			rot.SetRotationDeg(cross, (angle / 180.0f)*2.0f);
			rot.Multiply(target_to_pos);
		}
		else {
			rot.SetRotationDeg(cross, ((180.0f-angle) / 180.0f)*2.0f);
			rot.Multiply(target_to_pos);
		}
		
		/*if (angle >= 45.0f&&angle<160.0f)
		{
			if (rot_f < 1.5f)
			{
				rot_f += 0.05f;
			}
			rot.SetRotationDeg(cross, rot_f);
			rot.Multiply(target_to_pos);
		}
		else
		{
			rot_f = 0.0f;
		}*/
		
		
	}
}

void m_camera::Update()
{
	PadInput();
	Various_Getter();
	Math_Vector();
	switch (move_or_stop) {
	case stop:
		camera_stop();
		break;
	case move:
		camera_move();
		break;
	}
	camera_Target = player_pos;
	camera_Pos = camera_Target + target_to_pos;
	camera_Pos.y = player->Getpos().y + 100.0f;
	g_camera3D.SetPosition(camera_Pos);
	g_camera3D.SetTarget(camera_Target);
	//カメラの更新。
	g_camera3D.Update();
}