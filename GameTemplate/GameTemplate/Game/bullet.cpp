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
	
	m_tama.Init(L"Assets/modelData/missile.cmo");					//�ʂ̃��f���C�j�b�g
	
	m_tama.SetNormalMap(L"Assets/modelData/7_normal.dds");				//�m�[�}���}�b�v���Z�b�g
	
	switch (witchbullet)
	{
	case isPlayer: {
		m_player = game_obj->FindGO<Player>("player");					//�v���C���[�̌���
		m_player->AddMyPointer<Player, bullet>(&m_player, this);
		CoN = game_obj->FindGO<Class_of_NewGO>("newObject");			//�����ȃN���X��new����N���X������
		CoN->AddMyPointer<Class_of_NewGO, bullet>(&CoN, this);

		tamadir = m_player->Getforward();								//�ʂ̃f�B���N�V�����Ƀv���C���[�̃t�H���[�h����

		switch (LeftRite)		//���E�ǂ��炩�Ƀ~�T�C��������
		{
		case Left: {
			bulletpos = m_player->Getpos() + (m_player->Getrite()*-80.0f) + (m_player->Getup() *-20.0f);
			m_rotation = m_player->GetRotation();
			break;
		}
		case Rite: {
			bulletpos = m_player->Getpos() + (m_player->Getrite()*80.0f) + (m_player->Getup() *-20.0f);
			m_rotation = m_player->GetRotation();
			break;
		}
		default:
			break;
		}
		break;
	}
	case isEnemy: {

		m_player = game_obj->FindGO<Player>("player");					//�v���C���[�̌���
		m_player->AddMyPointer<Player, bullet>(&m_player, this);
		CoN = game_obj->FindGO<Class_of_NewGO>("newObject");			//�����ȃN���X��new����N���X������
		CoN->AddMyPointer<Class_of_NewGO,bullet>(&CoN, this);
	
		switch (LeftRite)		//���E�ǂ��炩�Ƀ~�T�C��������
		{
		case Left: {
			bulletpos = m_enemy->Getpos() + (m_enemy->Getrite()*-80.0f) + (m_enemy->Getup() *-20.0f);
			m_rotation = m_enemy->GetRotation();
			break;
		}
		case Rite: {
			bulletpos = m_enemy->Getpos() + (m_enemy->Getrite()*80.0f) + (m_enemy->Getup() *-20.0f);
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
	BtoT = target - bulletpos;
	BtoT.Normalize();
	tamadir = m_forward * 10.0f + BtoT;		//�e�̐i�s������ݒ�	30�͒���
	tamadir.Normalize();					//���K��


	if (abs(bulletmodellocal.Dot(tamadir)) <= 0.9999999999999f)//�����̊O�ς��Ƃ�Ȃ��悤�ɏ��O
	{
		CVector3 forwardModelLocal = bulletmodellocal;		
		float dotresult = forwardModelLocal.Dot(tamadir);	//����]��Ԃ̃��f���̑O�����ƁA�e�̐i�s�����Ƃ̓���
		CVector3 Axis;
		Axis.Cross(tamadir, forwardModelLocal);				//�O�ςŉ�]�̎������
		Axis.Normalize();									//���K��
		m_rotation.SetRotation(Axis, -Acos(dotresult));		//�쐬����������ɉ�]

		UpdateVector();										//���̍X�V
	}
	bulletpos += m_forward * speed * deltaTime;
}

void bullet::bulletFire()
{
	switch (witchbullet)
	{
	case isPlayer: {
		if (LockOnEnemy != nullptr)
		{
			CVector3 target = LockOnEnemy->Getpos();
			CVector3 toTarget = target - bulletpos;
			toTarget.Normalize();
			isHoming = m_forward.Dot(toTarget) > 0.0f &&CVector3(m_player->Getpos() - bulletpos).Length() > 1000.0f;
			
			if (isHoming)
			{
				
				BulletHoming(target);
			}
			else
			{
				bulletpos += m_forward * speed * deltaTime;
			}

			toTarget = LockOnEnemy->Getpos() - bulletpos;


			if (toTarget.Length() < 300.0f)
			{
				for (const auto& enemy : CoN->GetEnemy())
				{
					if (enemy == LockOnEnemy)
					{
						CoN->GetEnemy().erase(remove(CoN->GetEnemy().begin(), CoN->GetEnemy().end(), enemy),
							CoN->GetEnemy().end());
					}
				}
				game_obj->DeleteGO(LockOnEnemy);
				if (CoN != nullptr)
				{
					if (CoN->GetHitSE()->IsPlaying())
					{
						CoN->GetHitSE()->Stop();
					}
					CoN->GetHitSE()->Play(false);
				}
				game_obj->DeleteGO(this);
			}
		}
		else
		{
			bulletpos += m_forward * speed * deltaTime;
		}

		
		
		break;
	}
	case isEnemy: {
		CVector3 target = m_player->Getpos();
		CVector3 toTarget = target - bulletpos;
		toTarget.Normalize();
		isHoming = m_forward.Dot(toTarget) > 0.0f &&CVector3(m_enemy->Getpos() - bulletpos).Length() > 1000.0f;
		if (isHoming)
		{
			BulletHoming(target);
		}
		else
		{
			bulletpos += m_forward * speed * deltaTime;
		}
		
		if (m_player != nullptr&&!this->GetDeath_f())
		{
			CVector3 toPlayer = m_player->Getpos() - bulletpos;
			bool HitPlayer = toPlayer.Length() < 200.0f;
			if (HitPlayer)
			{
				m_player->SetHP(1);
				if (CoN != nullptr)
				{
					if (CoN->GetHitSE()->IsPlaying())
					{
						CoN->GetHitSE()->Stop();
					}
					CoN->GetHitSE()->Play(false);
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
		m_playerPos = m_player->Getpos();
	}
	
	UpdateVector();
	if (fire)
	{
		if (m_player != nullptr)
		{
			bulletFire();
		}
		else
		{
			bulletpos += m_forward * speed * deltaTime;
		}
		

		if (speed < bulletspeed)
		{
			speed += 100.0f;
		}
		m_time += 1.0f*deltaTime;

		if (m_time >= 10.0f)
		{
			game_obj->DeleteGO(this);
		}
		
	}
	else
	{
		switch (witchbullet)
		{
		case isPlayer: {
			if (m_player == nullptr)
			{
				game_obj->DeleteGO(this);
			}
			else
			{
				switch (LeftRite)		//���E�ǂ��炩�Ƀ~�T�C��������
				{
				case Left: {
					bulletpos = m_player->Getpos() + (m_player->Getrite()*-80.0f) + (m_player->Getup() *-20.0f);
					m_rotation = m_player->GetRotation();
					break;
				}
				case Rite: {
					bulletpos = m_player->Getpos() + (m_player->Getrite()*80.0f) + (m_player->Getup() *-20.0f);
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
				switch (LeftRite)		//���E�ǂ��炩�Ƀ~�T�C��������
				{
				case Left: {
					bulletpos = m_enemy->Getpos() + (m_enemy->Getrite()*-80.0f) + (m_enemy->Getup() *-20.0f);
					m_rotation = m_enemy->GetRotation();
					break;
				}
				case Rite: {
					bulletpos = m_enemy->Getpos() + (m_enemy->Getrite()*80.0f) + (m_enemy->Getup() *-20.0f);
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
	if (CoN == nullptr)
	{
		game_obj->DeleteGO(this);
	}
	
	m_tama.UpdateWorldMatrix(bulletpos, m_rotation, CVector3::One()*2.0f);		//���[���h�}�g���N�X�̍X�V
}

void bullet::Draw()
{
	m_tama.Draw(																				//�e�̕`��
		LightOn,
		g_camera3D.GetViewMatrix(),
		g_camera3D.GetProjectionMatrix()
	);
	
}

void bullet::EffectDraw()
{
	if (fire)
	{
		m_spriteeffect.Update(bulletpos + m_forward * -170.0f);
		m_spriteeffect.Draw();
	}
	
}

void bullet::OnDestroy()
{
}
