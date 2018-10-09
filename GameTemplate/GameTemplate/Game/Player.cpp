#include "stdafx.h"
#include "Player.h"
#include"math/kMath.h"
#include "m_camera.h"


Player::Player(int No, const char* obj_name):GameObject(No, obj_name)
{	

}


Player::~Player()
{
}

bool Player::Start()
{
	camera = game_obj->FindGO<m_camera>("camera");
	//cmoファイルの読み込み。
	m_model.Init(L"Assets/modelData/unityChan.cmo");
	rot_M.MakeRotationFromQuaternion(m_rotation);
	m_forward.x = rot_M.m[2][0];
	m_forward.y = rot_M.m[2][1];
	m_forward.z = rot_M.m[2][2];
	m_rite.x = rot_M.m[0][0];
	m_rite.y = rot_M.m[0][1];
	m_rite.z = rot_M.m[0][2];
	m_up.x = rot_M.m[1][0];
	m_up.y = rot_M.m[1][1];
	m_up.z = rot_M.m[1][2];
	m_forward.Normalize();
	m_rite.Normalize();
	m_up.Normalize();
	m_characon.Init(
		30.0f,
		80.0f,
		m_position
	);

	shaderResource.CreateFromDDSTextureFromFile(L"Resource/sprite/damage.dds");
	sprite_ins.Init(shaderResource, 1000.0f, 1000.0f,2);
	return true;
}

void Player::state_move()
{
}

void Player::state_stop()
{
}
//いろんなベクトルの計算。
void Player::vector()
{
	rot_M.MakeRotationFromQuaternion(m_rotation);
	m_forward.x = rot_M.m[2][0];
	m_forward.y = rot_M.m[2][1];
	m_forward.z = rot_M.m[2][2];
	m_rite.x = rot_M.m[0][0];
	m_rite.y = rot_M.m[0][1];
	m_rite.z = rot_M.m[0][2];
	m_up.x = rot_M.m[1][0];
	m_up.y = rot_M.m[1][1];
	m_up.z = rot_M.m[1][2];
	m_forward.Normalize();
	m_rite.Normalize();
	m_up.Normalize();
}
//普通の計算
void Player::Math()
{
	float MV_y = movespeed.y;
	movespeed = camera->Get_camera_forward()* pad_Y * 300.0f+ camera->Get_camerarite()*pad_X*300.0f;
	move_vector = movespeed;
	
	
	move_vector.Normalize();
	if (movespeed.Length() >= 0.00001f)
	{
		m_angle = acosf(move_vector.Dot(CVector3::AxisZ()));
		CVector3 cross;
		cross.Cross(CVector3::AxisZ(), move_vector);
		cross.Normalize();
		m_rotation.SetRotation(cross, m_angle);
	}
	movespeed.y = MV_y;
}

void Player::Pad_Input()
{
	//パッドの入力量を代入
	pad_X = g_pad[0].GetLStickXF();
	pad_Y = g_pad[0].GetLStickYF();
	padinput_vector = { pad_X ,0.0f,pad_Y };
	//パッド入力があるかを判定
	//入力有り。
	if (padinput_vector.Length() >= 0.000001f)
	{
		move_or_stop = move;
	}
	//入力無し。
	if (padinput_vector.Length() < 0.000001f)
	{
		move_or_stop = stop;
	}

	if (g_pad[0].IsTrigger(enButtonA) && m_characon.IsOnGround())
	{
		movespeed.y += 400.0f;
	}
	if (g_pad[0].IsTrigger(enButtonB))
	{
	}
}

void Player::Update()
{
	vector();
	Pad_Input();
	Math();
	switch (move_or_stop) {
	case stop:
		state_stop();
		break;
	case move:
		state_move();
		break;
	}
	
	movespeed.y -= 9.8f;
	m_position = m_characon.Execute(1.0f/60.0f, movespeed);
	//ワールド行列の更新。
	m_model.UpdateWorldMatrix(m_position, m_rotation, CVector3::One());
}
void Player::Draw()
{
	
	m_model.Draw(
		g_camera3D.GetViewMatrix(), 
		g_camera3D.GetProjectionMatrix()
	);
	sprite_ins.Draw(
		*g_graphicsEngine->GetD3DDeviceContext()
	);
}