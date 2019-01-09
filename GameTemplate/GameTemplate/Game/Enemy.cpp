#include "stdafx.h"
#include "Enemy.h"
#include"enemybullet.h"

Enemy::Enemy(int No, const char* obj_name):GameObject(No, obj_name)
{
}


Enemy::~Enemy()
{
	for (auto& tama : m_bullet)
	{
		game_obj->DeleteGO(tama);//���������񂾂�e������
	}
}

bool Enemy::Start()
{
	m_player = game_obj->FindGO<Player>("player");			//�v���C���[������
	m_model.Init(L"Assets/modelData/Enemy.cmo");			//���f���̃C�j�b�g
	m_model.SetShadowReciever(true);
	mathVector();											//�O�E����v�Z
	/*�X�v���C�g�̃V�F�[�_�[���\�[�X�̍쐬*/
	shaderResource.CreateFromDDSTextureFromFile(L"Resource/sprite/EnemyPos.dds");
	matoshaderResource.CreateFromDDSTextureFromFile(L"Resource/sprite/mato.dds");
	/*�X�v���C�g�̏�����*/
	sprite_ins.InitScreen2D(shaderResource, 0.0f, 0.0f, 0.1f);
	mato.InitScreen2D(matoshaderResource, 0.0f, 0.0f, 0.05f);
	return true;
}

void Enemy::mathVector()
{
	CMatrix m_Matrix = CMatrix::Identity();
	/*�N�I�[�^�j�I�������]�s����쐬*/
	m_Matrix.MakeRotationFromQuaternion(m_rotation);
	/*��]�s�񂩂�O�E����擾*/
	m_rite = { m_Matrix.m[0][0] ,m_Matrix.m[0][1] ,m_Matrix.m[0][2] };
	m_up = { m_Matrix.m[1][0] ,m_Matrix.m[1][1] ,m_Matrix.m[1][2] };
	m_forward = { m_Matrix.m[2][0] ,m_Matrix.m[2][1] ,m_Matrix.m[2][2] };
	/*���K��*/
	m_rite.Normalize();
	m_up.Normalize();
	m_forward.Normalize();

}



CVector3 Enemy::side_vec(CVector3 forward_or_rite)
{
	CVector3 e_to_p = CVector3::Zero();				//�G�l�~�[����v���C���[�Ɍ������x�N�g��
	CVector3 sideVec = CVector3::Zero();			//�v���C���[�̕�����C�ӂ̎��ɐ����ȕ��ʏ�ɂȂ������x�N�g��
	float len = 0.0f;								//�v���C���[�̈ʒu�������Ŏ󂯎�������Ɏˉe�����ۂ̒���
	/*�v���C���[�̈ʒu�Ƃ����Ă��A���m�ɂ͒e�����B�����ۂɃv���C���[������ł��낤�ʒu*/
	e_to_p = targetPos - m_position;
	len = forward_or_rite.Dot(e_to_p);
	sideVec = e_to_p - (forward_or_rite*len);
	sideVec.Normalize();

	return sideVec;
}

float Enemy::p_angle(CVector3 forward_or_rite)
{
	CVector3 e_to_p = targetPos - m_position;				//�G�l�~�[����v���C���[�Ɍ������x�N�g��
	e_to_p.Normalize();
	float acos_f = forward_or_rite.Dot(e_to_p);				//�����Ŏ󂯎��������e_to_p��cos�Ƃ����߂�
	float angle = CMath::RadToDeg(acosf(Acos(acos_f)));		//�A�[�Ncos���āA�Ƃ����߂ăf�O���[�ɂȂ���(����₷������)
	
	return angle;
}

float Enemy::rot_dir(CVector3 forward_or_rite)
{
	CVector3 SV = side_vec(forward_or_rite);			//�v���C���[�̕�����C�ӂ̎��ɐ����ȕ��ʏ�ɂȂ������x�N�g��
	

	float dir = 1.0f;		//��]����
	/*�󂯎�����������Ȃ̂��𔻒肵�Ă���*/
	/*SV�Ƃ̓��ό��ʂ�0���傫�������������ŉ�]���������肷��*/
	if (forward_or_rite.x == m_forward.x&&forward_or_rite.y == m_forward.y&&forward_or_rite.z == m_forward.z)
	{
		if (SV.Dot(m_rite) > 0.0f)
		{
			dir = -1.0f;
		}
		else if (SV.Dot(m_rite) < 0.0f)
		{
			dir = 1.0f;
		}
	}
	if (forward_or_rite.x == m_rite.x&&forward_or_rite.y == m_rite.y&&forward_or_rite.z == m_rite.z)
	{
		if (SV.Dot(m_forward) > 0.0f)
		{
			dir = 1.0f;
		}
		else if (SV.Dot(m_forward) < 0.0f)
		{
			dir = -1.0f;
		}
	}
	

	return dir;
}

