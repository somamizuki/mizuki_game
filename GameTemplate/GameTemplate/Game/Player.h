#pragma once
#include "ObjectInfo.h"
#include"character/HitObject.h"
#include"Enemy.h"
#include"SpriteEffect.h"
#include"level/Level.h"
#include "missileRechargeHUD.h"
#include"HPGaugeHUD.h"


class GameCamera;
class bullet;
class Class_of_NewGO;
class BossEnemy;
using namespace PlayerInfo;
class Player :public GameObject
{
public:
	Player(int No, const char* obj_name);
	~Player();
	/// <summary>
	/// �X�^�[�g�֐�
	/// </summary>
	bool Start();
	/// <summary>
	/// �A�b�v�f�[�g�֐�
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
	/// ��O�ɕ`�悵�������̂̕`��
	/// </summary>
	void PostDraw();
	/// <summary>
	/// UI�`��
	/// </summary>
	void UIDraw();
	/// <summary>
	/// DeleteGO���ɌĂ΂��֐�
	/// </summary>
	void OnDestroy();
	/// <summary>
	/// �|�W�V�����̃Z�b�^�[
	/// </summary>
	/// <param name="pos">�|�W�V����(CVector3)</param>
	void SetPosition(CVector3 pos)
	{
		m_position = pos;
	}
	/// <summary>
	/// ��]�̃Z�b�^�[
	/// </summary>
	/// <param name="rot">��](CQuaternion)</param>
	void SetRotation(CQuaternion rot)
	{
		m_rotation = rot;
	}
	/// <summary>
	/// �|�W�V�����̃Q�b�^�[
	/// </summary>
	/// <returns>�|�W�V����(CVector3)</returns>
	const CVector3& GetPosition() const
	{
		return m_position;
	}
	/// <summary>
	/// �O�����̃Q�b�^�[
	/// </summary>
	/// <returns>�O����(CVector3)</returns>
	const CVector3& GetForward() const
	{
		return m_forward;
	}
	/// <summary>
	/// �E�����̃Q�b�^�[
	/// </summary>
	/// <returns>�E����(CVector3)</returns>
	const CVector3& GetRite() const
	{
		return m_rite;
	}
	/// <summary>
	/// ������̃Q�b�^�[
	/// </summary>
	/// <returns>�����(CVector3)</returns>
	const CVector3& GetUp() const
	{
		return m_up;
	}
	/// <summary>
	/// �v���C���[�̈ړ����x�̃Q�b�^�[
	/// </summary>
	/// <returns>�ړ����x(CVector3)</returns>
	const CVector3& GetMoveSpeed() const
	{
		return movespeed;
	}

	/// <summary>
	/// ��]�̃Q�b�^�[
	/// </summary>
	/// <returns>��](CQuaternion)</returns>
	const CQuaternion& GetRotation() const
	{
		return m_rotation;
	}
	/// <summary>
	/// HP�̃Z�b�^�[
	/// </summary>
	/// <param name="damage">�_���[�W��(int)</param>
	void SetHP(int damage)
	{
		if (m_playerparam.Time <= 0.0f)
		{
			m_playerparam.HP = max(0, m_playerparam.HP - damage);
			m_playerparam.Time = NODAMAGETIME;
		}

	}

private:
	//�v���C���[�̃p�����[�^�[���������\����
	struct PlayerParam
	{
		int		HP = 50;
		float	Time = 0.0f;
	};


	PlayerParam					m_playerparam;							//�v���C���[�̃p�����[�^�[
	const float					HPMAX = m_playerparam.HP;				//HP�̍ő�l
	const float					NODAMAGETIME = 0.5f;					//���G����

	SkinModel					m_skinmodel;								//�X�L�����f���B
	CVector3					m_position = CVector3::Zero();			//�v���C���[�̃|�W�V����
	CQuaternion					m_rotation = CQuaternion::Identity();	//�v���C���[�̉�]
	CVector3					movespeed = CVector3::Zero();			//�ړ����x
	CVector3					m_forward;								//�O����
	CVector3					m_rite;									//�E����
	CVector3					m_up;									//�����
	ShaderResourceView			m_aimSRV;								//�G�C���X�v���C�g�̃V�F�[�_�[���\�[�X�r���[
	sprite						m_aimsprite;							//�G�C���X�v���C�g
	ShaderResourceView			m_lockonSRV;							//���b�N�I���X�v���C�g�̃V�F�[�_�[���\�[�X�r���[
	sprite						m_lockonsprite;							//���b�N�I���X�v���C�g
	CVector3					m_lockonenemypos = { 0.0f,0.0f,0.0f };	//���b�N�I�����ꂽ�X�v���C�g�̃|�W�V����


