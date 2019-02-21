#pragma once

#include"Class_of_NewGO.h"
#include"ObjectInfo.h"
#include"SpriteEffect.h"

using namespace BulletInfo;
class Player;
class bullet:public GameObject
{
public:
	bullet(int No, const char* obj_name);
	~bullet();

	bool Start();									//�X�^�[�g�֐�(�������Ƃ�)
	void Update();									//�X�V����
	void Draw();									//�`��
	void EffectDraw();

	/*�|�W�V������������֐�*/
	const CVector3 Getpos() const
	{
		return bulletpos;
	}
	/*�e�����˂��ꂽ���ǂ����𔻒肷��*/
	bool isfire()
	{
		return fire;
	}

	void SetBulletParam()
	{
		if (!Get_isStart())
		{
			if (Start())
			{
				Set_isStart(true);
			}
		}
		switch (witchbullet)
		{
		case isPlayer: {
			speed = m_player->Get_PlayerMove().Length() + 500.0f;
			fire = true;
			break;
		}
		case isEnemy: {
			if (m_enemy != nullptr)
			{
				speed = m_enemy->Getmovespeed().Length() + bulletspeed;
				fire = true;
			}
			break;
		}
		default:
			break;
		}
	}

	void SetTarget(Enemy* enemy)
	{
		LockOnEnemy = enemy;
		if (LockOnEnemy != nullptr)
		{
			LockOnEnemy->AddDeleteGOListeners([&](GameObject* go)
			{
				LockOnEnemy = nullptr;
			});
		}
	}

	void SetLeft_or_Rite(LorR LR)
	{
		LeftRite = LR;
	}

	void SetEnemy(Enemy* enemy)
	{
		m_enemy = enemy;
		
	}

	void WitchBullet(witchBullet Witch)
	{
		witchbullet = Witch;
	}
	


	Enemy* Getm_enemy()
	{
		return m_enemy;
	}
	Player* Getm_player()
	{
		return m_player;
	}

private:
	void bulletFire();
	void UpdateVector();
	void BulletHoming(CVector3& target);
	float Acos(float dotresult)				//���ς̌��ʂ�1.0�`-1.0�͈̔͂𒴂��Ȃ��悤�ɂ���B
	{
		float resulte = acosf(min(1.0f, max(-1.0f, dotresult)));
		return resulte;
	}

	//����
	SkinModel m_tama;								//�ʂ̃��f��
	CVector3 tamadir = CVector3::Zero();			//�ʂ̃f�B���N�V����
	CVector3 bulletpos = CVector3::Zero();			//�ʂ̃|�W�V����
	CQuaternion m_rotation = CQuaternion::Identity();//�e�̉�]
	float speed = 0.0f;								//�ʂ̍ŏI���x
	float m_time = 0.0f;
	Player* m_player = nullptr;						//�v���C���[�̃|�C���^�[
	CVector3 m_playerPos = CVector3::Zero();
	Enemy* LockOnEnemy = nullptr;					//���b�N�I�����ꂽEnemy�������|�C���^�[
	Enemy* m_enemy = nullptr;						//Enemy�̒e�̂Ƃ�Enemy���g�������|�C���^�[
	Class_of_NewGO* CoN = nullptr;					//�����ȃN���X��new����N���X�̃|�C���^�[
	ID3D11ShaderResourceView* g_normalMapSRV = nullptr;//�@���}�b�v�p��SRV
	bool fire = false;								//�~�T�C�����˂̃t���O
	bool PlayersBullet = false;						//true�Ȃ�Player�̒e
	bool EnemysBullet = false;						//true�Ȃ�Enemy�̒e
	bool isHoming = false;
	LorR LeftRite;									//enum,Left�Ȃ獶�ɁARite�Ȃ�E�ɒe����������
	witchBullet witchbullet;						//enum,isPlayer�Ȃ�Player�́AisEnemy�Ȃ�Enemy�̒e
	/*���f���̎��A�O�A�E�A��*/
	CVector3 m_forward = CVector3::Zero();
	CVector3 m_rite = CVector3::Zero();
	CVector3 m_up = CVector3::Zero();

	SpriteEffect m_spriteeffect;
	ShaderResourceView m_srv;
};