void Enemy::enemyMove()
{
	//�O����̕������X�V
	mathVector();

	CVector3 e_to_p = CVector3::Zero();					//�G�l�~�[����v���C���[�Ɍ������x�N�g��
	CQuaternion rot = CQuaternion::Identity();			//��]
	float forwardrotangle = 0.0f;						//�O������ɉ��x��]�����邩
	float ritedrotangle = 0.0f;							//�E������ɉ��x��]�����邩
	float frotspeed = 0.0f;								//�O������̉�]���x
	float rrotspeed = 0.0f;								//�E������̉�]���x
	float rrotspeed_max = 1.0f;							//�E������̉�]���x�̍ő�l
	float frotspeed_max = 2.0f;							//�O������̉�]���x�̍ő�l
	

	/*������rrotspeed_max�����������ɒ������Ă��邾��*/
	CVector3 p_to_e = m_position - m_player->Getpos();
	p_to_e.Normalize();
	float acos_f = m_player->Getforward().Dot(p_to_e);
	float angle = CMath::RadToDeg(acosf(Acos(acos_f)));
	rrotspeed_max = max(0.5f, min(1.5f,angle*(1.0f / 100.0f)));
	///////////////////////////////////////////////////////////


	
	forwardrotangle = CMath::RadToDeg(acosf(Acos(m_up.Dot(side_vec(m_forward)))));
	frotspeed = min(frotspeed_max, forwardrotangle);

	rot.SetRotationDeg(CVector3::AxisZ(), frotspeed*rot_dir(m_forward));
	m_rotation.Multiply(rot);
	mathVector();

	forwardrotangle = CMath::RadToDeg(acosf(Acos(m_up.Dot(side_vec(m_forward)))));
	if (forwardrotangle < 1.0f)
	{
		ritedrotangle = CMath::RadToDeg(acosf(Acos(m_forward.Dot(side_vec(m_rite)))));
		rrotspeed = min(rrotspeed_max, ritedrotangle/**(1.0f / max(1.0f,ritedrotangle))*/);

		rot.SetRotationDeg(CVector3::AxisX(), -rrotspeed);
		m_rotation.Multiply(rot);
		mathVector();
	}
	/*�v���C���[�̑O�����ƃv���C���[���玩���Ɍ������x�N�g���Ƃ̊p�x�����߂�*/
	p_to_e = m_position - m_player->Getpos();
	p_to_e.Normalize();
	acos_f = m_player->Getforward().Dot(p_to_e);
	angle = CMath::RadToDeg(acosf(Acos(acos_f)));

	e_to_p = m_player->Getpos() - m_position;
	/*�܂��A��������܂��Ă��܂���B���낢���*/
	if (p_angle(m_forward)<45.0f&&e_to_p.Length() < 4000.0f)
	{
		if (speed > m_player->Get_PlayerMove().Length() - 1000.0f)
		{
			speed -= 50.0f;
		}
	}
	else 
	{
		if (speed < 4000.0f)
		{
			speed += 50.0f;
		}
	}

	if (p_angle(m_forward) > 120.0f/*&&angle<30.0f*/)
	{
		if (speed < 8000.0f)
		{
			speed += 50.0f;

		}
	}
	else
	{
		if (speed > 4000.0f)
		{
			speed -= 50.0f;

		}
	}
	
	

	
	


	movespeed = m_forward * speed;
	m_position += movespeed * (1.0f / 60.0f);




	
}

