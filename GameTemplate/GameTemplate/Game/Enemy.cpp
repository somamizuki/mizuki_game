#include "stdafx.h"
#include "Enemy.h"
#include "Player.h"
#include"Class_of_NewGO.h"
#include"bullet.h"

Enemy::Enemy(int No, const char* obj_name) :GameObject(No, obj_name)
{
}


Enemy::~Enemy()
{

}

bool Enemy::Start()
{
	m_player = game_obj->FindGO<Player>("player");			//�v���C���[������
	m_player->AddMyPointer<Player, Enemy>(&m_player, this);
	/*m_player->AddDeleteGOListeners([&](GameObject* go)
	{
		m_player = nullptr;
	});*/
	m_skinmodel.Init(L"Assets/modelData/Enemy.cmo");			//���f���̃C�j�b�g
	m_skinmodel.SetShadowReciever(true);						//�X�L�����f�����V���h�E���V�[�o�[�ɓo�^
	m_skinmodel.SetNormalMap(L"Resource/sprite/StarSparrow_Normal.dds");//�X�L�����f���ɖ@���}�b�v��K�p
	Vector();											//�O�E����v�Z
	/*�X�v���C�g�̃V�F�[�_�[���\�[�X�̍쐬*/
	m_outscreenenemySRV.CreateFromDDSTextureFromFile(L"Resource/sprite/EnemyPos.dds");
	m_enemymarkerSRV.CreateFromDDSTextureFromFile(L"Resource/sprite/Enemy.dds");
	/*�X�v���C�g�̏�����*/
	m_outenemysprite.Init(m_outscreenenemySRV.GetBody(), 200.0f*0.35f, 173.0f*0.35f);
	m_enemymarkersprite.Init(m_enemymarkerSRV.GetBody(), 512.0f, 512.0f);

	m_class_of_newgo = game_obj->FindGO<Class_of_NewGO>("newObject");
	m_class_of_newgo->AddMyPointer<Class_of_NewGO, Enemy>(&m_class_of_newgo, this);
	Vector();																			//
	m_leftbullet = new bullet(0, "bullet");													//
	m_leftbullet->WitchBullet(isEnemy);														//
	m_leftbullet->SetEnemy(this);
	m_leftbullet->SetLeft_or_Rite(Left);

	m_ritebullet = new bullet(0, "bullet");
	m_ritebullet->WitchBullet(isEnemy);
	m_ritebullet->SetEnemy(this);
	m_ritebullet->SetLeft_or_Rite(Rite);
	CVector3 pos;
	/*level���疼�O�Ńt�b�N����Engin��������*/
	m_enemyenginlevel.Init(L"Assets/level/Enemy_EnginPos.tkl", [&](LevelObjectData Lobjdata)
	{
		if (std::wcscmp(Lobjdata.name, L"Enemy") == 0)
		{
			pos = Lobjdata.position;
		}
		else if (std::wcscmp(Lobjdata.name, L"Box") == 0)
		{
			Engin* engin = new Engin;
			engin->m_toengin = Lobjdata.position - pos;
			engin->m_toengin = { CVector3::AxisX().Dot(engin->m_toengin),CVector3::AxisY().Dot(engin->m_toengin),CVector3::AxisZ().Dot(engin->m_toengin) };
			m_spriteeffect.push_back(engin);
		}
		return true;
	});

	m_effectsrv.CreateFromDDSTextureFromFile(L"Resource/sprite/fog.dds");

	for (const auto& effct : m_spriteeffect)
	{
		effct->m_spriteeffect.Init(m_effectsrv.GetBody(), 0.06f, 0);
	}

	return true;
}

void Enemy::Vector()
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

void Enemy::BulletManager()
{

	CVector3 toPlayerVec = m_player->GetPosition() - m_position; //�v���C���[�Ɍ������x�N�g�����v�Z
	toPlayerVec.Normalize();								//�m�[�}���C�Y
	bool LockOnflag = m_forward.Dot(toPlayerVec) > cosf(CMath::DegToRad(10.0f));		//�p�x�Ń��b�N�I�����邩�ǂ������߂�
	/*�E�~�T�C�����Z�b�g������Ă��Ȃ���΃^�C�}�[��i�߂�*/
	if (m_ritebullet != nullptr)
	{
		m_ritebullettime += 1.0f*(1.0f / 60.0f);
	}
	if (m_ritebullettime >= BULLETSPAN && m_ritebullet == nullptr)
	{
		m_ritebullet = new bullet(0, "bullet");
		m_ritebullet->WitchBullet(isEnemy);
		m_ritebullet->SetEnemy(this);
		m_ritebullet->SetLeft_or_Rite(Rite);
		m_ritebullettime = 0.0f;
	}
	if (m_leftbullet == nullptr)
	{
		m_leftbullettime += 1.0f*(1.0f / 60.0f);
	}
	if (m_leftbullettime >= BULLETSPAN && m_leftbullet == nullptr)
	{
		m_leftbullet = new bullet(0, "bullet");
		m_leftbullet->WitchBullet(isEnemy);
		m_leftbullet->SetEnemy(this);
		m_leftbullet->SetLeft_or_Rite(Left);
		m_leftbullettime = 0.0f;
	}
	if (LockOnflag)
	{
		if (m_ritebullet != nullptr)
		{
			m_ritebullet->SetBulletParam();
			m_ritebullet = nullptr;
		}
		else if (m_leftbullet != nullptr)
		{
			m_leftbullet->SetBulletParam();
			m_leftbullet = nullptr;
		}
	}

}

