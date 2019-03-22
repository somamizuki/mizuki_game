#pragma once
#include "ObjectInfo.h"
#include"character/HitObject.h"
#include"Enemy.h"
#include"SpriteEffect.h"
#include"level/Level.h"
#include "missileRechargeHUD.h"
#include"HPGaugeHUD.h"


class m_camera;
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
	void setposition(CVector3 pos)
	{
		m_position = pos;
	}
	/// <summary>
	/// ��]�̃Z�b�^�[
	/// </summary>
	/// <param name="rot">��](CQuaternion)</param>
	void setrot(CQuaternion rot)
	{
		m_rotation = rot;
	}
	/// <summary>
	/// �|�W�V�����̃Q�b�^�[
	/// </summary>
	/// <returns>�|�W�V����(CVector3)</returns>
	const CVector3& Getpos() const
	{
		return m_position;
	}
	/// <summary>
	/// �O�����̃Q�b�^�[
	/// </summary>
	/// <returns>�O����(CVector3)</returns>
	const CVector3& Getforward() const
	{
		return m_forward;
	}
	/// <summary>
	/// �E�����̃Q�b�^�[
	/// </summary>
	/// <returns>�E����(CVector3)</returns>
	const CVector3& Getrite() const
	{
		return m_rite;
	}
	/// <summary>
	/// ������̃Q�b�^�[
	/// </summary>
	/// <returns>�����(CVector3)</returns>
	const CVector3& Getup() const
	{
		return m_up;
	}
	/// <summary>
	/// �v���C���[�̈ړ����x�̃Q�b�^�[
	/// </summary>
	/// <returns>�ړ����x(CVector3)</returns>
	const CVector3& Get_PlayerMove() const
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
		if (m_playerParam.Time <= 0.0f)
		{
			m_playerParam.HP = max(0, m_playerParam.HP - damage);
			m_playerParam.Time = nodamageeTime;
		}

	}

private:
	//�v���C���[�̃p�����[�^�[���������\����
	struct playerParam
	{
		int HP = 100;
		float Time = 0.0f;
	};


	playerParam m_playerParam;							//�v���C���[�̃p�����[�^�[
	const float HPMAX = m_playerParam.HP;				//HP�̍ő�l
	const float nodamageeTime = 0.5f;					//���G����

	SkinModel m_model;									//�X�L�����f���B
	CVector3 m_position = CVector3::Zero();				//�v���C���[�̃|�W�V����
	CQuaternion m_rotation = CQuaternion::Identity();	//�v���C���[�̉�]
	CVector3 movespeed = CVector3::Zero();				//�ړ����x
	CVector3 m_forward;									//�O����
	CVector3 m_rite;									//�E����
	CVector3 m_up;										//�����
	ShaderResourceView aimSRV;							//�G�C���X�v���C�g�̃V�F�[�_�[���\�[�X�r���[
	sprite aimsprite;									//�G�C���X�v���C�g
	ShaderResourceView LockOnSRV;						//���b�N�I���X�v���C�g�̃V�F�[�_�[���\�[�X�r���[
	sprite LockOnSprite;								//���b�N�I���X�v���C�g
	CVector3 LockOnEnemyPos = { 0.0f,0.0f,0.0f };		//���b�N�I�����ꂽ�X�v���C�g�̃|�W�V����


	float pad_X;									//�p�b�hX�̓��͗�
	float pad_Y;									//�p�b�hY�̓��͗�
	const float DefaultSpeed = 1800.0f;					//�f�t�H���g�̑��x
	const float BoostSpeed = 3000.0f;					//�u�[�X�g���̑��x
	const float RotSpeed_X = 3.0f;						//Z������̉�]�X�s�[�h
	const float RotSpeed_Y = 2.0f;						//X������̉�]�X�s�[�h
	const float RotSpeed_Tw = 0.3f;						//�G�C�������������ϐ�


	const float bulletspan = 1.0f;						//�~�T�C���̔��ˊԊu
	float ritebulletTime = 0.0f;						//�E�~�T�C���𔭎˂��Ă���̌o�ߎ���
	float leftbulletTime = 0.0f;						//���~�T�C���𔭎˂��Ă���̌o�ߎ���
	float leftmissileGaugelevel = 1.0f;					//���~�T�C���̃Q�[�W���x��
	float ritemissileGaugelevel = 1.0f;					//�E�~�T�C���̃Q�[�W���x��

	bool LockOnflag = false;							//���b�N�I���t���O

	float Speed = 0.0f;									//�ړ����x(�T�u)

	void playermove();								//�v���C���[�̈ړ��֐�
	void playerreturn();							//�~�b�V�����G���A�O�ɏo�Ȃ��悤�ɂ���
	void bossfightmove();							//�{�X��̈ړ�
	void bossfightInit();							//�{�X��̏�����
	bool bossfightInitflag = false;					//�{�X��̏��������������̃t���O
	BossEnemy* m_bossenemy = nullptr;				//�{�X�̃|�C���^�[
	CVector3 m_bosspos = CVector3::Zero();			//�{�X�̃|�W�V����
	const float tobosslen = 9000.0f;				//�{�X�ւ̋���
	const float bosshight = 8000.0f;				//�{�X�̍���
	CVector3 m_BosstoPlayer = CVector3::Zero();		//�{�X����v���C���[�ւ̃x�N�g��
	void vector();									//�v���C���[�̑O�E��̃x�N�g�����v�Z����֐�
	void bulletManager();							//�o���b�g���Ǘ�����֐�
	Enemy* LockOnManager();							//���b�N�I�����Ǘ�����֐�
	Enemy* prevLockOnEnemy = nullptr;				//�O�t���[���Ń��b�N�I������Ă����G�l�~�[
	void spritemanager();							//�X�v���C�g���Ǘ�����֐�
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

	m_camera* camera = nullptr;						//�J�����̃|�C���^�[
	Class_of_NewGO* CofNG = nullptr;				//new����N���X�̃|�C���^�[
	bullet* RiteBullet = nullptr;					//�E�o���b�g�̃|�C���^�[
	bullet* LeftBullet = nullptr;					//���o���b�g�̃|�C���^�[
	enum PlayerState								//�v���C���[�̃X�e�[�g
	{
		Nomal,		//�ʏ�
		Return,		//���_�ɖ߂�(�~�b�V�����͈͂𒴂�����)
		Boss,		//�{�X��
	};
	PlayerState pState = Nomal;
	HitObject m_characon;							//�L�����R��

	/*�W�F�b�g�G���W���̍\����*/
	struct Engin
	{
		SpriteEffect spriteeffect;
		CVector3 toEngin;
	};
	std::vector<Engin*> spriteeffect;			//�W�F�b�g�G���W����vector
	ShaderResourceView m_srv;					//�W�F�b�g�G���W���̃V�F�[�_�[���\�[�X�r���[
	Level playerenginlevel;						//�G���W���̃|�W�V���������������x��
	missileRechargeHUD m_leftRechargeHUD;		//���~�T�C���̃��`���[�WHUD
	missileRechargeHUD m_riteRechargeHUD;		//�E�~�T�C���̃��`���[�WHUD
	HPGaugeHUD m_hpHUD;							//HP��HUD

};

