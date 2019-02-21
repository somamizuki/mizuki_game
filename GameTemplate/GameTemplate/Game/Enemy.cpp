#include "stdafx.h"
#include "Enemy.h"
#include "Player.h"
#include"Class_of_NewGO.h"
#include"bullet.h"

Enemy::Enemy(int No, const char* obj_name):GameObject(No, obj_name)
{
}


Enemy::~Enemy()
{
	/*�G�l�~�[���폜���ꂽ�Ƃ��ꏏ�ɏ���*/
	for (const auto& effct : spriteeffect)
	{
		delete effct;
	}
	if (RiteBullet != nullptr)
	{
		game_obj->DeleteGO(RiteBullet);
	}
	if (LeftBullet != nullptr)
	{
		game_obj->DeleteGO(LeftBullet);
	}
}

bool Enemy::Start()
{
	m_player = game_obj->FindGO<Player>("player");			//�v���C���[������
	m_player->AddDeleteGOListeners([&](GameObject* go)
	{
		m_player = nullptr;
	});
	m_model.Init(L"Assets/modelData/Enemy.cmo");			//���f���̃C�j�b�g
	m_model.SetShadowReciever(true);						//�X�L�����f�����V���h�E���V�[�o�[�ɓo�^
	m_model.SetNormalMap(L"Assets/modelData/StarSparrow_Normal.dds");//�X�L�����f���ɖ@���}�b�v��K�p
	mathVector();											//�O�E����v�Z
	/*�X�v���C�g�̃V�F�[�_�[���\�[�X�̍쐬*/
	shaderResource.CreateFromDDSTextureFromFile(L"Resource/sprite/EnemyPos.dds");
	EnemyMarkerSRV.CreateFromDDSTextureFromFile(L"Resource/sprite/Enemy.dds");
	/*�X�v���C�g�̏�����*/
	sprite_ins.Init(shaderResource.GetBody(), 200.0f*0.35f, 173.0f*0.35f);
	EnemyMarkerSprite.Init(EnemyMarkerSRV.GetBody(), 512.0f, 512.0f);

	CoN = game_obj->FindGO<Class_of_NewGO>("newObject");
	mathVector();																			//
	LeftBullet = new bullet(0, "bullet");													//
	LeftBullet->WitchBullet(isEnemy);														//
	LeftBullet->SetEnemy(this);
	LeftBullet->SetLeft_or_Rite(Left);

	RiteBullet = new bullet(0, "bullet");
	RiteBullet->WitchBullet(isEnemy);
	RiteBullet->SetEnemy(this);
	RiteBullet->SetLeft_or_Rite(Rite);
	CVector3 pos;
	/*level���疼�O�Ńt�b�N����Engin��������*/
	Enemy_EnginPos.Init(L"Assets/level/Enemy_EnginPos.tkl", [&](LevelObjectData Lobjdata)
	{
		if (std::wcscmp(Lobjdata.name, L"Enemy") == 0)
		{
			pos = Lobjdata.position;
		}
		else if (std::wcscmp(Lobjdata.name, L"Box") == 0)
		{
			Engin* engin = new Engin;
			engin->toEngin = Lobjdata.position - pos;
			engin->toEngin = { CVector3::AxisX().Dot(engin->toEngin),CVector3::AxisY().Dot(engin->toEngin),CVector3::AxisZ().Dot(engin->toEngin) };
			spriteeffect.push_back(engin);
		}
		return true;
	});

	m_srv.CreateFromDDSTextureFromFile(L"Resource/sprite/fog.dds");

	for (const auto& effct : spriteeffect)
	{
		effct->spriteeffect.Init(m_srv.GetBody(), 0.033f, 0);
	}


	/*m_spriteeffect[0].Init(m_srv.GetBody(), 0.033f, 0);
	m_spriteeffect[1].Init(m_srv.GetBody(), 0.033f, 0);*/
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

void Enemy::bulletManager()
{
	
	CVector3 toPlayerVec = m_player->Getpos() - m_position; //�v���C���[�Ɍ������x�N�g�����v�Z
	toPlayerVec.Normalize();								//�m�[�}���C�Y
	bool LockOnflag = m_forward.Dot(toPlayerVec)>cosf(CMath::DegToRad(10.0f));		//�p�x�Ń��b�N�I�����邩�ǂ������߂�
	/*�E�~�T�C�����Z�b�g������Ă��Ȃ���΃^�C�}�[��i�߂�*/
	if (RiteBullet!=nullptr)
	{
		ritebulletTime += 1.0f*(1.0f / 60.0f);
	}
	if (ritebulletTime >= 3.0f&&RiteBullet == nullptr)
	{
		RiteBullet = new bullet(0, "bullet");
		RiteBullet->WitchBullet(isEnemy);
		RiteBullet->SetEnemy(this);
		RiteBullet->SetLeft_or_Rite(Rite);
		ritebulletTime = 0.0f;
	}
	if (LeftBullet == nullptr)
	{
		leftbulletTime += 1.0f*(1.0f / 60.0f);
	}
	if (leftbulletTime >= 3.0f&&LeftBullet == nullptr)
	{
		LeftBullet = new bullet(0, "bullet");
		LeftBullet->WitchBullet(isEnemy);
		LeftBullet->SetEnemy(this);
		LeftBullet->SetLeft_or_Rite(Left);
		leftbulletTime = 0.0f;
	}
	if (LockOnflag)
	{
		if (RiteBullet != nullptr)
		{
			RiteBullet->SetBulletParam();
			RiteBullet = nullptr;
		}
		else if (LeftBullet != nullptr)
		{
			LeftBullet->SetBulletParam();
			LeftBullet = nullptr;
		}
	}
	
}

CVector3 Enemy::side_vec(CVector3 forward_or_rite)
{
	CVector3 e_to_p = CVector3::Zero();				//�G�l�~�[����v���C���[�Ɍ������x�N�g��
	CVector3 sideVec = CVector3::Zero();			//�v���C���[�̕�����C�ӂ̎��ɐ����ȕ��ʏ�ɂȂ������x�N�g��
	float len = 0.0f;								//�v���C���[�̈ʒu�������Ŏ󂯎�������Ɏˉe�����ۂ̒���
	/*�v���C���[�̈ʒu�Ƃ����Ă��A���m�ɂ͒e�����B�����ۂɃv���C���[������ł��낤�ʒu*/
	e_to_p = m_player->Getpos() - m_position;
	len = forward_or_rite.Dot(e_to_p);
	sideVec = e_to_p - (forward_or_rite*len);
	sideVec.Normalize();

	return sideVec;
}

float Enemy::p_angle(CVector3 forward_or_rite)
{
	CVector3 e_to_p = m_player->Getpos() - m_position;				//�G�l�~�[����v���C���[�Ɍ������x�N�g��
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
	const float rrotspeed_max = 0.5f;					//�E������̉�]���x�̍ő�l
	const float frotspeed_max = 3.0f;					//�O������̉�]���x�̍ő�l
	const float BoostSpeed = 4000.0f;
	const float DefaultSpeed = 3000.0f;
	float acos_f = 0.0f;
	float angle = 0.0f;
	CVector3 p_to_e = CVector3::Zero();
	/*��]*/
	forwardrotangle = CMath::RadToDeg(acosf(Acos(m_up.Dot(side_vec(m_forward)))));
	frotspeed = min(frotspeed_max, forwardrotangle);

	rot.SetRotationDeg(CVector3::AxisZ(), frotspeed*rot_dir(m_forward));
	m_rotation.Multiply(rot);
	mathVector();

	forwardrotangle = CMath::RadToDeg(acosf(Acos(m_up.Dot(side_vec(m_forward)))));
	if (forwardrotangle < 0.1f)
	{
		ritedrotangle = CMath::RadToDeg(acosf(Acos(m_forward.Dot(side_vec(m_rite)))));
		rrotspeed = min(rrotspeed_max, ritedrotangle);

		rot.SetRotationDeg(CVector3::AxisX(), -rrotspeed);
		m_rotation.Multiply(rot);
		mathVector();
	}

	bool NearPlayer = CVector3(m_position - m_player->Getpos()).Length() < 2000.0f;
	if (NearPlayer)
	{
		if (p_angle(m_up) < 90.0f)
		{
			rot.SetRotationDeg(CVector3::AxisX(), 2.0f);
			m_rotation.Multiply(rot);
			mathVector();
		}
		if (p_angle(m_up) >= 90.0f)
		{
			rot.SetRotationDeg(CVector3::AxisX(), -2.0f);
			m_rotation.Multiply(rot);
			mathVector();
		}
		
	}


	/*�v���C���[�̑O�����ƃv���C���[���玩���Ɍ������x�N�g���Ƃ̊p�x�����߂�*/
	p_to_e = m_position - m_player->Getpos();
	p_to_e.Normalize();
	acos_f = m_player->Getforward().Dot(p_to_e);
	angle = CMath::RadToDeg(acosf(Acos(acos_f)));

	if (p_angle(m_forward) > 120.0f/*&&angle<30.0f*/)
	{
		if (speed < BoostSpeed)
		{
			speed += 50.0f;
		}
	}
	else
	{
		if (speed > DefaultSpeed)
		{
			speed -= 50.0f;
		}
		else
		{
			speed += 50.0f;
		}
	}
	movespeed = m_forward * speed;
	m_position += movespeed * deltaTime;
	for (const auto& enemy : CoN->GetEnemy())
	{
		if (this == enemy || enemy==NULL)
		{
			continue;
		}
		CVector3 E_to_E = enemy->Getpos() - m_position;
		float length = E_to_E.Length();
		
		if (length < 500.0f)
		{
			E_to_E.Normalize();
			length = length - 500.0f;

			m_position += (E_to_E* length);
		}
	}
	
}

void Enemy::SpriteManager()
{

	/*�G�l�~�[���F���₷�����邽�߂̃X�v���C�g�̃|�W�V�������v�Z*/
	{
		CMatrix WVP;
		WVP.MakeTranslation(m_position);
		WVP.Mul(WVP, g_camera3D.GetViewMatrix());
		WVP.Mul(WVP, g_camera3D.GetProjectionMatrix());
		CVector3 SCpos = CVector3(WVP.m[3][0], WVP.m[3][1], WVP.m[3][2]);
		EnemyMarkerDraw = false;
		if (SCpos.z >= 0.0f)
		{
			EnemyMarkerDraw = true;
		}
		SCpos /= WVP.m[3][3];
		SCpos.x *= FRAME_BUFFER_W / 2.0f;
		SCpos.y *= FRAME_BUFFER_H / 2.0f;
		SCpos.z = 0.0f;
		EnemyMarkerSprite.Update(
			SCpos,
			CQuaternion::Identity(),
			CVector3::One()*0.09f
		);
	}


	/*�G�l�~�[�̕����p�X�v���C�g�̃|�W�V�������v�Z*/
	{
		posinScreen = true;
		CVector3 camtoMypos = m_position - g_camera3D.GetPosition();
		CVector3 spritepos = { g_camera3D.GetRite().Dot(camtoMypos),g_camera3D.GetUp().Dot(camtoMypos),0.0f };
		
		camtoMypos.Normalize();
		if (g_camera3D.GetForward().Dot(camtoMypos) > cosf(g_camera3D.GetViewAngle()*2.0f))
		{
			posinScreen = false;
		}
		spritepos.Normalize();

		spritepos *= 500.0f;
		sprite_ins.Update(
			spritepos,
			CQuaternion::Identity(),
			CVector3::One()
		);
	}
}

void Enemy::Update()
{
	if (m_player != nullptr)
	{
		
		enemyMove();
		bulletManager();
		SpriteManager();
	}
	else
	{
		posinScreen = false;
		EnemyMarkerDraw = false;
		movespeed = m_forward * speed;
		m_position += movespeed * deltaTime;
		for (const auto& enemy : CoN->GetEnemy())
		{
			if (this == enemy || enemy == NULL)
			{
				continue;
			}
			CVector3 E_to_E = enemy->Getpos() - m_position;
			float length = E_to_E.Length();

			if (length < 500.0f)
			{
				E_to_E.Normalize();
				length = length - 500.0f;

				m_position += (E_to_E* length);
			}
		}
	}
	
	
	
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

void Enemy::EffectDraw()
{
	for (const auto& effct : spriteeffect)
	{
		CVector3 pos = m_rite * effct->toEngin.x + m_up * effct->toEngin.y + m_forward * effct->toEngin.z;
		effct->spriteeffect.Update(m_position + pos);
		effct->spriteeffect.Draw();
	}




	/*m_spriteeffect[0].Update(m_position + m_rite * 105.0f + m_forward * -130.0f);
	m_spriteeffect[1].Update(m_position + m_rite * -105.0f + m_forward * -130.0f);
	m_spriteeffect[0].Draw();
	m_spriteeffect[1].Draw();*/
}

void Enemy::PostDraw()
{
	if (posinScreen)
	{
		sprite_ins.Draw(
			*g_graphicsEngine->GetD3DDeviceContext()
		);
	}
	if (EnemyMarkerDraw)
	{
		EnemyMarkerSprite.Draw(
			*g_graphicsEngine->GetD3DDeviceContext()
		);
	}
	
	
}