CVector3 Enemy::SideVec(CVector3 forward_or_rite)
{
	CVector3 e_to_p = CVector3::Zero();				//�G�l�~�[����v���C���[�Ɍ������x�N�g��
	CVector3 sideVec = CVector3::Zero();			//�v���C���[�̕�����C�ӂ̎��ɐ����ȕ��ʏ�ɂȂ������x�N�g��
	float len = 0.0f;								//�v���C���[�̈ʒu�������Ŏ󂯎�������Ɏˉe�����ۂ̒���
	/*�v���C���[�̈ʒu�Ƃ����Ă��A���m�ɂ͒e�����B�����ۂɃv���C���[������ł��낤�ʒu*/
	e_to_p = m_player->GetPosition() - m_position;
	len = forward_or_rite.Dot(e_to_p);
	sideVec = e_to_p - (forward_or_rite*len);
	sideVec.Normalize();

	return sideVec;
}

float Enemy::ToPlayerAngle(CVector3 forward_or_rite)
{
	CVector3 e_to_p = m_player->GetPosition() - m_position;				//�G�l�~�[����v���C���[�Ɍ������x�N�g��
	e_to_p.Normalize();
	float acos_f = forward_or_rite.Dot(e_to_p);				//�����Ŏ󂯎��������e_to_p��cos�Ƃ����߂�
	float angle = CMath::RadToDeg(acosf(Acos(acos_f)));		//�A�[�Ncos���āA�Ƃ����߂ăf�O���[�ɂȂ���(����₷������)

	return angle;
}

