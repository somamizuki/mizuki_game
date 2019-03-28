#include "stdafx.h"
#include "bullet.h"
#include"Player.h"


CVector3 bulletmodellocal = CVector3::AxisZ();		//���f�����W�n�̑O�ɓ����郏�[���h�̎�Z����
bullet::bullet(int No, const char* obj_name) : GameObject(No, obj_name)
{
}


bullet::~bullet()
{

}

bool bullet::Start()
{

	m_skinmodel.Init(L"Assets/modelData/missile.cmo");					//�ʂ̃��f���C�j�b�g
	m_skinmodel.SetNormalMap(L"Resource/sprite/7_normal.dds");				//�m�[�}���}�b�v���Z�b�g
	m_player = game_obj->FindGO<Player>("player");					//�v���C���[�̌���
	m_player->AddMyPointer<Player, bullet>(&m_player, this);
	m_class_of_newgo = game_obj->FindGO<Class_of_NewGO>("newObject");			//�����ȃN���X��new����N���X������
	m_class_of_newgo->AddMyPointer<Class_of_NewGO, bullet>(&m_class_of_newgo, this);
	switch (m_witchbullet)
	{
	case isPlayer: {
		m_movedirection = m_player->GetForward();								//�ʂ̃f�B���N�V�����Ƀv���C���[�̃t�H���[�h����

		switch (m_left_or_rite)		//���E�ǂ��炩�Ƀ~�T�C��������
		{
		case Left: {
			m_position = m_player->GetPosition() + (m_player->GetRite()*-80.0f) + (m_player->GetUp() *-20.0f);
			m_rotation = m_player->GetRotation();
			break;
		}
		case Rite: {
			m_position = m_player->GetPosition() + (m_player->GetRite()*80.0f) + (m_player->GetUp() *-20.0f);
			m_rotation = m_player->GetRotation();
			break;
		}
		default:
			break;
		}
		break;
	}
	case isEnemy: {
		switch (m_left_or_rite)		//���E�ǂ��炩�Ƀ~�T�C��������
		{
		case Left: {
			m_position = m_enemy->GetPosition() + (m_enemy->GetRite()*-80.0f) + (m_enemy->GetUp() *-20.0f);
			m_rotation = m_enemy->GetRotation();
			break;
		}
		case Rite: {
			m_position = m_enemy->GetPosition() + (m_enemy->GetRite()*80.0f) + (m_enemy->GetUp() *-20.0f);
			m_rotation = m_enemy->GetRotation();
			break;
		}
		default:
			break;
		}
		break;
	}
	default:
		break;
	}
	m_srv.CreateFromDDSTextureFromFile(L"Resource/sprite/fog.dds");
	m_spriteeffect.Init(m_srv.GetBody(), 0.15f, 0);
	return true;
}

void bullet::UpdateVector()
{
	/*�N�I�[�^�j�I�����烂�f���̎����X�V*/
	CMatrix RotM;
	RotM.MakeRotationFromQuaternion(m_rotation);
	m_rite = { RotM.m[0][0] , RotM.m[0][1] ,RotM.m[0][2] };
	m_up = { RotM.m[1][0] , RotM.m[1][1] ,RotM.m[1][2] };
	m_forward = { RotM.m[2][0] , RotM.m[2][1] ,RotM.m[2][2] };
	m_rite.Normalize();
	m_up.Normalize();
	m_forward.Normalize();
}

void bullet::BulletHoming(CVector3& target)
{
	CVector3 BtoT;					//�e����^�[�Q�b�g�Ɍ������x�N�g��
	BtoT = target - m_position;
	BtoT.Normalize();
	m_movedirection = m_forward * 10.0f + BtoT;		//�e�̐i�s������ݒ�	30�͒���
	m_movedirection.Normalize();					//���K��


	if (abs(bulletmodellocal.Dot(m_movedirection)) <= 0.9999999999999f)//�����̊O�ς��Ƃ�Ȃ��悤�ɏ��O
	{
		CVector3 forwardModelLocal = bulletmodellocal;
		float dotresult = forwardModelLocal.Dot(m_movedirection);	//����]��Ԃ̃��f���̑O�����ƁA�e�̐i�s�����Ƃ̓���
		CVector3 Axis;
		Axis.Cross(m_movedirection, forwardModelLocal);				//�O�ςŉ�]�̎������
		Axis.Normalize();									//���K��
		m_rotation.SetRotation(Axis, -Acos(dotresult));		//�쐬����������ɉ�]

		UpdateVector();										//���̍X�V
	}
	m_position += m_forward * m_speed * deltaTime;
}

