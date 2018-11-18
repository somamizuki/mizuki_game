#include "stdafx.h"
#include "Player.h"
#include"math/kMath.h"
#include "m_camera.h"
#include"bullet.h"


Player::Player(int No, const char* obj_name):GameObject(No, obj_name)
{	

}


Player::~Player()
{
	for (auto& tama : m_bullet)
	{
		game_obj->DeleteGO(tama);
	}
	m_bullet.clear();
}

bool Player::Start()
{
	camera = game_obj->FindGO<m_camera>("camera");
	//cmoファイルの読み込み。
	m_model.Init(L"Assets/modelData/StarSparrow.cmo");
	


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

	shaderResource.CreateFromDDSTextureFromFile(L"Resource/sprite/damage.dds");
	sprite_ins.InitScreen2D(shaderResource, 0.0f, 0.0f,0.02f);
	return true;
}

void Player::playermove()
{
	CQuaternion rotX = CQuaternion::Identity();
	CQuaternion rotY = CQuaternion::Identity();
	float pad_X;									//パッドXの入力量
	float pad_Y;									//パッドYの入力量
	pad_X = g_pad[0].GetLStickXF()*2.0f;
	pad_Y = g_pad[0].GetLStickYF()*2.0f;

	movespeed = m_forward * 4000.0f;
	if (g_pad[0].IsPress(enButtonB))
	{
		movespeed = m_forward * 8000.0f;
	}
	if (g_pad[0].IsTrigger(enButtonA))
	{
		movespeed = m_forward * 2000.0f;
	}
	
	rotX.SetRotationDeg(CVector3::AxisZ(), -pad_X);
	m_rotation.Multiply(rotX);
	rotY.SetRotationDeg(CVector3::AxisX(), pad_Y);
	m_rotation.Multiply(rotY);
	if (g_pad[0].IsPress(enButtonLB1))
	{
		rotY.SetRotationDeg(CVector3::AxisY(), -0.3f);
		m_rotation.Multiply(rotY);
	}
	if (g_pad[0].IsPress(enButtonRB1))
	{
		rotY.SetRotationDeg(CVector3::AxisY(), 0.3f);
		m_rotation.Multiply(rotY);
	}

	vector();
}

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



void Player::Update()
{
	playermove();
	
	vector();
	m_position += movespeed * (1.0f / 60.0f);
	
	

	for (auto& tama : m_bullet)
	{
		
		CVector3 player_to_bullet = m_position - tama->Getpos();
		if (player_to_bullet.Length() > 10000.0f|| tama->GetDeadf())
		{
			game_obj->DeleteGO(tama);
			m_bullet.erase(std::remove(m_bullet.begin(), m_bullet.end(), tama), m_bullet.end());
			break;
		}
	}
	bool atack_f = true;
	for (auto& tama : m_bullet)
	{
		CVector3 player_to_bullet = m_position - tama->Getpos();
		if (player_to_bullet.Length() < 2000.0f)
		{
			atack_f = false;
		}
	}
	if (g_pad[0].IsTrigger(enButtonRB2) && atack_f == true)
	{
		m_bullet.push_back(new bullet(0, "bullet"));
	}
	
	
	
	
	//ワールド行列の更新。

	m_model.UpdateWorldMatrix(m_position, m_rotation, CVector3::One());


	

	CVector2 sptrans = CVector2(0.0f, 0.0f);
	CVector4 tmp = m_position + m_forward * (movespeed.Length()+10000.0f);
	g_camera3D.GetViewMatrix().Mul(tmp);
	g_camera3D.GetProjectionMatrix().Mul(tmp);
	sptrans.x = tmp.x / tmp.w ;
	sptrans.y = tmp.y / tmp.w ;

	sprite_ins.Update(sptrans);
	
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