float Enemy::RotDirection(CVector3 forward_or_rite)
{
	CVector3 SV = SideVec(forward_or_rite);			//�v���C���[�̕�����C�ӂ̎��ɐ����ȕ��ʏ�ɂȂ������x�N�g��


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

void Enemy::EnemyMove()
{
	//�O����̕������X�V
	Vector();

	CVector3 e_to_p = CVector3::Zero();					//�G�l�~�[����v���C���[�Ɍ������x�N�g��
	CQuaternion rot = CQuaternion::Identity();			//��]
	float forwardrotangle = 0.0f;						//�O������ɉ��x��]�����邩
	float ritedrotangle = 0.0f;							//�E������ɉ��x��]�����邩
	float frotspeed = 0.0f;								//�O������̉�]���x
	float rrotspeed = 0.0f;								//�E������̉�]���x
	float rrotspeed_max = 0.8f;					//�E������̉�]���x�̍ő�l
	float frotspeed_max = 3.0f;					//�O������̉�]���x�̍ő�l
	const float BoostSpeed = 4500.0f;
	const float DefaultSpeed = 3000.0f;
	float acos_f = 0.0f;
	float angle = 0.0f;
	CVector3 p_to_e = CVector3::Zero();
	if (ToPlayerAngle(m_forward) < 45.0f)
	{
		rrotspeed_max *= 2.0f;
	}
	/*��]*/
	forwardrotangle = CMath::RadToDeg(acosf(Acos(m_up.Dot(SideVec(m_forward)))));
	frotspeed = min(frotspeed_max, forwardrotangle);

	rot.SetRotationDeg(CVector3::AxisZ(), frotspeed*RotDirection(m_forward));
	m_rotation.Multiply(rot);
	Vector();

	forwardrotangle = CMath::RadToDeg(acosf(Acos(m_up.Dot(SideVec(m_forward)))));
	if (forwardrotangle < 0.5f)
	{
		ritedrotangle = CMath::RadToDeg(acosf(Acos(m_forward.Dot(SideVec(m_rite)))));
		rrotspeed = min(rrotspeed_max, ritedrotangle);

		rot.SetRotationDeg(CVector3::AxisX(), -rrotspeed);
		m_rotation.Multiply(rot);
		Vector();
	}

	bool NearPlayer = CVector3(m_position - m_player->GetPosition()).Length() < 2000.0f;
	if (NearPlayer)
	{
		if (ToPlayerAngle(m_up) < 90.0f)
		{
			rot.SetRotationDeg(CVector3::AxisX(), 2.0f);
			m_rotation.Multiply(rot);
			Vector();
		}
		if (ToPlayerAngle(m_up) >= 90.0f)
		{
			rot.SetRotationDeg(CVector3::AxisX(), -2.0f);
			m_rotation.Multiply(rot);
			Vector();
		}

	}


	/*�v���C���[�̑O�����ƃv���C���[���玩���Ɍ������x�N�g���Ƃ̊p�x�����߂�*/
	p_to_e = m_position - m_player->GetPosition();
	p_to_e.Normalize();
	acos_f = m_player->GetForward().Dot(p_to_e);
	angle = CMath::RadToDeg(acosf(Acos(acos_f)));


	if (ToPlayerAngle(m_forward) > 160.0f || angle < 20.0f)
	{
		if (m_nowspeed < BoostSpeed)
		{
			m_nowspeed += 200.0f;
		}
	}
	else
	{
		if (m_nowspeed > DefaultSpeed)
		{
			m_nowspeed -= 100.0f;
		}
		else
		{
			m_nowspeed += 100.0f;
		}
	}
	m_movespeed = m_forward * m_nowspeed;
	m_position += m_movespeed * deltaTime;
	for (const auto& enemy : m_class_of_newgo->GetEnemy())
	{
		if (this == enemy || enemy == NULL)
		{
			continue;
		}
		CVector3 E_to_E = enemy->GetPosition() - m_position;
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
		m_enemymarkerdraw = false;
		if (SCpos.z >= 0.0f)
		{
			m_enemymarkerdraw = true;
		}
		SCpos /= WVP.m[3][3];
		SCpos.x *= FRAME_BUFFER_W / 2.0f;
		SCpos.y *= FRAME_BUFFER_H / 2.0f;
		SCpos.z = 0.0f;
		m_enemymarkersprite.Update(
			SCpos,
			CQuaternion::Identity(),
			CVector3::One()*0.09f
		);
	}


	/*�G�l�~�[�̕����p�X�v���C�g�̃|�W�V�������v�Z*/
	{
		m_posinscreen = true;
		CVector3 camtoMypos = m_position - g_camera3D.GetPosition();
		CVector3 spritepos = { g_camera3D.GetRite().Dot(camtoMypos),g_camera3D.GetUp().Dot(camtoMypos),0.0f };

		camtoMypos.Normalize();
		if (g_camera3D.GetForward().Dot(camtoMypos) > cosf(g_camera3D.GetViewAngle()*2.0f))
		{
			m_posinscreen = false;
		}
		spritepos.Normalize();

		spritepos *= 500.0f;
		m_outenemysprite.Update(
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

		EnemyMove();
		BulletManager();
		SpriteManager();
	}
	else
	{
		m_posinscreen = false;
		m_enemymarkerdraw = false;
		m_movespeed = m_forward * m_nowspeed;
		m_position += m_movespeed * deltaTime;
		for (const auto& enemy : m_class_of_newgo->GetEnemy())
		{
			if (this == enemy || enemy == nullptr)
			{
				continue;
			}
			CVector3 E_to_E = enemy->GetPosition() - m_position;
			float length = E_to_E.Length();

			if (length < 500.0f)
			{
				E_to_E.Normalize();
				length = length - 500.0f;

				m_position += (E_to_E* length);
			}
		}
	}



	m_skinmodel.UpdateWorldMatrix(m_position, m_rotation, CVector3::One());
}

void Enemy::Draw()
{
	m_skinmodel.Draw(
		LightOn,
		g_camera3D.GetViewMatrix(),
		g_camera3D.GetProjectionMatrix()
	);



}

void Enemy::EffectDraw()
{
	for (const auto& effct : m_spriteeffect)
	{
		CVector3 pos = m_rite * effct->m_toengin.x + m_up * effct->m_toengin.y + m_forward * effct->m_toengin.z;
		effct->m_spriteeffect.Update(m_position + pos);
		effct->m_spriteeffect.Draw();
	}




	/*m_spriteeffect[0].Update(m_position + m_rite * 105.0f + m_forward * -130.0f);
	m_spriteeffect[1].Update(m_position + m_rite * -105.0f + m_forward * -130.0f);
	m_spriteeffect[0].Draw();
	m_spriteeffect[1].Draw();*/
}

void Enemy::PostDraw()
{
	if (m_posinscreen)
	{
		m_outenemysprite.Draw(
			*g_graphicsEngine->GetD3DDeviceContext()
		);
	}
	if (m_enemymarkerdraw)
	{
		m_enemymarkersprite.Draw(
			*g_graphicsEngine->GetD3DDeviceContext()
		);
	}


}

void Enemy::OnDestroy()
{
	m_class_of_newgo->GetResult()->SetKnockDownEnemySUM();
	m_class_of_newgo->GetEffect()->Play(m_position, CVector3::One()*100.0f);
	/*�G�l�~�[���폜���ꂽ�Ƃ��ꏏ�ɏ���*/
	for (const auto& effct : m_spriteeffect)
	{
		delete effct;
	}
	m_spriteeffect.clear();
	if (m_ritebullet != nullptr)
	{
		game_obj->DeleteGO(m_ritebullet);
	}
	if (m_leftbullet != nullptr)
	{
		game_obj->DeleteGO(m_leftbullet);
	}
}