	float						pad_X;									//�p�b�hX�̓��͗�
	float						pad_Y;									//�p�b�hY�̓��͗�
	const float					DEFAULTSPEED = 1800.0f;					//�f�t�H���g�̑��x
	const float					BOOSTSPEED = 3000.0f;					//�u�[�X�g���̑��x
	const float					ROTSPEED_X = 3.0f;						//Z������̉�]�X�s�[�h
	const float					ROTSPEED_Y = 2.0f;						//X������̉�]�X�s�[�h
	const float					ROTSPEED_TW = 0.3f;						//�G�C�������������ϐ�


	const float					BULLETSPAN = 1.0f;						//�~�T�C���̔��ˊԊu
	float						m_ritebullettime = 0.0f;				//�E�~�T�C���𔭎˂��Ă���̌o�ߎ���
	float						m_leftbullettime = 0.0f;				//���~�T�C���𔭎˂��Ă���̌o�ߎ���
	float						m_leftmissilegaugelevel = 1.0f;			//���~�T�C���̃Q�[�W���x��
	float						m_ritemissilegaugelevel = 1.0f;			//�E�~�T�C���̃Q�[�W���x��

	bool						m_lockonflag = false;					//���b�N�I���t���O

	float						m_nowspeed = 0.0f;						//�ړ����x(�T�u)

	void PlayerMove();				//�v���C���[�̈ړ��֐�
	void PlayerReturn();			//�~�b�V�����G���A�O�ɏo�Ȃ��悤�ɂ���
	void BossFightMove();			//�{�X��̈ړ�
	void BossFightInit();			//�{�X��̏�����
	bool						m_bossfightinitflag = false;			//�{�X��̏��������������̃t���O
	BossEnemy*					m_bossenemy = nullptr;					//�{�X�̃|�C���^�[
	CVector3					m_bossposition = CVector3::Zero();		//�{�X�̃|�W�V����
	const float					TOBOSSLENGTH = 9000.0f;					//�{�X�ւ̋���
	const float					BOSSHEIGHT = 8000.0f;					//�{�X�̍���
	CVector3					m_bosstoplayer = CVector3::Zero();		//�{�X����v���C���[�ւ̃x�N�g��
	void Vector();														//�v���C���[�̑O�E��̃x�N�g�����v�Z����֐�
	void BulletManager();												//�o���b�g���Ǘ�����֐�
	Enemy* LockOnManager();												//���b�N�I�����Ǘ�����֐�
	Enemy*						m_prevlockonenemy = nullptr;			//�O�t���[���Ń��b�N�I������Ă����G�l�~�[
	void SpriteManager();												//�X�v���C�g���Ǘ�����֐�
	/// <summary>
	/// ���ς̌��ʂ�1.0�`-1.0�͈̔͂𒴂��Ȃ��悤�ɂ���B
	/// </summary>
	/// <param name="dotresult">���ό���(float)</param>
	/// <returns>�p�x���W�A��(float)</returns>
	float Acos(float dotresult)
	{
		float resulte = acosf(min(1.0f, max(-1.0f, dotresult)));
		return resulte;
	}

	GameCamera*					m_camera = nullptr;				//�J�����̃|�C���^�[
	Class_of_NewGO*				m_class_of_newgo = nullptr;		//new����N���X�̃|�C���^�[
	bullet*						m_ritebullet = nullptr;			//�E�o���b�g�̃|�C���^�[
	bullet*						m_leftbullet = nullptr;			//���o���b�g�̃|�C���^�[
	enum PlayerState		//�v���C���[�̃X�e�[�g
	{
		Nomal,		//�ʏ�
		Return,		//���_�ɖ߂�(�~�b�V�����͈͂𒴂�����)
		Boss,		//�{�X��
	};
	PlayerState					m_playerstate = Nomal;
	HitObject					m_characon;						//�L�����R��

	/*�W�F�b�g�G���W���̍\����*/
	struct Engin
	{
		SpriteEffect	m_spriteeffect;
		CVector3		m_toengin;
	};
	std::vector<Engin*>			m_spriteeffectlist;				//�W�F�b�g�G���W����vector
	ShaderResourceView			m_effectSRV;					//�W�F�b�g�G���W���̃V�F�[�_�[���\�[�X�r���[
	Level						m_playerenginlevel;				//�G���W���̃|�W�V���������������x��
	missileRechargeHUD			m_leftrechargeHUD;				//���~�T�C���̃��`���[�WHUD
	missileRechargeHUD			m_riterechargeHUD;				//�E�~�T�C���̃��`���[�WHUD
	HPGaugeHUD					m_hpHUD;						//HP��HUD

};

