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
	for (auto& tama : m_bullet)			//������������Ƌʂ������B�����A�e
	{
		game_obj->DeleteGO(tama);
	}
}

bool Player::Start()
{
	camera = game_obj->FindGO<m_camera>("camera");				//�J�����̃C���X�^���X������
	m_model.Init(L"Assets/modelData/StarSparrow.cmo");			//cmo�t�@�C���̓ǂݍ��݁B
	vector();				//�v���C���[�̑O�E��̃x�N�g�����v�Z����
	shaderResource.CreateFromDDSTextureFromFile(L"Resource/sprite/damage.dds");	//aim�p�̃V�F�[�_�[���\�[�X���쐬
	aim.InitScreen2D(shaderResource, 0.0f, 0.0f,0.02f);			//aim��������
	return true;
}

void Player::playermove()
{
	CQuaternion rotX = CQuaternion::Identity();
	CQuaternion rotY = CQuaternion::Identity();
	
	pad_X = g_pad[0].GetLStickXF();						//�p�b�h�̓��͗ʂ��擾
	pad_Y = g_pad[0].GetLStickYF();

	
	movespeed = m_forward * defaultspeed;				//�O�����Ƀf�t�H���g�X�s�[�h��
	if (g_pad[0].IsPress(enButtonB))					//B�{�^���������ꂽ��
	{
		movespeed = m_forward * boostspeed;				//�ړ����x���u�[�X�g�ɂ���
	}
	if (g_pad[0].IsTrigger(enButtonA))					//A�{�^���������ꂽ��
	{

		movespeed = m_forward * slowspeed;				//����
	}

	/*
	��]
	*/
	rotX.SetRotationDeg(CVector3::AxisZ(), -pad_X* rotspeedX);		//�}���`�v���C����̂ŉ�]���̓��[���h�̎��ł悢
	m_rotation.Multiply(rotX);
	rotY.SetRotationDeg(CVector3::AxisX(), pad_Y*rotspeedZ);		
	m_rotation.Multiply(rotY);

	/*
	�G�C���̔�����
	*/
	if (g_pad[0].IsPress(enButtonLB1))				//L�o���p�[�������ꂽ��
	{
		
		rotY.SetRotationDeg(CVector3::AxisY(), -bityousei);
		m_rotation.Multiply(rotY);
	}
	if (g_pad[0].IsPress(enButtonRB1))				//R�o���p�[�������ꂽ��
	{
		rotY.SetRotationDeg(CVector3::AxisY(), bityousei);
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
		float eraseLength = 20000.0f;
		CVector3 player_to_bullet = m_position - tama->Getpos();
		if (player_to_bullet.Length() > eraseLength || tama->GetDeath_f())
		{
			game_obj->DeleteGO(tama);
			m_bullet.erase(std::remove(m_bullet.begin(), m_bullet.end(), tama), m_bullet.end());
			break;
		}
	}
	bool atack_f = true;
	for (auto& tama : m_bullet)
	{
		float atackLength = 2000.0f;
		CVector3 player_to_bullet = m_position - tama->Getpos();
		if (player_to_bullet.Length() < atackLength)
		{
			atack_f = false;
		}
	}
	if (g_pad[0].IsTrigger(enButtonRB2) && atack_f == true)
	{
		m_bullet.push_back(new bullet(0, "bullet"));
	}
	
	
	
	//���[���h�s��̍X�V�B

	m_model.UpdateWorldMatrix(m_position, m_rotation, CVector3::One());


	

	CVector2 sptrans = CVector2(0.0f, 0.0f);
	CVector4 tmp = m_position + m_forward * (movespeed.Length()+bulletspeed);
	g_camera3D.GetViewMatrix().Mul(tmp);
	g_camera3D.GetProjectionMatrix().Mul(tmp);
	sptrans.x = tmp.x / tmp.w ;
	sptrans.y = tmp.y / tmp.w ;

	aim.Update(sptrans);
	
}
void Player::Draw()
{

	m_model.Draw(
		g_camera3D.GetViewMatrix(), 
		g_camera3D.GetProjectionMatrix()
	);
}

void Player::PostDraw()
{
	aim.Draw(
		*g_graphicsEngine->GetD3DDeviceContext()
	);
}