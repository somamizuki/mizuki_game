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
	m_model.SetShadowReciever(true);
	g_graphicsEngine->GetShadowMap()->RegistShadowCaster(&m_model);
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
		//��]
		rotY.SetRotationDeg(CVector3::AxisY(), -bityousei);
		m_rotation.Multiply(rotY);
	}
	if (g_pad[0].IsPress(enButtonRB1))				//R�o���p�[�������ꂽ��
	{
		//��]
		rotY.SetRotationDeg(CVector3::AxisY(), bityousei);		
		m_rotation.Multiply(rotY);
	}

	vector();
}

void Player::playerreturn()
{
	movespeed = m_forward * defaultspeed;				//�O�����Ƀf�t�H���g�X�s�[�h��
	CQuaternion rotX = CQuaternion::Identity();
	CQuaternion rotY = CQuaternion::Identity();
	CVector3 mpos_to_zero = CVector3::Zero() - m_position;
	float flen = m_forward.Dot(mpos_to_zero);
	CVector3 fsidevec = mpos_to_zero - (m_forward * flen);
	fsidevec.Normalize();
	float fangle = CMath::RadToDeg(acosf(Acos(fsidevec.Dot(m_up))));
	if (m_rite.Dot(fsidevec)>0.0f)
	{
		rotX.SetRotationDeg(CVector3::AxisZ(), max(-rotspeedX, -rotspeedX * fangle));		//�}���`�v���C����̂ŉ�]���̓��[���h�̎��ł悢
		m_rotation.Multiply(rotX);
	}
	if (m_rite.Dot(fsidevec) <0.0f)
	{
		rotX.SetRotationDeg(CVector3::AxisZ(), min(rotspeedX, rotspeedX*fangle));		//�}���`�v���C����̂ŉ�]���̓��[���h�̎��ł悢
		m_rotation.Multiply(rotX);
	}
	if (m_rite.Dot(fsidevec) == 0.0f&&fangle>179.0f)
	{
		rotX.SetRotationDeg(CVector3::AxisZ(), min(rotspeedX, rotspeedX*fangle));		//�}���`�v���C����̂ŉ�]���̓��[���h�̎��ł悢
		m_rotation.Multiply(rotX);
	}
	vector();
	if (fangle < 1.0f)
	{
		mpos_to_zero = CVector3::Zero() - m_position;
		float rlen = m_rite.Dot(mpos_to_zero);
		CVector3 rsidevec = mpos_to_zero - (m_rite * rlen);
		rsidevec.Normalize();
		float rangle = CMath::RadToDeg(acosf(Acos(rsidevec.Dot(m_forward))));
		if (m_up.Dot(rsidevec) > 0.0f)
		{
			rotY.SetRotationDeg(CVector3::AxisX(), max(-rotspeedZ, -rotspeedZ * rangle));		//�}���`�v���C����̂ŉ�]���̓��[���h�̎��ł悢
			m_rotation.Multiply(rotY);
		}
		if (m_up.Dot(rsidevec) < 0.0f)
		{
			rotY.SetRotationDeg(CVector3::AxisX(), min(rotspeedZ, rotspeedZ*rangle));		//�}���`�v���C����̂ŉ�]���̓��[���h�̎��ł悢
			m_rotation.Multiply(rotY);
		}
		if (m_up.Dot(rsidevec) == 0.0f&&rangle > 179.0f)
		{
			rotY.SetRotationDeg(CVector3::AxisX(), min(rotspeedZ, rotspeedZ*rangle));		//�}���`�v���C����̂ŉ�]���̓��[���h�̎��ł悢
			m_rotation.Multiply(rotY);
		}
	}
}

void Player::vector()
{
	rot_M.MakeRotationFromQuaternion(m_rotation);	//�N�I�[�^�j�I�������]�s����쐬
	m_rite.x = rot_M.m[0][0];
	m_rite.y = rot_M.m[0][1];
	m_rite.z = rot_M.m[0][2];
	m_up.x = rot_M.m[1][0];
	m_up.y = rot_M.m[1][1];
	m_up.z = rot_M.m[1][2];
	m_forward.x = rot_M.m[2][0];
	m_forward.y = rot_M.m[2][1];
	m_forward.z = rot_M.m[2][2];

	/*
	���K��
	*/
	m_forward.Normalize();
	m_rite.Normalize();
	m_up.Normalize();
}



void Player::Update()
{
	switch (pState)
	{
	case Nomal:
	{
		playermove();
		break;
	}
	case Return:
	{
		playerreturn();
		break;
	}
	}
	vector();
	m_position += movespeed * (1.0f / 60.0f);//���݂͉σt���[�����[�g�ł͂Ȃ��B
	if (CVector3(m_position - CVector3::Zero()).Length() > 80000.0f)
	{
		pState = Return;
	}
	else
	{
		pState = Nomal;
	}
	for (auto& tama : m_bullet)
	{
		CVector3 player_to_bullet = m_position - tama->Getpos();	//�e����v���C���[�Ɍ������x�N�g��
		if (player_to_bullet.Length() > eraselength || tama->GetDeath_f())	//player_to_bullet��eraseLength���傫����Βe������
		{
			game_obj->DeleteGO(tama);
			m_bullet.erase(std::remove(m_bullet.begin(), m_bullet.end(), tama), m_bullet.end());
			break;
		}
	}

	/*�����͒e�𖈃t���[���o�Ȃ��悤�ɂ��鏈��*/
	bool atack_f = true;
	for (auto& tama : m_bullet)
	{
		CVector3 player_to_bullet = m_position - tama->Getpos();
		if (player_to_bullet.Length() < firelength)
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
	g_graphicsEngine->GetShadowMap()->RegistShadowCaster(&m_model);
	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	/*�X�v���C�g�̃|�W�V������e��1�t���[����ɂ��邢�����X�N���[�����W�n�ɒ��������̂ɐݒ�*/
	/*�����̓N���X�����͊֐������ׂ�*/
	CVector2 sptrans = CVector2(0.0f, 0.0f);
	CVector4 tmp = m_position + m_forward * (movespeed.Length()+bulletspeed);
	g_camera3D.GetViewMatrix().Mul(tmp);
	g_camera3D.GetProjectionMatrix().Mul(tmp);
	sptrans.x = tmp.x / tmp.w ;
	sptrans.y = tmp.y / tmp.w ;

	aim.Update(sptrans);
	////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
}
/*
�ʏ�̕`��
*/
void Player::Draw()
{
	//�v���C���[�̕`��
	m_model.Draw(
		LightOn,
		g_camera3D.GetViewMatrix(), 
		g_camera3D.GetProjectionMatrix()
	);
}

void Player::PostDraw()
{
	//�X�v���C�g�̕`��
	aim.Draw(
		*g_graphicsEngine->GetD3DDeviceContext()
	);
}