void bullet::BulletFire()
{
	switch (m_witchbullet)
	{
	case isPlayer: {
		if (m_lockonenemy != nullptr)
		{
			CVector3 target = m_lockonenemy->GetPosition();
			CVector3 toTarget = target - m_position;
			toTarget.Normalize();
			m_ishoming = m_forward.Dot(toTarget) > 0.0f &&CVector3(m_player->GetPosition() - m_position).Length() > 1000.0f;

			if (m_ishoming)
			{
				BulletHoming(target);
			}
			else
			{
				m_position += m_forward * m_speed * deltaTime;
			}

			toTarget = m_lockonenemy->GetPosition() - m_position;


			if (toTarget.Length() < 300.0f)
			{
				game_obj->DeleteGO(m_lockonenemy);
				if (m_class_of_newgo != nullptr)
				{
					if (m_class_of_newgo->GetHitSE()->IsPlaying())
					{
						m_class_of_newgo->GetHitSE()->Stop();
					}
					m_class_of_newgo->GetHitSE()->Play(false);
				}
				game_obj->DeleteGO(this);
			}
		}
		else
		{
			m_position += m_forward * m_speed * deltaTime;
		}

		break;
	}
	case isEnemy: {
		CVector3 target = m_player->GetPosition();
		CVector3 toTarget = target - m_position;
		toTarget.Normalize();
		m_ishoming = m_forward.Dot(toTarget) > 0.0f &&CVector3(m_enemy->GetPosition() - m_position).Length() > 1000.0f;
		if (m_ishoming)
		{
			BulletHoming(target);
		}
		else
		{
			m_position += m_forward * m_speed * deltaTime;
		}

		if (m_player != nullptr && !this->GetDeath_f())
		{
			CVector3 toPlayer = m_player->GetPosition() - m_position;
			bool HitPlayer = toPlayer.Length() < 200.0f;
			if (HitPlayer)
			{
				m_player->SetHP(1);
				if (m_class_of_newgo != nullptr)
				{
					if (m_class_of_newgo->GetHitSE()->IsPlaying())
					{
						m_class_of_newgo->GetHitSE()->Stop();
					}
					m_class_of_newgo->GetHitSE()->Play(false);
				}
				game_obj->DeleteGO(this);
			}
		}

		break;
	}
	default:
		break;
	}
}

void bullet::Update()
{
	if (m_player != nullptr)
	{
		m_playerposition = m_player->GetPosition();
	}

	UpdateVector();
	if (m_fireflag)
	{
		if (m_player != nullptr)
		{
			BulletFire();
		}
		else
		{
			m_position += m_forward * m_speed * deltaTime;
		}


		if (m_speed < bulletspeed)
		{
			m_speed += 100.0f;
		}
		m_time += 1.0f*deltaTime;

		if (m_time >= 10.0f)
		{
			game_obj->DeleteGO(this);
		}

	}
	else
	{
		switch (m_witchbullet)
		{
		case isPlayer: {
			if (m_player == nullptr)
			{
				game_obj->DeleteGO(this);
			}
			else
			{
				switch (m_left_or_rite)		//���E�ǂ��炩�Ƀ~�T�C��������
				{
				case Left: {
					m_position = m_player->GetPosition() + (m_player->GetRite()*-80.0f) + (m_player->GetUp() *-20.0f);
					m_rotation = m_player->GetRotation();
					break;
				}
				case Rite: {
					m_position = m_player->GetPosition() + (m_player->GetRite()*80.0f) + (m_player->GetUp() *-20.0f);
					m_rotation = m_player->GetRotation();
					break;
				}
				default:
					break;
				}
			}
			break;
		}
		case isEnemy: {
			if (m_enemy != nullptr)
			{
				switch (m_left_or_rite)		//���E�ǂ��炩�Ƀ~�T�C��������
				{
				case Left: {
					m_position = m_enemy->GetPosition() + (m_enemy->GetRite()*-80.0f) + (m_enemy->GetUp() *-20.0f);
					m_rotation = m_enemy->GetRotation();
					break;
				}
				case Rite: {
					m_position = m_enemy->GetPosition() + (m_enemy->GetRite()*80.0f) + (m_enemy->GetUp() *-20.0f);
					m_rotation = m_enemy->GetRotation();
					break;
				}
				default:
					break;
				}
			}


			break;
		}
		default:
			break;
		}
	}
	if (m_class_of_newgo == nullptr)
	{
		game_obj->DeleteGO(this);
	}

	m_skinmodel.UpdateWorldMatrix(m_position, m_rotation, CVector3::One()*2.0f);		//���[���h�}�g���N�X�̍X�V
}

void bullet::Draw()
{
	m_skinmodel.Draw(																				//�e�̕`��
		LightOn,
		g_camera3D.GetViewMatrix(),
		g_camera3D.GetProjectionMatrix()
	);

}

void bullet::EffectDraw()
{
	if (m_fireflag)
	{
		m_spriteeffect.Update(m_position + m_forward * -170.0f);
		m_spriteeffect.Draw();
	}

}

void bullet::OnDestroy()
{
}