void Enemy::SpriteManager()
{
	mathVector();
	
	//�G������������v�Z����
	CVector3 p_to_e = CVector3::Zero();
	CVector3 sideVec = CVector3::Zero();
	float len = 0.0f;
	p_to_e = m_position - m_player->Getpos();
	len = m_player->Getforward().Dot(p_to_e);
	sideVec = p_to_e - (m_player->Getforward()*len);
	sideVec.Normalize();
	//�G��������������i��͉�ʊO�ɂ��邩�ǂ����̔���p�̕ϐ��j
	CVector2 sptrans = CVector2(0.0f, 0.0f);
	CVector2 inposf = CVector2(0.0f, 0.0f);
	CVector4 tmp = m_player->Getpos() + m_player->Getup()*100.0f + sideVec * 250.0f;
	CVector4 pos = m_player->Getpos() + m_player->Getup()*100.0f + p_to_e;
	//�G�̕������X�N���[�����W�n�ɕϊ�
	g_camera3D.GetViewMatrix().Mul(tmp);
	g_camera3D.GetProjectionMatrix().Mul(tmp);
	sptrans.x = tmp.x / tmp.w;
	sptrans.y = tmp.y / tmp.w;
	//2D�̈ʒu���A�b�v�f�[�g
	sprite_ins.Update(sptrans);
	//�G����ʓ��ɂ��邩�̔���
	g_camera3D.GetViewMatrix().Mul(pos);
	g_camera3D.GetProjectionMatrix().Mul(pos);
	inposf.x = pos.x / pos.w;
	inposf.y = pos.y / pos.w;
	//true�Ȃ��ʊO�ɂ���
	if (inposf.x > 1.0f || inposf.y > 1.0f)
	{
		posinScreen = true;
	}
	if (inposf.x <= 1.0f && inposf.y <= 1.0f)
	{
		posinScreen = false;
	}
	p_to_e.Normalize();
	//�v���C���[�̌��ɂ���΋����I�ɉ�ʊO
	if (p_to_e.Dot(m_player->Getforward()) < 0.0f)
	{
		posinScreen = true;
	}

	


	//�܂Ƃ̈ʒu��\��
	float speed = m_player->Get_PlayerMove().Length() + bulletspeed;
	p_to_e = m_position - m_player->Getpos();
	float yosoku_f = p_to_e.Length()*(1.0f / speed);
	CVector4 matopos = m_position + movespeed * yosoku_f;
	
	//�܂Ƃ̈ʒu���X�N���[�����W�n�ɕϊ�
	CVector2 matotrans= CVector2(0.0f, 0.0f);
	g_camera3D.GetViewMatrix().Mul(matopos);
	g_camera3D.GetProjectionMatrix().Mul(matopos);
	matotrans.x = matopos.x / matopos.w;
	matotrans.y = matopos.y / matopos.w;
	//�܂Ƃ̈ʒu���A�b�v�f�[�g
	mato.Update(matotrans);


	
}

void Enemy::Update()
{
	/*�e�����B�����ۂɃv���C���[������ł��낤�ʒu��\��*/
	float speed = movespeed.Length() + bulletspeed;							//�e�̍ŏI���x
	CVector3 e_to_p = m_player->Getpos() - m_position;						//�G�l�~�[����v���C���[�Ɍ������x�N�g��
	float yosoku_f = e_to_p.Length()*(1.0f / speed);						//�e�����B����܂ł̎���
	targetPos = m_player->Getpos() + m_player->Get_PlayerMove()*yosoku_f;
	
	atack_f = false;
	enemyMove();
	if (p_angle(m_forward)<2.0f)
	{
		/*�v���C���[���O����2.0�x�ȓ��ɂ����猂��*/
		atack_f = true;
	}

	for (auto& tama : m_bullet)
	{
		CVector3 to_bullet = tama->Getpos() - m_position;
		//�e��������茂����
		if (to_bullet.Length() <= firelength)
		{
			atack_f = false;
		}
		//�����Ȃ�����e������
		if (to_bullet.Length() > eraselength)
		{
			game_obj->DeleteGO(tama);
			m_bullet.erase(std::remove(m_bullet.begin(), m_bullet.end(), tama), m_bullet.end());
		}
	}
	if (atack_f==true)
	{
		//�e������
		enemybullet* tama= new enemybullet(0, "enemybullet");
		tama->setpoint(this);
		m_bullet.push_back(tama);
	
	}




	SpriteManager();
	m_model.UpdateWorldMatrix(m_position, m_rotation, CVector3::One());
}

void Enemy::Draw()
{
	m_model.Draw(
		LightOn,
		g_camera3D.GetViewMatrix(), 
		g_camera3D.GetProjectionMatrix()
	);
	
	
	
}

void Enemy::PostDraw()
{
	if (posinScreen == true)
	{
		sprite_ins.Draw(
			*g_graphicsEngine->GetD3DDeviceContext()
		);
	}
	else
	{
		mato.Draw(
			*g_graphicsEngine->GetD3DDeviceContext()
		);
	}
}