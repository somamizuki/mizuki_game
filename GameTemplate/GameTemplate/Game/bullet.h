#pragma once

#include"Class_of_NewGO.h"
#include"ObjectInfo.h"
#include"SpriteEffect.h"

using namespace BulletInfo;
class Player;
class bullet :public GameObject
{
public:
	/// <summary>
	/// �R���X�g���N�^
	/// </summary>
	/// <param name="No"></param>
	/// <param name="obj_name"></param>
	bullet(int No, const char* obj_name);
	/// <summary>
	/// �f�X�g���N�^
	/// </summary>
	~bullet();
	/// <summary>
	/// �X�^�[�g�֐�
	/// </summary>
	bool Start();
	/// <summary>
	/// �A�b�v�f�[�g
	/// </summary>
	void Update();
	/// <summary>
	/// �`��֐�
	/// </summary>
	void Draw();
	/// <summary>
	/// �G�t�F�N�g�`��
	/// </summary>
	void EffectDraw();
	/// <summary>
	/// Delete���ɌĂ΂��֐�
	/// </summary>
	void OnDestroy();

	/// <summary>
	/// �|�W�V�����̃Q�b�^�[
	/// </summary>
	/// <returns>CVector3</returns>
	const CVector3 Getpos() const
	{
		return m_position;
	}
	/// <summary>
	/// ���˂��ꂽ��
	/// </summary>
	/// <returns>bool</returns>
	bool isfire()
	{
		return m_fireflag;
	}
	/// <summary>
	/// �o���b�g�̃p�����[�^�[���Z�b�g
	/// </summary>
	void SetBulletParam()
	{
		if (!Get_isStart())
		{
			if (Start())
			{
				Set_isStart(true);
			}
		}
		switch (m_witchbullet)
		{
		case isPlayer: {
			m_speed = m_player->GetMoveSpeed().Length() + 500.0f;
			m_fireflag = true;
			break;
		}
		case isEnemy: {
			if (m_enemy != nullptr)
			{
				m_speed = m_enemy->GetMoveSpeed().Length() + bulletspeed;
				m_fireflag = true;
			}
			break;
		}
		default:
			break;
		}
	}
	/// <summary>
	/// ���b�N�I�������G�l�~�[���Z�b�g
	/// </summary>
	/// <param name="enemy"></param>
	void SetTarget(Enemy* enemy)
	{
		m_lockonenemy = enemy;
		if (m_lockonenemy != nullptr)
		{
			m_lockonenemy->RemoveHasMyPointerObject(this);
			m_lockonenemy->AddMyPointer<Enemy, bullet>(&m_lockonenemy, this);
		}
	}
	/// <summary>
	/// ���E�ǂ��炩��I��
	/// </summary>
	/// <param name="LR">LorR</param>
	void SetLeft_or_Rite(LorR LR)
	{
		m_left_or_rite = LR;
	}
	/// <summary>
	/// �G�l�~�[�̒e�̏ꍇ�A���g���Z�b�g
	/// </summary>
	/// <param name="enemy"></param>
	void SetEnemy(Enemy* enemy)
	{
		m_enemy = enemy;
	}
	/// <summary>
	/// Player��Enemy�ǂ���̃o���b�g�����Z�b�g
	/// </summary>
	/// <param name="Witch">witchBullet</param>
	void WitchBullet(witchBullet Witch)
	{
		m_witchbullet = Witch;
	}
	/// <summary>
	/// �G�l�~�[�̃Q�b�^�[
	/// </summary>
	/// <returns>Enemy*</returns>
	Enemy* Getm_enemy()
	{
		return m_enemy;
	}
	/// <summary>
	/// �v���C���[�̃Q�b�^�[
	/// </summary>
	/// <returns>Player*</returns>
	Player* Getm_player()
	{
		return m_player;
	}
private:
	void BulletFire();
	void UpdateVector();
	void BulletHoming(CVector3& target);
	float Acos(float dotresult)				//���ς̌��ʂ�1.0�`-1.0�͈̔͂𒴂��Ȃ��悤�ɂ���B
	{
		float resulte = acosf(min(1.0f, max(-1.0f, dotresult)));
		return resulte;
	}

	//����
	SkinModel			m_skinmodel;							//�~�T�C���̃��f��
	CVector3			m_movedirection = CVector3::Zero();		//�~�T�C���̃f�B���N�V����
	CVector3			m_position = CVector3::Zero();			//�~�T�C���̃|�W�V����
	CQuaternion			m_rotation = CQuaternion::Identity();	//�~�T�C���̉�]
	float				m_speed = 0.0f;							//�~�T�C���̍ŏI���x
	float				m_time = 0.0f;							//�~�T�C���̍ő��s����
	Player*				m_player = nullptr;						//�v���C���[�̃|�C���^�[
	CVector3			m_playerposition = CVector3::Zero();	//�v���C���[�̃|�W�V����
	Enemy*				m_lockonenemy = nullptr;				//���b�N�I�����ꂽEnemy�������|�C���^�[
	Enemy*				m_enemy = nullptr;						//Enemy�̒e�̂Ƃ�Enemy���g�������|�C���^�[
	Class_of_NewGO*		m_class_of_newgo = nullptr;				//�����ȃN���X��new����N���X�̃|�C���^�[
	bool				m_fireflag = false;						//�~�T�C�����˂̃t���O
	bool				m_isplayersbullet = false;				//true�Ȃ�Player�̒e
	bool				m_isenemysbullet = false;				//true�Ȃ�Enemy�̒e
	bool				m_ishoming = false;						//�ǐՃt���O
	LorR				m_left_or_rite;							//enum,Left�Ȃ獶�ɁARite�Ȃ�E�ɒe����������
	witchBullet			m_witchbullet;							//enum,isPlayer�Ȃ�Player�́AisEnemy�Ȃ�Enemy�̒e
	/*���f���̎��A�O�A�E�A��*/
	CVector3			m_forward = CVector3::Zero();
	CVector3			m_rite = CVector3::Zero();
	CVector3			m_up = CVector3::Zero();

	SpriteEffect		m_spriteeffect;							//�X�v���C�g�G�t�F�N�g(�p�[�e�B�N���̂悤�Ȏ���)
	ShaderResourceView	m_srv;									//�G�t�F�N�g��SRV
};

